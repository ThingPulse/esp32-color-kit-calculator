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

#include <lvgl.h>

#include "Button2.h"


#include <Wire.h> // Needed for I2C
#include <SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h> 

SFE_MAX1704X lipo(MAX1704X_MAX17048); // Create a MAX17048

#define BUTTON_PIN 4

Button2 button;

/*Change to your screen resolution*/
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 480;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[2][ screenWidth * 30 ];

uint32_t lastTouchMillis = 0;

CKGCompact gfx;

void gotoSleep() {
    gfx.touch()->sleep();
    gfx.sleep();
    uint8_t res = lipo.sleep();
    log_i("Gauge reached deep sleep: %s", res == 0 ? "yes" : "false");

    pinMode(PIN_TACTILE_BUTTON1, INPUT);
    pinMode(PIN_TACTILE_BUTTON2, INPUT);
    pinMode(PIN_TACTILE_BUTTON3, INPUT);
    pinMode(PIN_FUELGAGE_INT, INPUT);
    pinMode(PIN_TOUCH_INT, INPUT);
    pinMode(PIN_DB0, INPUT);
    pinMode(PIN_DB1, INPUT);
    pinMode(PIN_DB2, INPUT);
    pinMode(PIN_DB3, INPUT);
    pinMode(PIN_DB4, INPUT);
    pinMode(PIN_DB5, INPUT);
    pinMode(PIN_DB6, INPUT);
    pinMode(PIN_DB7, INPUT);
    pinMode(PIN_DB8, INPUT);
    pinMode(PIN_DB9, INPUT);
    pinMode(PIN_DB10, INPUT);
    pinMode(PIN_DB11, INPUT);
    pinMode(PIN_DB12, INPUT);
    pinMode(PIN_DB13, INPUT);
    pinMode(PIN_DB14, INPUT);
    pinMode(PIN_DB15, INPUT);
    pinMode(PIN_TFT_RD, INPUT);
    pinMode(PIN_TFT_WR, INPUT);
    pinMode(PIN_TFT_RS, INPUT);
    pinMode(PIN_TFT_CS, INPUT);
    pinMode(PIN_TFT_RESET, INPUT);
    pinMode(PIN_TFT_LED, INPUT);
    pinMode(PIN_I2C_SDA, INPUT);
    pinMode(PIN_I2C_SCL, INPUT);
    pinMode(PIN_BUZZER, INPUT);

   
    delay(200);

    log_i("Going to sleep");
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_1,1);
    esp_deep_sleep_start();
}

void handleTap(Button2& b) {
    if (b.wasPressedFor() > 1000) {
        gotoSleep();
    }
}


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
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    
    gfx.begin();

      // Set up the MAX17043 LiPo fuel gauge:
    if (lipo.begin() == false) // Connect to the MAX17043 using the default wire port
    {
        Serial.println(F("MAX17043 not detected. Please check wiring. Freezing."));
        while (1)
        ;
    }

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
    button.begin(BUTTON_PIN);
    button.setTapHandler(handleTap);

    log_i("Benchmark done");

}
uint32_t lastLogMillis = 0;
void hal_loop() {
  lv_timer_handler();
  delay(1);
  if (lastTouchMillis > 0 && millis() - lastTouchMillis > AUTO_SLEEP_MILLIS) {
    lastTouchMillis = 0;
    gotoSleep();
  }
  button.loop();
}