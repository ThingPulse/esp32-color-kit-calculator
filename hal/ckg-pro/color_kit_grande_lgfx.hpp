#pragma once

#define LGFX_USE_V1


#include <LovyanGFX.hpp>
#include <driver/i2c.h>
#include "settings.h"


class ColorKitGrande : public lgfx::LGFX_Device {

  lgfx::Panel_ILI9488 _panel_instance;
  lgfx::Bus_SPI _bus_instance;
  lgfx::Light_PWM _light_instance;
  lgfx::Touch_FT5x06 _touch_instance;

public:
  ColorKitGrande(void) {
    {
      auto cfg = _bus_instance.config();

      cfg.freq_write = 40000000;
      cfg.freq_read = 16000000;
      cfg.dma_channel = 1;
      cfg.pin_sclk = TFT_SCLK;
      cfg.pin_mosi = TFT_MOSI;
      cfg.pin_miso = TFT_MISO;
      cfg.pin_dc = TFT_DC;

      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }

    {
      auto cfg = _panel_instance.config();

      cfg.pin_cs = TFT_CS;
      cfg.pin_rst = TFT_RST;
      // cfg.pin_busy = -1;

      cfg.memory_width = 320;
      cfg.memory_height = 480;
      cfg.panel_width = 320;
      cfg.panel_height = 480;
      // cfg.offset_x = 0;
      // cfg.offset_y = 0;
      // cfg.offset_rotation = 0;
      // cfg.dummy_read_pixel = 8;
      // cfg.dummy_read_bits = 1;
      // cfg.readable = true;
      // cfg.invert = false;
      // cfg.rgb_order = false; // false = do NOT invert RGB order
      // cfg.dlen_16bit = false;
      // cfg.bus_shared = true;

      _panel_instance.config(cfg);
    }

    {
      auto cfg = _light_instance.config();

      cfg.pin_bl = TFT_BL;
      // cfg.invert = false;
      cfg.freq = 44100;
      // cfg.pwm_channel = 7;

      _light_instance.config(cfg);
      _panel_instance.setLight(&_light_instance);
    }
    {
      auto cfg = _touch_instance.config();

      // cfg.x_min = 0;
      cfg.x_max = _panel_instance.config().panel_width - 1;
      // cfg.y_min = 0;
      cfg.y_max = _panel_instance.config().panel_height - 1;
      // cfg.bus_shared = true;
      // cfg.offset_rotation = 0;

      cfg.i2c_port = 1;
      cfg.i2c_addr = TOUCH_I2C_ADDR;
      cfg.pin_int = TOUCH_INT;
      cfg.pin_sda = TOUCH_SDA;
      cfg.pin_scl = TOUCH_SCL;
      cfg.freq = 400000;

      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }

    setPanel(&_panel_instance);
  }
};
