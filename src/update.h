#ifndef UPDATE_H
#define UPDATE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "gui_guider.h"

typedef struct {
    unsigned long long received_bytes;
    unsigned long long sent_bytes;
} NetworkStats;

extern int cpu_usage;
extern int ram_usage;
extern int cpu_temp;
extern double download_speed;
extern double upload_speed;
extern char time_str[16];
extern char date_str[16];
extern char weekday_str[16];
extern char eth0_ip[64];
extern char eth1_ip[64];
extern char wlan0_ip[64];
extern char hostname_str[64];
extern char app_version_str[64];

int get_cpu_usage(void);
int get_cpu_temperature(void);
int get_ram_usage(void);
void get_current_time_str(char *buffer, size_t size);
void get_current_date_str(char *buffer, size_t size);
void get_current_weekday_str(char *buffer, size_t size);
void get_network_speed(double *download, double *upload);
int get_interface_ip(const char *interface, char *ip_buf, size_t buf_size);

/**
 * @brief Override the version shown on the Version screen
 * @param version Version string without the leading 'v' (e.g. "1.2.3")
 */
void set_app_version(const char *version);

void startupdate(void);
void stopupdate(void);
void *run_monitor_loop(void *arg);

#endif /* UPDATE_H */
