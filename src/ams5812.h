/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2022 Bolder Flight Systems Inc
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

#ifndef AMS5812_SRC_AMS5812_H_  // NOLINT
#define AMS5812_SRC_AMS5812_H_

#if defined(ARDUINO)
#include "Arduino.h"
#include "Wire.h"
#else
#include "core/core.h"
#endif

namespace bfs {

class Ams5812 {
 public:
  enum Transducer : int8_t {
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
    AMS5812_0300_A
  };
  Ams5812() {}
  Ams5812(TwoWire *bus, const uint8_t addr, const Transducer type);
  void Config(TwoWire *bus, const uint8_t addr, const Transducer type);
  bool Begin();
  bool Read();
  inline float pres_pa() const {return pres_pa_;}
  inline float die_temp_c() const {return temp_c_;}

 private:
  /* Communication interface */
  TwoWire *bus_;
  uint8_t addr_;
  static constexpr size_t MAX_TRIES_ = 10;
  /* Min and max pressure, millibar */
  float min_pres_psi_, max_pres_psi_, pres_range_psi_;
  /* Digital output at min and max pressure */
  static constexpr uint16_t PMIN_ = 3277;
  static constexpr uint16_t PMAX_ = 29491;
  static constexpr float PRANGE_ = static_cast<float>(PMAX_ - PMIN_);
  /* Digital output at min and max temperature */
  static constexpr uint16_t TMIN_ = 3277;
  static constexpr uint16_t TMAX_ = 29491;
  static constexpr float TRANGE_ = static_cast<float>(TMAX_ - TMIN_);
  /* Minimum and maximum temperature */
  static constexpr float MIN_T_C_ = -25.0f;
  static constexpr float MAX_T_C_ = 85.0f;
  static constexpr float T_RANGE_C_ = MAX_T_C_ - MIN_T_C_;
  /* Data */
  uint8_t buf_[4];
  uint8_t bytes_rx_;
  uint16_t pres_cnts_, temp_cnts_;
  float pres_psi_, temp_;
  float pres_pa_, temp_c_;
};

}  // namespace bfs

#endif  // AMS5812_SRC_AMS5812_H_ NOLINT
