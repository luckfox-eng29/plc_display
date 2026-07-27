#include <stdio.h>
#include <string.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include <fcntl.h>
#include "frozen.h"
#include "gui_guider.h"
#include "ui_index.h"
#include "update.h"
#include "lvgl/lvgl.h"

struct sockaddr_un addr;
int ctrl_client_fd = 0;
pthread_t ctrl_thread;

// Forward declarations
static void *handle_client(void *arg);
static void handle_lvgl_call(const int seq, const char *method, const char *json, size_t json_len);

/**
 * @brief Write a JSON response to the ctrl client
 */
static int write_json(int fd, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    char *json_str = json_vasprintf(fmt, ap);
    va_end(ap);
    if (json_str == NULL)
    {
        return -1;
    }
    int written = write(fd, json_str, strlen(json_str));
    free(json_str);
    return written;
}

/**
 * @brief Write a JSON error response to the ctrl client
 */
static int write_json_error(int fd, int seq, const char *error)
{
    return write_json(fd, "{seq: %d, error: %Q, errno: %d}", seq, error, errno);
}

/**
 * @brief Handle LVGL-related ctrl actions
 */
static void handle_lvgl_call(const int seq, const char *method, const char *json, size_t json_len)
{
    lv_obj_t *obj = NULL;
    char *obj_name = NULL;

    if (strcmp(method, "lv_disp_set_rotation") == 0)
    {
        char *rotation = NULL;
        if (json_scanf(json, json_len, "{params: {rotation: %Q}}", &rotation) > 0)
        {
            lv_disp_rot_t rot;
            if (strcmp(rotation, "0") == 0)
            {
                rot = LV_DISP_ROT_NONE;
            }
            else if (strcmp(rotation, "90") == 0)
            {
                rot = LV_DISP_ROT_90;
            }
            else if (strcmp(rotation, "180") == 0)
            {
                rot = LV_DISP_ROT_180;
            }
            else if (strcmp(rotation, "270") == 0)
            {
                rot = LV_DISP_ROT_270;
            }
            else
            {
                rot = -1;
            }
            free(rotation);
            if (rot != -1)
            {
                lv_disp_set_rotation(NULL, rot);
                write_json(ctrl_client_fd, "{seq: %d}", seq);
            }
            else
            {
                write_json_error(ctrl_client_fd, seq, "illegal rotation value");
            }
        }
        else
        {
            write_json_error(ctrl_client_fd, seq, "missing rotation parameter");
        }
    }
    else if (json_scanf(json, json_len, "{params: {obj: %Q}}", &obj_name) > 0)
    {
        obj = ui_get_obj(obj_name);

        if (obj == NULL)
        {
            write_json_error(ctrl_client_fd, seq, "object not found");
            free(obj_name);
            return;
        }

        if (strcmp(method, "lv_scr_load") == 0)
        {
            if (lv_scr_act() != obj)
            {
                lv_scr_load(obj);
            }
            write_json(ctrl_client_fd, "{seq: %d}", seq);
        }
        else if (strcmp(method, "lv_label_set_text") == 0)
        {
            char *text = NULL;
            if (json_scanf(json, json_len, "{params: {text: %Q}}", &text) > 0)
            {
                lv_label_set_text(obj, text);
                free(text);
                write_json(ctrl_client_fd, "{seq: %d}", seq);
            }
            else
            {
                write_json_error(ctrl_client_fd, seq, "missing text parameter");
            }
        }
        else if (strcmp(method, "lv_obj_set_state") == 0)
        {
            char *lv_state = NULL;
            if (json_scanf(json, json_len, "{params: {state: %Q}}", &lv_state) > 0)
            {
                // Handle custom states if needed
                free(lv_state);
                write_json(ctrl_client_fd, "{seq: %d}", seq);
            }
            else
            {
                write_json_error(ctrl_client_fd, seq, "missing state parameter");
            }
        }
        else if (strcmp(method, "lv_obj_add_flag") == 0)
        {
            char *flag = NULL;
            if (json_scanf(json, json_len, "{params: {flag: %Q}}", &flag) > 0)
            {
                if (strcmp(flag, "LV_OBJ_FLAG_HIDDEN") == 0)
                {
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                }
                free(flag);
                write_json(ctrl_client_fd, "{seq: %d}", seq);
            }
            else
            {
                write_json_error(ctrl_client_fd, seq, "missing flag parameter");
            }
        }
        else if (strcmp(method, "lv_obj_clear_flag") == 0)
        {
            char *flag = NULL;
            if (json_scanf(json, json_len, "{params: {flag: %Q}}", &flag) > 0)
            {
                if (strcmp(flag, "LV_OBJ_FLAG_HIDDEN") == 0)
                {
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
                }
                free(flag);
                write_json(ctrl_client_fd, "{seq: %d}", seq);
            }
            else
            {
                write_json_error(ctrl_client_fd, seq, "missing flag parameter");
            }
        }
        else if (strcmp(method, "lv_obj_set_style_bg_color") == 0)
        {
            char *color = NULL;
            if (json_scanf(json, json_len, "{params: {color: %Q}}", &color) > 0)
            {
                uint32_t color_hex = strtol(color, NULL, 16);
                lv_obj_set_style_bg_color(obj, lv_color_hex(color_hex), LV_PART_MAIN | LV_STATE_DEFAULT);
                free(color);
                write_json(ctrl_client_fd, "{seq: %d}", seq);
            }
            else
            {
                write_json_error(ctrl_client_fd, seq, "missing color parameter");
            }
        }
        else if (strcmp(method, "lv_obj_fade_in") == 0)
        {
            int time = 0;
            if (json_scanf(json, json_len, "{params: {time: %d}}", &time) > 0)
            {
                lv_obj_fade_in(obj, time, 0);
                write_json(ctrl_client_fd, "{seq: %d}", seq);
            }
            else
            {
                write_json_error(ctrl_client_fd, seq, "missing time parameter");
            }
        }
        else if (strcmp(method, "lv_obj_fade_out") == 0)
        {
            int time = 0;
            if (json_scanf(json, json_len, "{params: {time: %d}}", &time) > 0)
            {
                lv_obj_fade_out(obj, time, 0);
                write_json(ctrl_client_fd, "{seq: %d}", seq);
            }
            else
            {
                write_json_error(ctrl_client_fd, seq, "missing time parameter");
            }
        }
        else
        {
            write_json_error(ctrl_client_fd, seq, "unknown lvgl method");
        }

        free(obj_name);
    }
    else
    {
        printf("[ctrl] handle_lvgl_call: No object name provided for method %s\n", method);
        write_json_error(ctrl_client_fd, seq, "missing object name");
    }
}

