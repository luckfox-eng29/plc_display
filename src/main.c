#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include "update.h"
#include "ctrl.h"
#include <pthread.h>

lv_ui guider_ui;

int g_display_width = 170;  // Rotated width (was 320)
int g_display_height = 320; // Rotated height (was 170)


/* PLC_DISPLAY_VERSION is defined by CMakeLists.txt, the single place that owns
 * the version (see the PLC_DISPLAY_VERSION cache variable there). */

int main(int argc, char *argv[]) {
    /* --version / -v report the build stamp and exit before touching the
     * framebuffer, so scripts and the web UI can query it cheaply. */
    if (argc > 1 && (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0)) {
        printf("%s\n", PLC_DISPLAY_VERSION);
        return 0;
    }

    /* The web UI owns our stdout over a pipe, which makes glibc block buffer it
     * and hold log lines back. Force line buffering so they arrive as written. */
    setvbuf(stdout, NULL, _IOLBF, 0);

    int disp_width = g_display_width;
    int disp_height = g_display_height;
    const int disp_buf_size = disp_width * disp_height / 2;
 
    /*LittlevGL init*/
    lv_init();

    /*Linux frame buffer device init*/
    fbdev_init();
    
    /*A small buffer for LittlevGL to draw the screen's content*/
    lv_color_t buf0[disp_buf_size];
    lv_color_t buf1[disp_buf_size];

    /*Initialize a descriptor for the buffer*/
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf0, buf1, disp_buf_size);

    /*Initialize and register a display driver*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf   = &disp_buf;
    disp_drv.flush_cb   = fbdev_flush;
    disp_drv.hor_res    = g_display_width;
    disp_drv.ver_res    = g_display_height;
    disp_drv.rotated = LV_DISP_ROT_270;
    disp_drv.sw_rotate = true;
    lv_disp_drv_register(&disp_drv);

    // Get display handle and set rotation
    //lv_disp_t *disp = lv_disp_get_default();
    //lv_disp_set_rotation(disp, LV_DISP_ROT_270);  // Counter-clockwise 90°

    evdev_init();
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv); /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;

    /*This function will be called periodically (by the library) to get the mouse position and state*/
    indev_drv.read_cb = evdev_read;
    lv_indev_drv_register(&indev_drv);

    /*Create a Demo*/
    
    /*Create a GUI-Guider app */ 
    setup_ui(&guider_ui); 
    //custom_init(&guider_ui);
    startupdate();

    // Connect to ctrl socket and start ctrl loop
    if (connect_ctrl_client("/var/run/kvm_lyra_plc_display.sock") != 0)
    {
        printf("[main] Warning: Cannot connect to ctrl server, ctrl actions disabled\n");
    }
    else
    {
        start_ctrl_loop();
        printf("[main] Ctrl loop started\n");
    }

    /*Handle LitlevGL tasks (tickless mode)*/
    while(1) {
        lv_timer_handler();
        usleep(5000);
    } 

    return 0; 
}



/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}

