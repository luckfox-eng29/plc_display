#ifndef UI_INDEX_H
#define UI_INDEX_H

#include "gui_guider.h"

typedef struct {
    const char *name;
    lv_obj_t **obj; // Pointer to the object pointer, as the object pointer is only populated after the ui is initialized
} ui_obj_map;

extern ui_obj_map ui_objects[];
extern const int ui_objects_size;

/**
 * @brief Get LVGL object by name
 * @param name Object name string
 * @return Pointer to the object, or NULL if not found
 */
lv_obj_t *ui_get_obj(const char *name);

#endif // UI_INDEX_H