/**
 * @brief Handle ctrl client connection - reads and dispatches JSON messages
 */
static void *handle_client(void *arg)
{
    const int BUF_SIZE = 1024;
    char buf_in[BUF_SIZE];

    while (1)
    {
        ssize_t n = read(ctrl_client_fd, buf_in, BUF_SIZE);
        if (n > 0)
        {
            buf_in[n] = '\0';
            char *method = NULL;
            int32_t seq = -1;
            if (json_scanf(buf_in, n, "{action: %Q, seq: %d}", &method, &seq) > 0)
            {
                printf("[ctrl] Received action: %s, seq: %d\n", method, seq);

                // Dispatch based on method prefix
                if (strncmp("lv_", method, 3) == 0)
                {
                    handle_lvgl_call(seq, method, buf_in, n);
                }
                else if (strcmp("set_app_version", method) == 0)
                {
                    char *version = NULL;
                    if (json_scanf(buf_in, n, "{params: {version: %Q}}", &version) > 0)
                    {
                        set_app_version(version);
                        free(version);
                        if (seq > 0)
                        {
                            write_json(ctrl_client_fd, "{seq: %d}", seq);
                        }
                    }
                    else
                    {
                        write_json_error(ctrl_client_fd, seq, "missing version parameter");
                    }
                }
                else if (strcmp("ui_set_text", method) == 0)
                {
                    char *name = NULL;
                    char *text = NULL;
                    if (json_scanf(buf_in, n, "{params: {obj: %Q, text: %Q}}", &name, &text) > 0)
                    {
                        lv_obj_t *obj = ui_get_obj(name);
                        if (obj != NULL)
                        {
                            lv_label_set_text(obj, text);
                        }
                        free(name);
                        free(text);
                    }
                    if (seq > 0)
                    {
                        write_json(ctrl_client_fd, "{seq: %d}", seq);
                    }
                }
                else if (strcmp("set_timezone", method) == 0)
                {
                    char *timezone = NULL;
                    if (json_scanf(buf_in, n, "{params: {timezone: %Q}}", &timezone) > 0)
                    {
                        setenv("TZ", timezone, 1);
                        tzset();
                        free(timezone);
                        write_json(ctrl_client_fd, "{seq: %d}", seq);
                    }
                    else
                    {
                        write_json_error(ctrl_client_fd, seq, "invalid timezone");
                    }
                }
                else
                {
                    printf("[ctrl] Unknown method: %s\n", method);
                    write_json_error(ctrl_client_fd, seq, "unknown method");
                }

                free(method);
            }
            else
            {
                printf("[ctrl] Failed to parse JSON message\n");
            }
        }
        else if (n == 0)
        {
            // EOF - client disconnected
            printf("[ctrl] Client disconnected (EOF)\n");
            break;
        }
        else
        {
            perror("[ctrl] Error reading from client");
            break;
        }
    }

    close(ctrl_client_fd);
    ctrl_client_fd = 0;
    return NULL;
}

/**
 * @brief Connect to the ctrl socket server
 */
int connect_ctrl_client(const char *path)
{
    int client_fd = socket(AF_UNIX, SOCK_SEQPACKET, 0);
    if (client_fd == -1)
    {
        perror("[ctrl] Cannot create socket");
        return -1;
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);

    if (connect(client_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("[ctrl] Cannot connect to ctrl server");
        close(client_fd);
        return -1;
    }

    ctrl_client_fd = client_fd;
    printf("[ctrl] Connected to %s\n", path);
    return 0;
}

/**
 * @brief Start the ctrl loop thread
 */
void start_ctrl_loop()
{
    if (pthread_create(&ctrl_thread, NULL, handle_client, NULL) != 0)
    {
        perror("[ctrl] Failed to create ctrl_thread");
    }
    else
    {
        printf("[ctrl] Ctrl loop started\n");
    }
}

/**
 * @brief Stop the ctrl loop and close the socket
 */
void stop_ctrl_loop()
{
    if (ctrl_client_fd > 0)
    {
        if (shutdown(ctrl_client_fd, SHUT_RDWR) == -1)
        {
            perror("[ctrl] Error shutting down client socket");
        }
        if (close(ctrl_client_fd) == -1)
        {
            perror("[ctrl] Error closing client socket");
        }
        ctrl_client_fd = 0;
    }
    printf("[ctrl] Ctrl loop stopped\n");
}
