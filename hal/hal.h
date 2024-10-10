#pragma once

#if defined(NATIVE)
  #include "mac_arm64/include_hal_mac_arm64.h"
#elif defined(ARDUINO)
  #include "ESP32/include_hal_esp32.h"
#endif