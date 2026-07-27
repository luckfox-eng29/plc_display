/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_Main(lv_ui *ui)
{
    //Write codes Main
    ui->Main = lv_obj_create(NULL);
    lv_obj_set_size(ui->Main, 320, 170);
    lv_obj_set_scrollbar_mode(ui->Main, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->Main, LV_OBJ_FLAG_SCROLLABLE);

    //Write style for Main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Main, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Main, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Main, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Main_Logo_Img
    ui->Main_Logo_Img = lv_img_create(ui->Main);
    lv_obj_add_flag(ui->Main_Logo_Img, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Main_Logo_Img, &_LOGO_alpha_64x64);
    lv_img_set_pivot(ui->Main_Logo_Img, 50,50);
    lv_img_set_angle(ui->Main_Logo_Img, 0);
    lv_obj_set_pos(ui->Main_Logo_Img, 48, 10);
    lv_obj_set_size(ui->Main_Logo_Img, 64, 64);

    //Write style for Main_Logo_Img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Main_Logo_Img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Main_Logo_Img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Main_Logo_Img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Main_Logo_Img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Main_Clock_Label
    ui->Main_Clock_Label = lv_label_create(ui->Main);
    lv_label_set_text(ui->Main_Clock_Label, "00:00");
    lv_label_set_long_mode(ui->Main_Clock_Label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Main_Clock_Label, 15, 76);
    lv_obj_set_size(ui->Main_Clock_Label, 130, 48);

    //Write style for Main_Clock_Label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Main_Clock_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Main_Clock_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Main_Clock_Label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Main_Clock_Label, &lv_font_Alatsi_Regular_48, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Main_Clock_Label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Main_Clock_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Main_Clock_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Main_Clock_Label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Main_Clock_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Main_Clock_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Main_Clock_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Main_Clock_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Main_Clock_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Main_Clock_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Main_Date_Label
    ui->Main_Date_Label = lv_label_create(ui->Main);
    lv_label_set_text(ui->Main_Date_Label, "0000-00-00 ");
    lv_label_set_long_mode(ui->Main_Date_Label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Main_Date_Label, 32, 130);
    lv_obj_set_size(ui->Main_Date_Label, 96, 12);

    //Write style for Main_Date_Label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Main_Date_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Main_Date_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Main_Date_Label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Main_Date_Label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Main_Date_Label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Main_Date_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Main_Date_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Main_Date_Label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Main_Date_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Main_Date_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Main_Date_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Main_Date_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Main_Date_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Main_Date_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Main_Week_Label
    ui->Main_Week_Label = lv_label_create(ui->Main);
    lv_label_set_text(ui->Main_Week_Label, "Wednesday");
    lv_label_set_long_mode(ui->Main_Week_Label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Main_Week_Label, 32, 148);
    lv_obj_set_size(ui->Main_Week_Label, 96, 12);

    //Write style for Main_Week_Label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Main_Week_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Main_Week_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Main_Week_Label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Main_Week_Label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Main_Week_Label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Main_Week_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Main_Week_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Main_Week_Label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Main_Week_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Main_Week_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Main_Week_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Main_Week_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Main_Week_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Main_Week_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Main_Eth0_Cont
    ui->Main_Eth0_Cont = lv_obj_create(ui->Main);
    lv_obj_set_pos(ui->Main_Eth0_Cont, 160, 10);
    lv_obj_set_size(ui->Main_Eth0_Cont, 150, 46);
    lv_obj_set_scrollbar_mode(ui->Main_Eth0_Cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->Main_Eth0_Cont, LV_OBJ_FLAG_SCROLLABLE);

    //Write style for Main_Eth0_Cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Main_Eth0_Cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Main_Eth0_Cont, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Main_Eth0_Cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Main_Eth0_Cont, lv_color_hex(0x212324), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Main_Eth0_Cont, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Main_Eth0_Cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Main_Eth0_Cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Main_Eth0_Cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Main_Eth0_Cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Main_Eth0_Cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Main_Eth0_Img
    ui->Main_Eth0_Img = lv_img_create(ui->Main_Eth0_Cont);
    lv_obj_add_flag(ui->Main_Eth0_Img, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Main_Eth0_Img, &_eth0_alpha_24x24);
    lv_img_set_pivot(ui->Main_Eth0_Img, 50,50);
    lv_img_set_angle(ui->Main_Eth0_Img, 0);
    lv_obj_set_pos(ui->Main_Eth0_Img, 10, 6);
    lv_obj_set_size(ui->Main_Eth0_Img, 24, 24);

    //Write style for Main_Eth0_Img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Main_Eth0_Img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Main_Eth0_Img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Main_Eth0_Img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Main_Eth0_Img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Main_Eth0_Headline
    ui->Main_Eth0_Headline = lv_label_create(ui->Main_Eth0_Cont);
    lv_label_set_text(ui->Main_Eth0_Headline, "eth0");
    lv_label_set_long_mode(ui->Main_Eth0_Headline, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Main_Eth0_Headline, 2, 30);
    lv_obj_set_size(ui->Main_Eth0_Headline, 40, 10);

    //Write style for Main_Eth0_Headline, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Main_Eth0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Main_Eth0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Main_Eth0_Headline, lv_color_hex(0x9013fe), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Main_Eth0_Headline, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Main_Eth0_Headline, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Main_Eth0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Main_Eth0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Main_Eth0_Headline, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Main_Eth0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Main_Eth0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Main_Eth0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Main_Eth0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Main_Eth0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Main_Eth0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Main_Eth0_Ipaddr_Label
    ui->Main_Eth0_Ipaddr_Label = lv_label_create(ui->Main_Eth0_Cont);
    lv_label_set_text(ui->Main_Eth0_Ipaddr_Label, "000.000.000.000");
    lv_label_set_long_mode(ui->Main_Eth0_Ipaddr_Label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Main_Eth0_Ipaddr_Label, 40, 16);
    lv_obj_set_size(ui->Main_Eth0_Ipaddr_Label, 110, 14);

    //Write style for Main_Eth0_Ipaddr_Label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Main_Eth0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Main_Eth0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Main_Eth0_Ipaddr_Label, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Main_Eth0_Ipaddr_Label, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Main_Eth0_Ipaddr_Label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Main_Eth0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Main_Eth0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Main_Eth0_Ipaddr_Label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Main_Eth0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Main_Eth0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Main_Eth0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Main_Eth0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Main_Eth0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Main_Eth0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Main_Eth1_Cont
    ui->Main_Eth1_Cont = lv_obj_create(ui->Main);
    lv_obj_set_pos(ui->Main_Eth1_Cont, 160, 62);
    lv_obj_set_size(ui->Main_Eth1_Cont, 150, 46);
    lv_obj_set_scrollbar_mode(ui->Main_Eth1_Cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->Main_Eth1_Cont, LV_OBJ_FLAG_SCROLLABLE);

    //Write style for Main_Eth1_Cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Main_Eth1_Cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Main_Eth1_Cont, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Main_Eth1_Cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Main_Eth1_Cont, lv_color_hex(0x212324), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Main_Eth1_Cont, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Main_Eth1_Cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Main_Eth1_Cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Main_Eth1_Cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Main_Eth1_Cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Main_Eth1_Cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Main_Eth1_Ipaddr_Label
    ui->Main_Eth1_Ipaddr_Label = lv_label_create(ui->Main_Eth1_Cont);
    lv_label_set_text(ui->Main_Eth1_Ipaddr_Label, "000.000.000.000");
    lv_label_set_long_mode(ui->Main_Eth1_Ipaddr_Label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Main_Eth1_Ipaddr_Label, 40, 16);
    lv_obj_set_size(ui->Main_Eth1_Ipaddr_Label, 110, 14);

    //Write style for Main_Eth1_Ipaddr_Label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Main_Eth1_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Main_Eth1_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Main_Eth1_Ipaddr_Label, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Main_Eth1_Ipaddr_Label, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Main_Eth1_Ipaddr_Label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Main_Eth1_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Main_Eth1_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Main_Eth1_Ipaddr_Label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Main_Eth1_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Main_Eth1_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Main_Eth1_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Main_Eth1_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Main_Eth1_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Main_Eth1_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Main_Eth1_Headline
    ui->Main_Eth1_Headline = lv_label_create(ui->Main_Eth1_Cont);
    lv_label_set_text(ui->Main_Eth1_Headline, "eth1");
    lv_label_set_long_mode(ui->Main_Eth1_Headline, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Main_Eth1_Headline, 2, 30);
    lv_obj_set_size(ui->Main_Eth1_Headline, 40, 10);

    //Write style for Main_Eth1_Headline, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Main_Eth1_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Main_Eth1_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Main_Eth1_Headline, lv_color_hex(0x417505), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Main_Eth1_Headline, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Main_Eth1_Headline, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Main_Eth1_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Main_Eth1_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Main_Eth1_Headline, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Main_Eth1_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Main_Eth1_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Main_Eth1_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Main_Eth1_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Main_Eth1_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Main_Eth1_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Main_Eth1_Img
    ui->Main_Eth1_Img = lv_img_create(ui->Main_Eth1_Cont);
    lv_obj_add_flag(ui->Main_Eth1_Img, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Main_Eth1_Img, &_eth1_alpha_24x24);
    lv_img_set_pivot(ui->Main_Eth1_Img, 50,50);
    lv_img_set_angle(ui->Main_Eth1_Img, 0);
    lv_obj_set_pos(ui->Main_Eth1_Img, 10, 6);
    lv_obj_set_size(ui->Main_Eth1_Img, 24, 24);

    //Write style for Main_Eth1_Img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Main_Eth1_Img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Main_Eth1_Img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Main_Eth1_Img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Main_Eth1_Img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Main_Wlan0_Cont
    ui->Main_Wlan0_Cont = lv_obj_create(ui->Main);
    lv_obj_set_pos(ui->Main_Wlan0_Cont, 160, 114);
    lv_obj_set_size(ui->Main_Wlan0_Cont, 150, 46);
    lv_obj_set_scrollbar_mode(ui->Main_Wlan0_Cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->Main_Wlan0_Cont, LV_OBJ_FLAG_SCROLLABLE);

    //Write style for Main_Wlan0_Cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Main_Wlan0_Cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Main_Wlan0_Cont, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Main_Wlan0_Cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Main_Wlan0_Cont, lv_color_hex(0x212324), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Main_Wlan0_Cont, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Main_Wlan0_Cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Main_Wlan0_Cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Main_Wlan0_Cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Main_Wlan0_Cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Main_Wlan0_Cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Main_Wlan0_Ipaddr_Label
    ui->Main_Wlan0_Ipaddr_Label = lv_label_create(ui->Main_Wlan0_Cont);
    lv_label_set_text(ui->Main_Wlan0_Ipaddr_Label, "000.000.000.000");
    lv_label_set_long_mode(ui->Main_Wlan0_Ipaddr_Label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Main_Wlan0_Ipaddr_Label, 40, 16);
    lv_obj_set_size(ui->Main_Wlan0_Ipaddr_Label, 110, 14);

    //Write style for Main_Wlan0_Ipaddr_Label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Main_Wlan0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Main_Wlan0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Main_Wlan0_Ipaddr_Label, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Main_Wlan0_Ipaddr_Label, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Main_Wlan0_Ipaddr_Label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Main_Wlan0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Main_Wlan0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Main_Wlan0_Ipaddr_Label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Main_Wlan0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Main_Wlan0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Main_Wlan0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Main_Wlan0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Main_Wlan0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Main_Wlan0_Ipaddr_Label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Main_Wlan0_Headline
    ui->Main_Wlan0_Headline = lv_label_create(ui->Main_Wlan0_Cont);
    lv_label_set_text(ui->Main_Wlan0_Headline, "wlan0");
    lv_label_set_long_mode(ui->Main_Wlan0_Headline, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Main_Wlan0_Headline, 2, 30);
    lv_obj_set_size(ui->Main_Wlan0_Headline, 40, 10);

    //Write style for Main_Wlan0_Headline, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Main_Wlan0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Main_Wlan0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Main_Wlan0_Headline, lv_color_hex(0x00FF47), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Main_Wlan0_Headline, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Main_Wlan0_Headline, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Main_Wlan0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Main_Wlan0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Main_Wlan0_Headline, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Main_Wlan0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Main_Wlan0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Main_Wlan0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Main_Wlan0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Main_Wlan0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Main_Wlan0_Headline, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Main_Wlan0_Img
    ui->Main_Wlan0_Img = lv_img_create(ui->Main_Wlan0_Cont);
    lv_obj_add_flag(ui->Main_Wlan0_Img, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Main_Wlan0_Img, &_wlan0_alpha_24x24);
    lv_img_set_pivot(ui->Main_Wlan0_Img, 50,50);
    lv_img_set_angle(ui->Main_Wlan0_Img, 0);
    lv_obj_set_pos(ui->Main_Wlan0_Img, 10, 6);
    lv_obj_set_size(ui->Main_Wlan0_Img, 24, 24);

    //Write style for Main_Wlan0_Img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Main_Wlan0_Img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->Main_Wlan0_Img, lv_color_hex(0x00FF47), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Main_Wlan0_Img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Main_Wlan0_Img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Main_Wlan0_Img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of Main.


    //Update current screen layout.
    lv_obj_update_layout(ui->Main);

    //Init events for screen.
    events_init_Main(ui);
}
