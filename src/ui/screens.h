#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *ac;
    lv_obj_t *add;
    lv_obj_t *divide;
    lv_obj_t *dot;
    lv_obj_t *eight;
    lv_obj_t *equal;
    lv_obj_t *five;
    lv_obj_t *four;
    lv_obj_t *minus;
    lv_obj_t *multiply;
    lv_obj_t *negate;
    lv_obj_t *nine;
    lv_obj_t *one;
    lv_obj_t *percentage;
    lv_obj_t *seven;
    lv_obj_t *six;
    lv_obj_t *three;
    lv_obj_t *two;
    lv_obj_t *zero;
    lv_obj_t *label;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
};

void create_screen_main();
void tick_screen_main();

void create_screens();
void tick_screen(int screen_index);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/