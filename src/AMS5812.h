/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2021 Bolder Flight Systems Inc
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the “Software”), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#ifndef INCLUDE_AMS5812_AMS5812_H_
#define INCLUDE_AMS5812_AMS5812_H_

#include "Arduino.h"
#include "Wire.h"

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
  Ams5812(TwoWire *bus, uint8_t addr, Transducer type);
  bool Begin();
  bool Read();
  inline float pressure_pa() const {return pres_pa_;}
  inline float die_temperature_c() const {return temp_c_;}

 private:
  /* Communication interface */
  TwoWire *bus_;
  uint8_t addr_;
  static constexpr uint32_t I2C_CLOCK_ = 400000;
  static constexpr std::size_t MAX_TRIES_ = 10;
  /* Min and max pressure, millibar */
  float min_pres_psi_, max_pres_psi_, pres_range_psi_;
  /* Digital output at min and max pressure */
  static constexpr uint16_t DIG_OUT_PMIN_ = 3277;
  static constexpr uint16_t DIG_OUT_PMAX_ = 29491;
  static constexpr float DIG_OUT_PRANGE_ =
    static_cast<float>(DIG_OUT_PMAX_ - DIG_OUT_PMIN_);
  /* Digital output at min and max temperature */
  static constexpr uint16_t DIG_OUT_TMIN_ = 3277;
  static constexpr uint16_t DIG_OUT_TMAX_ = 29491;
  static constexpr float DIG_OUT_TRANGE_ =
    static_cast<float>(DIG_OUT_TMAX_ - DIG_OUT_TMIN_);
  /* Minimum and maximum temperature */
  static constexpr float MIN_T_C_ = -25.0f;
  static constexpr float MAX_T_C_ = 85.0f;
  static constexpr float T_RANGE_C_ = MAX_T_C_ - MIN_T_C_;
  /* Data */
  float pres_pa_, temp_c_;
};

#endif  // INCLUDE_AMS5812_AMS5812_H_
