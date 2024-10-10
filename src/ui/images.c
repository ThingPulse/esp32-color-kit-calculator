#include "images.h"

const ext_img_desc_t images[1] = {
    0
};
const lv_img_dsc_t img_undefined = {
    .header.always_zero = 0,
    .header.w = 0,
    .header.h = 0,
    .header.cf = LV_IMG_CF_UNKNOWN,
    .data_size = 0,
    .data = NULL,
};
