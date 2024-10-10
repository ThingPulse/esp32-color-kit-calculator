#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: GreyButtons
lv_style_t *get_style_grey_buttons_MAIN_DEFAULT();
void add_style_grey_buttons(lv_obj_t *obj);
void remove_style_grey_buttons(lv_obj_t *obj);

// Style: OrangeButtons
lv_style_t *get_style_orange_buttons_MAIN_DEFAULT();
void add_style_orange_buttons(lv_obj_t *obj);
void remove_style_orange_buttons(lv_obj_t *obj);

// Style: DarkButtons
lv_style_t *get_style_dark_buttons_MAIN_DEFAULT();
void add_style_dark_buttons(lv_obj_t *obj);
void remove_style_dark_buttons(lv_obj_t *obj);



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/