#include "update.h"
#include "lvgl.h"
#include <time.h>
#include <locale.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

int cpu_usage;
int ram_usage;
int cpu_temp;
double download_speed;
double upload_speed;
char time_str[16];
char date_str[16];
char weekday_str[16];
char eth0_ip[64];
char eth1_ip[64];
char wlan0_ip[64];
char hostname_str[64];
/* Owned by the web UI: pushed over the ctrl socket at connect, empty until then. */
char app_version_str[64];

static volatile int monitor_running = 0;

void get_current_time_str(char *buffer, size_t size)
{
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%H:%M", tm_info);
}

void get_current_date_str(char *buffer, size_t size)
{
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d", tm_info);
}

void get_current_weekday_str(char *buffer, size_t size)
{
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    const char *weekdays[] = {"Sunday", "Monday", "Tuesday", "Wednesday",
                               "Thursday", "Friday", "Saturday"};
    if (tm_info->tm_wday >= 0 && tm_info->tm_wday <= 6)
        snprintf(buffer, size, "%s", weekdays[tm_info->tm_wday]);
    else
        snprintf(buffer, size, "---");
}

static int get_network_stats(const char *interface, NetworkStats *stats)
{
    FILE *file = fopen("/proc/net/dev", "r");
    if (!file) return -1;

    char line[256];
    int found = 0;

    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        char *name = line;
        while (*name == ' ') name++;

        char *colon = strchr(name, ':');
        if (!colon) continue;

        *colon = '\0';

        if (strcmp(name, interface) == 0) {
            if (sscanf(colon + 1, "%llu %*u %*u %*u %*u %*u %*u %*u %llu",
                       &stats->received_bytes, &stats->sent_bytes) == 2) {
                found = 1;
                break;
            }
        }
    }

    fclose(file);
    return found ? 0 : -1;
}

static const char *monitored_interfaces[] = {"eth0", "eth1", "wlan0"};
#define MONITORED_IF_COUNT (sizeof(monitored_interfaces) / sizeof(monitored_interfaces[0]))

void get_network_speed(double *download, double *upload)
{
    static unsigned long long prev_recv_total = 0;
    static unsigned long long prev_sent_total = 0;
    static struct timespec prev_time = {0};

    unsigned long long recv_total = 0, sent_total = 0;
    int any_found = 0;

    for (int i = 0; i < (int)MONITORED_IF_COUNT; i++) {
        NetworkStats stats;
        if (get_network_stats(monitored_interfaces[i], &stats) == 0) {
            recv_total += stats.received_bytes;
            sent_total += stats.sent_bytes;
            any_found = 1;
        }
    }

    if (!any_found) {
        *download = *upload = -1.0;
        return;
    }

    struct timespec curr_time;
    clock_gettime(CLOCK_MONOTONIC, &curr_time);

    if (prev_recv_total == 0 && prev_sent_total == 0) {
        prev_recv_total = recv_total;
        prev_sent_total = sent_total;
        prev_time = curr_time;
        *download = *upload = 0.0;
        return;
    }

    double time_diff = (curr_time.tv_sec - prev_time.tv_sec) +
                       (curr_time.tv_nsec - prev_time.tv_nsec) / 1e9;

    if (time_diff < 0.1) {
        *download = *upload = 0.0;
        return;
    }

    *download = ((recv_total - prev_recv_total) * 8.0) / (time_diff * 1000000.0);
    *upload   = ((sent_total - prev_sent_total) * 8.0) / (time_diff * 1000000.0);

    prev_recv_total = recv_total;
    prev_sent_total = sent_total;
    prev_time = curr_time;
}

