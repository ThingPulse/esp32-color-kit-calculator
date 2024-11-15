#pragma once

#define LGFX_USE_V1


#include <LovyanGFX.hpp>
#include <driver/i2c.h>
#include "settings.h"


class ColorKitGrande : public lgfx::LGFX_Device
{
  static constexpr int I2C_PORT_NUM = I2C_NUM_0;
  static constexpr int I2C_PIN_SDA = TOUCH_SDA;
  static constexpr int I2C_PIN_SCL = TOUCH_SCL;
  static constexpr int I2C_PIN_INT = TOUCH_INT;

  lgfx::Bus_SPI _bus_instance;
  lgfx::Panel_ILI9488 _panel_instance;
  lgfx::Light_PWM     _light_instance;
  lgfx::ITouch*  _touch_instance_ptr = nullptr;

  /// Detects and configures the touch panel during initialization;
  bool init_impl(bool use_reset, bool use_clear) override
  {
    if (_touch_instance_ptr == nullptr)
    {
      lgfx::ITouch::config_t cfg;
      lgfx::i2c::init(I2C_PORT_NUM, I2C_PIN_SDA, I2C_PIN_SCL);
      if (lgfx::i2c::beginTransaction(I2C_PORT_NUM, 0x38, 400000, false).has_value()
       && lgfx::i2c::endTransaction(I2C_PORT_NUM).has_value())
      {
        _touch_instance_ptr = new lgfx::Touch_FT5x06();
        cfg = _touch_instance_ptr->config();
        cfg.i2c_addr = 0x38;
        cfg.x_max = 320;
        cfg.y_max = 480;
      }
      else
      if (lgfx::i2c::beginTransaction(I2C_PORT_NUM, 0x48, 400000, false).has_value()
       && lgfx::i2c::endTransaction(I2C_PORT_NUM).has_value())
      {
        _touch_instance_ptr = new lgfx::Touch_NS2009();
        cfg = _touch_instance_ptr->config();
        cfg.i2c_addr = 0x48;
        cfg.x_min = 368;
        cfg.y_min = 212;
        cfg.x_max = 3800;
        cfg.y_max = 3800;
      }
      if (_touch_instance_ptr != nullptr)
      {
        cfg.i2c_port = I2C_PORT_NUM;
        cfg.pin_sda  = I2C_PIN_SDA;
        cfg.pin_scl  = I2C_PIN_SCL;
        cfg.pin_int  = I2C_PIN_INT;
        cfg.freq = 400000;
        cfg.bus_shared = false;
        _touch_instance_ptr->config(cfg);
        _panel_instance.touch(_touch_instance_ptr);
      }
    }
    return lgfx::LGFX_Device::init_impl(use_reset, use_clear);
  }

public:

  ColorKitGrande(void)
  {
    {
      auto cfg = _bus_instance.config();
          
      cfg.freq_write = 40000000;    
      cfg.freq_read  = 16000000;    
     
      cfg.dma_channel = 1; 
      cfg.pin_sclk = TFT_SCLK;            
      cfg.pin_mosi = TFT_MOSI;            
      cfg.pin_miso = TFT_MISO;            
      cfg.pin_dc   = TFT_DC;  
          
      _bus_instance.config(cfg);
      _panel_instance.bus(&_bus_instance);
    }

    {
      auto cfg = _panel_instance.config();
      cfg.pin_cs          =    TFT_CS;
      cfg.pin_rst         =    TFT_RST;
      cfg.pin_busy        =    -1;
      cfg.offset_rotation =     2;
      cfg.readable        =  true;
      cfg.invert          = false;
      cfg.rgb_order       = false;
      cfg.dlen_16bit      =  true;
      cfg.bus_shared      = true;

      _panel_instance.config(cfg);
    }

    {
      auto cfg = _light_instance.config();

      cfg.pin_bl = TFT_BL;
      cfg.invert = false;
      cfg.freq   = 44100;
      cfg.pwm_channel = 7;

      _light_instance.config(cfg);
      _panel_instance.light(&_light_instance);
    }
    setPanel(&_panel_instance);
  }
};