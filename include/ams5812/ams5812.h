/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
*/

#ifndef INCLUDE_AMS5812_AMS5812_H_
#define INCLUDE_AMS5812_AMS5812_H_

#include "core/core.h"

namespace sensors {

class Ams5812 {
 public:
  enum Transducer {
    AMS5812_0000_D,
    AMS5812_0001_D,
    AMS5812_0000_D_B,
    AMS5812_0001_D_B,
    AMS5812_0003_D,
    AMS5812_0008_D,
    AMS5812_0015_D,
    AMS5812_0003_D_B,
    AMS5812_0008_D_B,
    AMS5812_0015_D_B,
    AMS5812_0030_D,
    AMS5812_0050_D,
    AMS5812_0150_D,
    AMS5812_0300_D,
    AMS5812_0600_D,
    AMS5812_1000_D,
    AMS5812_0030_D_B,
    AMS5812_0050_D_B,
    AMS5812_0150_D_B,
    AMS5812_0150_B,
    AMS5812_0150_A,
    AMS5812_0300_A};
  #if defined(__IMXRT1062__)
    Ams5812(TwoWire *bus, uint8_t addr, Transducer type);
  #else
    Ams5812(i2c_t3 *bus, uint8_t addr, Transducer type);
  #endif
  bool Begin();
  bool Read();
  float pressure_pa();
  float die_temperature_c();

 private:
  /* Communication interface */
  #if defined(__IMXRT1062__)
    TwoWire *bus_;
  #else
    i2c_t3 *bus_;
  #endif
  uint8_t addr_;
  static constexpr uint32_t I2C_CLOCK_ = 400000;
  static constexpr unsigned int MAX_TRIES_ = 10;
  static constexpr unsigned int I2C_TIMEOUT_US_ = 200;
  /* Min and max pressure, millibar */
  float min_press_psi_, max_press_psi_;
  /* Digital output at min and max pressure */
  static constexpr uint16_t DIG_OUT_PMIN_ = 3277;
  static constexpr uint16_t DIG_OUT_PMAX_ = 29491;
  /* Digital output at min and max temperature */
  static constexpr uint16_t DIG_OUT_TMIN_ = 3277;
  static constexpr uint16_t DIG_OUT_TMAX_ = 29491;
  /* Minimum and maximum temperature */
  static constexpr float MIN_T_C_ = -25.0f;
  static constexpr float MAX_T_C_ = 85.0f;
  /* Data */
  float p_;
  float t_;
};

}  // namespace sensors


#endif  // INCLUDE_AMS5812_AMS5812_H_