int get_cpu_usage(void)
{
    FILE *file;
    unsigned long long user, nice, system, idle, iowait, irq, softirq;
    unsigned long long total_time, idle_time, total_diff, idle_diff;
    static unsigned long long prev_total = 0, prev_idle = 0;
    int usage = 0;

    file = fopen("/proc/stat", "r");
    if (!file) return -1;

    fscanf(file, "cpu %llu %llu %llu %llu %llu %llu %llu",
           &user, &nice, &system, &idle, &iowait, &irq, &softirq);
    fclose(file);

    total_time = user + nice + system + idle + iowait + irq + softirq;
    idle_time = idle;

    if (prev_total == 0 || prev_idle == 0) {
        prev_total = total_time;
        prev_idle = idle_time;
        return 0;
    }

    total_diff = total_time - prev_total;
    idle_diff  = idle_time - prev_idle;

    if (total_diff > 0) {
        usage = (int)(100.0 * (1.0 - (double)idle_diff / (double)total_diff) + 0.5);
    }

    prev_total = total_time;
    prev_idle = idle_time;
    return usage;
}

int get_cpu_temperature(void)
{
    FILE *file;
    int raw_temp;

    file = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (!file) return -1;

    if (fscanf(file, "%d", &raw_temp) != 1) {
        fclose(file);
        return -1;
    }
    fclose(file);

    return (raw_temp + 50) / 1000;
}

int get_ram_usage(void)
{
    FILE *file = fopen("/proc/meminfo", "r");
    if (!file) return -1;

    unsigned long long mem_total = 0, mem_available = 0;
    unsigned long long mem_free = 0, buffers = 0, cached = 0;
    char key[64];
    unsigned long long value;
    char unit[32];

    while (fscanf(file, "%63s %llu %31s\n", key, &value, unit) == 3) {
        if (strcmp(key, "MemTotal:") == 0)          mem_total = value;
        else if (strcmp(key, "MemAvailable:") == 0)  mem_available = value;
        else if (strcmp(key, "MemFree:") == 0)       mem_free = value;
        else if (strcmp(key, "Buffers:") == 0)       buffers = value;
        else if (strcmp(key, "Cached:") == 0)        cached = value;
    }
    fclose(file);

    if (mem_total == 0) return -1;

    unsigned long long available = mem_available;
    if (available == 0)
        available = mem_free + buffers + cached;
    if (available > mem_total)
        available = mem_total;

    unsigned long long used = mem_total - available;
    int usage = (int)((used * 100ULL) / mem_total);
    if (usage < 0)   usage = 0;
    if (usage > 100)  usage = 100;
    return usage;
}

int get_interface_ip(const char *interface, char *ip_buf, size_t buf_size)
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) return -1;

    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, interface, IFNAMSIZ - 1);

    /* Check if interface is UP and RUNNING */
    if (ioctl(fd, SIOCGIFFLAGS, &ifr) < 0) {
        close(fd);
        return -1;
    }
    if (!(ifr.ifr_flags & IFF_UP) || !(ifr.ifr_flags & IFF_RUNNING)) {
        close(fd);
        return -1;
    }

    /* Get IP address */
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, interface, IFNAMSIZ - 1);
    if (ioctl(fd, SIOCGIFADDR, &ifr) < 0) {
        close(fd);
        return -1;
    }
    close(fd);

    struct sockaddr_in *addr = (struct sockaddr_in *)&ifr.ifr_addr;
    const char *ip = inet_ntoa(addr->sin_addr);
    if (ip && strcmp(ip, "0.0.0.0") != 0) {
        snprintf(ip_buf, buf_size, "%s", ip);
        return 0;
    }
    return -1;
}

/* lv_label_set_text() always invalidates and reallocates, even when the text is
 * unchanged, so labels fed by the 1 Hz timer are only written on a real change. */
static void set_label_text_if_changed(lv_obj_t *label, const char *text)
{
    if (strcmp(lv_label_get_text(label), text) == 0)
        return;
    lv_label_set_text(label, text);
}

void set_app_version(const char *version)
{
    if (version == NULL || version[0] == '\0')
        return;
    snprintf(app_version_str, sizeof(app_version_str), "%s", version);
}

