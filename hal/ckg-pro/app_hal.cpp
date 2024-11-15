//#define LGFX_AUTODETECT
//#include <LGFX_AUTODETECT.hpp>
#include "app_hal.h"
#if defined(COLOR_KIT_PRO)
  #include "color_kit_pro_lgfx.hpp"
#elif defined(COLOR_KIT_GRANDE)
  #include "color_kit_grande_lgfx.hpp"
#elif
 #error "Please define your board"
#endif
#include <Arduino.h>
#include <lvgl.h>



#include <Wire.h> // Needed for I2C

/*Change to your screen resolution*/
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 480;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[2][ screenWidth * 30 ];

uint32_t lastTouchMillis = 0;

#if defined( COLOR_KIT_PRO )
  ColorKitPro gfx;
#elif defined( COLOR_KIT_GRANDE )
  ColorKitGrande gfx;
#endif


/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p ) {

    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    gfx.startWrite();
    gfx.setAddrWindow(area->x1, area->y1, w, h);
    gfx.pushPixelsDMA((uint16_t*)&color_p->full, w * h);

    gfx.endWrite();

    lv_disp_flush_ready( disp );
}


/*Read the touchpad*/
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
    uint16_t touchX, touchY;

    data->state = LV_INDEV_STATE_REL;

    if( gfx.getTouch( &touchX, &touchY ) )
    {
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = touchX;
        data->point.y = touchY;
        lastTouchMillis = millis();
    }
}

void hal_setup()
{
    //Serial.begin(115200);
    //Serial.setDebugOutput(true);
    
    gfx.begin();

    lv_init();
    lv_disp_draw_buf_init( &draw_buf, buf[0], buf[1], screenWidth * 10 );

    //Initialize the display
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    //Change the following line to your display resolution
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    //Initialize the input device driver
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );
    gfx.setBrightness(255);
 

    log_i("Benchmark done");

}
uint32_t lastLogMillis = 0;
void hal_loop() {
  lv_timer_handler();
  delay(1);

  if (millis() - lastLogMillis > 1000) {
    lastLogMillis = millis();
    log_i("Loop: %d", millis());
  } 
}