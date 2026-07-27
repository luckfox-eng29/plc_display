// This file was generated manually to map UI object names to their pointers
#include "ui_index.h"
#include <string.h>

ui_obj_map ui_objects[] = {
    // Main screen
    {"Main", &guider_ui.Main},
    {"Main_Logo_Img", &guider_ui.Main_Logo_Img},
    {"Main_Clock_Label", &guider_ui.Main_Clock_Label},
    {"Main_Date_Label", &guider_ui.Main_Date_Label},
    {"Main_Week_Label", &guider_ui.Main_Week_Label},
    {"Main_Eth0_Cont", &guider_ui.Main_Eth0_Cont},
    {"Main_Eth0_Img", &guider_ui.Main_Eth0_Img},
    {"Main_Eth0_Headline", &guider_ui.Main_Eth0_Headline},
    {"Main_Eth0_Ipaddr_Label", &guider_ui.Main_Eth0_Ipaddr_Label},
    {"Main_Eth1_Cont", &guider_ui.Main_Eth1_Cont},
    {"Main_Eth1_Ipaddr_Label", &guider_ui.Main_Eth1_Ipaddr_Label},
    {"Main_Eth1_Headline", &guider_ui.Main_Eth1_Headline},
    {"Main_Eth1_Img", &guider_ui.Main_Eth1_Img},
    {"Main_Wlan0_Cont", &guider_ui.Main_Wlan0_Cont},
    {"Main_Wlan0_Ipaddr_Label", &guider_ui.Main_Wlan0_Ipaddr_Label},
    {"Main_Wlan0_Headline", &guider_ui.Main_Wlan0_Headline},
    {"Main_Wlan0_Img", &guider_ui.Main_Wlan0_Img},

    // Version screen
    {"Version", &guider_ui.Version},
    {"Version_Version_cont", &guider_ui.Version_Version_cont},
    {"Version_Logo_Img", &guider_ui.Version_Logo_Img},
    {"Version_Hostname_Label", &guider_ui.Version_Hostname_Label},
    {"Version_Hostname_Headline", &guider_ui.Version_Hostname_Headline},
    {"Version_App_Version_Label", &guider_ui.Version_App_Version_Label},
    {"Version_App_Version_Headline", &guider_ui.Version_App_Version_Headline},
    {"Version_Line", &guider_ui.Version_Line},

    // Monitor screen
    {"Monitor", &guider_ui.Monitor},
    {"Monitor_Net_Cont", &guider_ui.Monitor_Net_Cont},
    {"Monitor_Net_Img", &guider_ui.Monitor_Net_Img},
    {"Monitor_Net_Down_Label", &guider_ui.Monitor_Net_Down_Label},
    {"Monitor_Net_Up_Label", &guider_ui.Monitor_Net_Up_Label},
    {"Monitor_Net_Up_Img", &guider_ui.Monitor_Net_Up_Img},
    {"Monitor_Net_Down_Img", &guider_ui.Monitor_Net_Down_Img},
    {"Monitor_CPU_Temp_Cont", &guider_ui.Monitor_CPU_Temp_Cont},
    {"Monitor_CPU_Temp_Label", &guider_ui.Monitor_CPU_Temp_Label},
    {"Monitor_CPU_Temp_Headline", &guider_ui.Monitor_CPU_Temp_Headline},
    {"Monitor_RAM_Used_Cont", &guider_ui.Monitor_RAM_Used_Cont},
    {"Monitor_RAM_Used_Headline", &guider_ui.Monitor_RAM_Used_Headline},
    {"Monitor_RAM_Used_Arc", &guider_ui.Monitor_RAM_Used_Arc},
    {"Monitor_RAM_Used_Label", &guider_ui.Monitor_RAM_Used_Label},
    {"Monitor_CPU_Used_Cont", &guider_ui.Monitor_CPU_Used_Cont},
    {"Monitor_CPU_Used_Headline", &guider_ui.Monitor_CPU_Used_Headline},
    {"Monitor_CPU_Used_Arc", &guider_ui.Monitor_CPU_Used_Arc},
    {"Monitor_CPU_Used_Label", &guider_ui.Monitor_CPU_Used_Label},
};

const int ui_objects_size = sizeof(ui_objects) / sizeof(ui_objects[0]);

lv_obj_t *ui_get_obj(const char *name) {
    for (int i = 0; i < ui_objects_size; i++) {
        if (strcmp(ui_objects[i].name, name) == 0) {
            return *ui_objects[i].obj;
        }
    }
    return NULL;
}
