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

#include "core/core.h"
#include "global_defs/global_defs.h"

namespace sensors {
/* Enum of AMS-5812 pressure transducers support */
enum class Ams5812Type {
  MIN,
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
  AMS5812_0300_A,
  MAX
};
/*
* Sensor driver to read the AMS-5812 pressure transducer. Templated on
* the I2C bus, address, and transducer type, this is done to check
* the address and transducer type validity during compile time.
*/
template<TwoWire *BUS_, int ADDR_, Ams5812Type TYPE_>
class Ams5812 {
 public:
  /* Check that address is valid */
  static_assert(((ADDR_ > 0) && (ADDR_ < 128)),
    "Invalid I2C address, expected range 1-127");
  /* Check that pressure transducer type is valid */
  static_assert(((TYPE_ > Ams5812Type::MIN) && (TYPE_ < Ams5812Type::MAX)),
    "Invalid AMS5915 pressure transducer type");
  Ams5812() {
    float max_pres_psi_ = 0;
    switch (TYPE_) {
      case Ams5812Type::AMS5812_0000_D: {
        min_pres_psi_ = 0.0f;
        max_pres_psi_ = 0.075f;
        break;
      }
      case Ams5812Type::AMS5812_0001_D: {
        min_pres_psi_ = 0.0f;
        max_pres_psi_ = 0.15f;
        break;
      }
      case Ams5812Type::AMS5812_0000_D_B: {
        min_pres_psi_ = -0.075f;
        max_pres_psi_ = 0.075f;
        break;
      }
      case Ams5812Type::AMS5812_0001_D_B: {
        min_pres_psi_ = -0.15f;
        max_pres_psi_ = 0.15f;
        break;
      }
      case Ams5812Type::AMS5812_0003_D: {
        min_pres_psi_ = 0.0f;
        max_pres_psi_ = 0.3f;
        break;
      }
      case Ams5812Type::AMS5812_0008_D: {
        min_pres_psi_ = 0.0f;
        max_pres_psi_ = 0.8f;
        break;
      }
      case Ams5812Type::AMS5812_0015_D: {
        min_pres_psi_ = 0.0f;
        max_pres_psi_ = 1.5f;
        break;
      }
      case Ams5812Type::AMS5812_0003_D_B: {
        min_pres_psi_ = -0.3f;
        max_pres_psi_ = 0.3f;
        break;
      }
      case Ams5812Type::AMS5812_0008_D_B: {
        min_pres_psi_ = -0.8f;
        max_pres_psi_ = 0.8f;
        break;
      }
      case Ams5812Type::AMS5812_0015_D_B: {
        min_pres_psi_ = -1.5f;
        max_pres_psi_ = 1.5f;
        break;
      }
      case Ams5812Type::AMS5812_0030_D: {
        min_pres_psi_ = 0.0f;
        max_pres_psi_ = 3.0f;
        break;
      }
      case Ams5812Type::AMS5812_0050_D: {
        min_pres_psi_ = 0.0f;
        max_pres_psi_ = 5.0f;
        break;
      }
      case Ams5812Type::AMS5812_0150_D: {
        min_pres_psi_ = 0.0f;
        max_pres_psi_ = 15.0f;
        break;
      }
      case Ams5812Type::AMS5812_0300_D: {
        min_pres_psi_ = 0.0f;
        max_pres_psi_ = 30.0f;
        break;
      }
      case Ams5812Type::AMS5812_0600_D: {
        min_pres_psi_ = 0.0f;
        max_pres_psi_ = 60.0f;
        break;
      }
      case Ams5812Type::AMS5812_1000_D: {
        min_pres_psi_ = 0.0f;
        max_pres_psi_ = 100.0f;
        break;
      }
      case Ams5812Type::AMS5812_0030_D_B: {
        min_pres_psi_ = -3.0f;
        max_pres_psi_ = 3.0f;
        break;
      }
      case Ams5812Type::AMS5812_0050_D_B: {
        min_pres_psi_ = -5.0f;
        max_pres_psi_ = 5.0f;
        break;
      }
      case Ams5812Type::AMS5812_0150_D_B: {
        min_pres_psi_ = -15.0f;
        max_pres_psi_ = 15.0f;
        break;
      }
      case Ams5812Type::AMS5812_0150_B: {
        min_pres_psi_ = 11.0f;
        max_pres_psi_ = 17.5f;
        break;
      }
      case Ams5812Type::AMS5812_0150_A: {
        min_pres_psi_ = 0.0f;
        max_pres_psi_ = 15.0f;
        break;
      }
      case Ams5812Type::AMS5812_0300_A: {
        min_pres_psi_ = 0.0f;
        max_pres_psi_ = 30.0f;
        break;
      }
    }
    pres_range_psi = max_pres_psi_ - min_pres_psi_;
  }
  inline static constexpr int i2c_clock() {return I2C_CLOCK_;}
  bool Begin() {
    /* Checking to see if we can communicate with sensor */
    for (std::size_t tries = 0; tries < MAX_TRIES_; tries++) {
      if (Read()) {
        return true;
      }
      delay(10);
    }
    return false;
  }
  bool Read() {
    uint8_t buf[4];
    std::size_t bytes_req = sizeof(buf);
    std::size_t bytes_rx = BUS_->requestFrom(ADDR_, bytes_req);
    if (bytes_rx != bytes_req) {
      return false;
    }
    for (std::size_t i = 0; i < bytes_rx; i++) {
      buf[i] = BUS_->read();
    }
    uint16_t p_cnts =  static_cast<uint16_t>(buf[0] & 0x7F) << 8 | buf[1];
    uint16_t t_cnts = static_cast<uint16_t>(buf[2] & 0x7F) << 8 | buf[3];
    float p_psi = static_cast<float>(p_cnts - D_PMIN_) / D_PRANGE_
      * pres_range_psi + min_pres_psi_;
    float t_c = static_cast<float>(t_cnts - D_TMIN_) / D_TRANGE_ * T_RANGE_
      + MIN_T_C_;
    if (t_c > MAX_T_C_) {return false;}
    p_ = global::conversions::Psi_to_Pa(p_psi);
    t_ = t_c;
    return true;
  }
  inline float pressure_pa() const {return p_;}
  inline float die_temperature_c() const {return t_;}

 private:
  /* Communication interface */
  static constexpr int I2C_CLOCK_ = 400000;
  static constexpr std::size_t MAX_TRIES_ = 10;
  /* Min and max pressure, millibar */
  float min_pres_psi_, pres_range_psi;
  /* Digital output at min and max pressure */
  static constexpr uint16_t D_PMIN_ = 3277;
  static constexpr uint16_t D_PMAX_ = 29491;
  static constexpr float D_PRANGE_ = static_cast<float>(D_PMAX_ - D_PMIN_);
  /* Digital output at min and max temperature */
  static constexpr uint16_t D_TMIN_ = 3277;
  static constexpr uint16_t D_TMAX_ = 29491;
  static constexpr float D_TRANGE_ = static_cast<float>(D_TMAX_ - D_TMIN_);
  /* Minimum and maximum temperature */
  static constexpr float MIN_T_C_ = -25.0f;
  static constexpr float MAX_T_C_ = 85.0f;
  static constexpr float T_RANGE_ = MAX_T_C_ - MIN_T_C_;
  /* Data */
  float p_, t_;
};

}  // namespace sensors

#endif  // INCLUDE_AMS5812_AMS5812_H_