static void update_ui_timer(lv_timer_t *timer)
{
    (void)timer;

    int cpu, ram, temp;
    double down, up;

    /* Update Monitor screen widgets if valid */
    if (guider_ui.Monitor_CPU_Used_Arc && lv_obj_is_valid(guider_ui.Monitor_CPU_Used_Arc)) {
        cpu = cpu_usage;
        ram = ram_usage;
        temp = cpu_temp;
        down = download_speed;
        up = upload_speed;

        lv_arc_set_value(guider_ui.Monitor_CPU_Used_Arc, cpu);
        lv_arc_set_value(guider_ui.Monitor_RAM_Used_Arc, ram);

        char buf[32];

        snprintf(buf, sizeof(buf), "%d", cpu);
        lv_label_set_text(guider_ui.Monitor_CPU_Used_Label, buf);

        snprintf(buf, sizeof(buf), "%d", ram);
        lv_label_set_text(guider_ui.Monitor_RAM_Used_Label, buf);

        snprintf(buf, sizeof(buf), "%d°C", temp);
        lv_label_set_text(guider_ui.Monitor_CPU_Temp_Label, buf);

        if (up >= 0)
            snprintf(buf, sizeof(buf), "%.2f Mb", up);
        else
            snprintf(buf, sizeof(buf), "--");
        lv_label_set_text(guider_ui.Monitor_Net_Up_Label, buf);

        if (down >= 0)
            snprintf(buf, sizeof(buf), "%.2f Mb", down);
        else
            snprintf(buf, sizeof(buf), "--");
        lv_label_set_text(guider_ui.Monitor_Net_Down_Label, buf);
    }

    /* Update Main screen clock */
    if (guider_ui.Main_Clock_Label && lv_obj_is_valid(guider_ui.Main_Clock_Label)) {
        lv_label_set_text(guider_ui.Main_Clock_Label, time_str);
    }

    /* Update Main screen date */
    if (guider_ui.Main_Date_Label && lv_obj_is_valid(guider_ui.Main_Date_Label)) {
        lv_label_set_text(guider_ui.Main_Date_Label, date_str);
    }

    /* Update Main screen weekday */
    if (guider_ui.Main_Week_Label && lv_obj_is_valid(guider_ui.Main_Week_Label)) {
        lv_label_set_text(guider_ui.Main_Week_Label, weekday_str);
    }

    /* Update Main screen eth0 IP */
    if (guider_ui.Main_Eth0_Ipaddr_Label && lv_obj_is_valid(guider_ui.Main_Eth0_Ipaddr_Label)) {
        if (eth0_ip[0] != '\0')
            lv_label_set_text(guider_ui.Main_Eth0_Ipaddr_Label, eth0_ip);
        else
            lv_label_set_text(guider_ui.Main_Eth0_Ipaddr_Label, "N/A");
    }

    /* Update Main screen eth1 IP */
    if (guider_ui.Main_Eth1_Ipaddr_Label && lv_obj_is_valid(guider_ui.Main_Eth1_Ipaddr_Label)) {
        if (eth1_ip[0] != '\0')
            lv_label_set_text(guider_ui.Main_Eth1_Ipaddr_Label, eth1_ip);
        else
            lv_label_set_text(guider_ui.Main_Eth1_Ipaddr_Label, "N/A");
    }

    /* Update Main screen wlan0 IP */
    if (guider_ui.Main_Wlan0_Ipaddr_Label && lv_obj_is_valid(guider_ui.Main_Wlan0_Ipaddr_Label)) {
        if (wlan0_ip[0] != '\0')
            lv_label_set_text(guider_ui.Main_Wlan0_Ipaddr_Label, wlan0_ip);
        else
            lv_label_set_text(guider_ui.Main_Wlan0_Ipaddr_Label, "N/A");
    }

    /* Update network container background based on connection status */
    if (guider_ui.Main_Eth0_Cont && lv_obj_is_valid(guider_ui.Main_Eth0_Cont)) {
        if (eth0_ip[0] != '\0')
            lv_obj_set_style_bg_color(guider_ui.Main_Eth0_Cont, lv_color_hex(0x0080ff), LV_PART_MAIN | LV_STATE_DEFAULT);
        else
            lv_obj_set_style_bg_color(guider_ui.Main_Eth0_Cont, lv_color_hex(0x212324), LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    if (guider_ui.Main_Eth1_Cont && lv_obj_is_valid(guider_ui.Main_Eth1_Cont)) {
        if (eth1_ip[0] != '\0')
            lv_obj_set_style_bg_color(guider_ui.Main_Eth1_Cont, lv_color_hex(0x0080ff), LV_PART_MAIN | LV_STATE_DEFAULT);
        else
            lv_obj_set_style_bg_color(guider_ui.Main_Eth1_Cont, lv_color_hex(0x212324), LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    if (guider_ui.Main_Wlan0_Cont && lv_obj_is_valid(guider_ui.Main_Wlan0_Cont)) {
        if (wlan0_ip[0] != '\0')
            lv_obj_set_style_bg_color(guider_ui.Main_Wlan0_Cont, lv_color_hex(0x0080ff), LV_PART_MAIN | LV_STATE_DEFAULT);
        else
            lv_obj_set_style_bg_color(guider_ui.Main_Wlan0_Cont, lv_color_hex(0x212324), LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    /* Update Version screen app version. The label keeps its gui-guider
     * placeholder until the web UI has pushed its version over ctrl. */
    if (app_version_str[0] != '\0' &&
        guider_ui.Version_App_Version_Label && lv_obj_is_valid(guider_ui.Version_App_Version_Label)) {
        char version_text[sizeof(app_version_str) + 1];
        snprintf(version_text, sizeof(version_text), "v%s", app_version_str);
        set_label_text_if_changed(guider_ui.Version_App_Version_Label, version_text);
    }

    /* Update Version screen hostname */
    if (guider_ui.Version_Hostname_Label && lv_obj_is_valid(guider_ui.Version_Hostname_Label)) {
        set_label_text_if_changed(guider_ui.Version_Hostname_Label, hostname_str);
    }
}

void *run_monitor_loop(void *arg)
{
    (void)arg;

    while (monitor_running) {
        cpu_usage = get_cpu_usage();
        ram_usage = get_ram_usage();
        cpu_temp  = get_cpu_temperature();
        get_network_speed(&download_speed, &upload_speed);
        get_current_time_str(time_str, sizeof(time_str));
        get_current_date_str(date_str, sizeof(date_str));
        get_current_weekday_str(weekday_str, sizeof(weekday_str));

        /* Get IP addresses */
        if (get_interface_ip("eth0", eth0_ip, sizeof(eth0_ip)) != 0)
            eth0_ip[0] = '\0';
        if (get_interface_ip("eth1", eth1_ip, sizeof(eth1_ip)) != 0)
            eth1_ip[0] = '\0';
        if (get_interface_ip("wlan0", wlan0_ip, sizeof(wlan0_ip)) != 0)
            wlan0_ip[0] = '\0';
        if (gethostname(hostname_str, sizeof(hostname_str)) != 0 || hostname_str[0] == '\0')
            snprintf(hostname_str, sizeof(hostname_str), "Unknown");

        sleep(1);
    }
    return NULL;
}

void startupdate(void)
{
    /* Read hostname once before thread starts */
    if (gethostname(hostname_str, sizeof(hostname_str)) != 0 || hostname_str[0] == '\0')
        snprintf(hostname_str, sizeof(hostname_str), "Unknown");

    monitor_running = 1;

    pthread_t monitor_thread;
    pthread_create(&monitor_thread, NULL, run_monitor_loop, NULL);
    pthread_detach(monitor_thread);

    lv_timer_create(update_ui_timer, 1000, NULL);
}

void stopupdate(void)
{
    monitor_running = 0;
}
