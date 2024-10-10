#include "styles.h"
#include "images.h"
#include "fonts.h"

//
// Style: GreyButtons
//

void init_style_grey_buttons_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff2196f3));
};

lv_style_t *get_style_grey_buttons_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_grey_buttons_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_grey_buttons(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_grey_buttons_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_grey_buttons(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_grey_buttons_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: OrangeButtons
//

void init_style_orange_buttons_MAIN_DEFAULT(lv_style_t *style) {
    init_style_grey_buttons_MAIN_DEFAULT(style);
    
    lv_style_set_bg_color(style, lv_color_hex(0xffa5a5a5));
    lv_style_set_text_color(style, lv_color_hex(0xff000000));
    lv_style_set_radius(style, 25);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_text_font(style, &lv_font_montserrat_16);
    lv_style_set_bg_img_src(style, &img_undefined);
};

lv_style_t *get_style_orange_buttons_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_orange_buttons_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_orange_buttons(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_orange_buttons_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_orange_buttons(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_orange_buttons_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: DarkButtons
//

void init_style_dark_buttons_MAIN_DEFAULT(lv_style_t *style) {
    init_style_grey_buttons_MAIN_DEFAULT(style);
    
    lv_style_set_bg_color(style, lv_color_hex(0xffa5a5a5));
    lv_style_set_text_color(style, lv_color_hex(0xff000000));
    lv_style_set_radius(style, 25);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_text_font(style, &lv_font_montserrat_16);
    lv_style_set_bg_img_src(style, &img_undefined);
};

lv_style_t *get_style_dark_buttons_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_dark_buttons_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_dark_buttons(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_dark_buttons_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_dark_buttons(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_dark_buttons_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_grey_buttons,
        add_style_orange_buttons,
        add_style_dark_buttons,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_grey_buttons,
        remove_style_orange_buttons,
        remove_style_dark_buttons,
    };
    remove_style_funcs[styleIndex](obj);
}

