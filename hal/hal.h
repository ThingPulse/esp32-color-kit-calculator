#pragma once

#if defined(NATIVE)
  #include "mac_arm64/include_hal_mac_arm64.h"
#elif defined(ARDUINO)
  #include "ckg-pro/include_hal_ckg_pro.h"
#endif