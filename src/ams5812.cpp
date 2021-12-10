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

#include "ams5812.h"  // NOLINT
#if defined(ARDUINO)
#include "Arduino.h"
#include "Wire.h"
#else
#include "core/core.h"
#endif

namespace bfs {

Ams5812::Ams5812(TwoWire *bus, const uint8_t addr, const Transducer type) {
  bus_ = bus;
  addr_ = addr;
  switch (type) {
    case AMS5812_0000_D: {
      min_pres_psi_ = 0.0f;
      max_pres_psi_ = 0.075f;
      break;
    }
    case AMS5812_0001_D: {
      min_pres_psi_ = 0.0f;
      max_pres_psi_ = 0.15f;
      break;
    }
    case AMS5812_0000_D_B: {
      min_pres_psi_ = -0.075f;
      max_pres_psi_ = 0.075f;
      break;
    }
    case AMS5812_0001_D_B: {
      min_pres_psi_ = -0.15f;
      max_pres_psi_ = 0.15f;
      break;
    }
    case AMS5812_0003_D: {
      min_pres_psi_ = 0.0f;
      max_pres_psi_ = 0.3f;
      break;
    }
    case AMS5812_0008_D: {
      min_pres_psi_ = 0.0f;
      max_pres_psi_ = 0.8f;
      break;
    }
    case AMS5812_0015_D: {
      min_pres_psi_ = 0.0f;
      max_pres_psi_ = 1.5f;
      break;
    }
    case AMS5812_0003_D_B: {
      min_pres_psi_ = -0.3f;
      max_pres_psi_ = 0.3f;
      break;
    }
    case AMS5812_0008_D_B: {
      min_pres_psi_ = -0.8f;
      max_pres_psi_ = 0.8f;
      break;
    }
    case AMS5812_0015_D_B: {
      min_pres_psi_ = -1.5f;
      max_pres_psi_ = 1.5f;
      break;
    }
    case AMS5812_0030_D: {
      min_pres_psi_ = 0.0f;
      max_pres_psi_ = 3.0f;
      break;
    }
    case AMS5812_0050_D: {
      min_pres_psi_ = 0.0f;
      max_pres_psi_ = 5.0f;
      break;
    }
    case AMS5812_0150_D: {
      min_pres_psi_ = 0.0f;
      max_pres_psi_ = 15.0f;
      break;
    }
    case AMS5812_0300_D: {
      min_pres_psi_ = 0.0f;
      max_pres_psi_ = 30.0f;
      break;
    }
    case AMS5812_0600_D: {
      min_pres_psi_ = 0.0f;
      max_pres_psi_ = 60.0f;
      break;
    }
    case AMS5812_1000_D: {
      min_pres_psi_ = 0.0f;
      max_pres_psi_ = 100.0f;
      break;
    }
    case AMS5812_0030_D_B: {
      min_pres_psi_ = -3.0f;
      max_pres_psi_ = 3.0f;
      break;
    }
    case AMS5812_0050_D_B: {
      min_pres_psi_ = -5.0f;
      max_pres_psi_ = 5.0f;
      break;
    }
    case AMS5812_0150_D_B: {
      min_pres_psi_ = -15.0f;
      max_pres_psi_ = 15.0f;
      break;
    }
    case AMS5812_0150_B: {
      min_pres_psi_ = 11.0f;
      max_pres_psi_ = 17.5f;
      break;
    }
    case AMS5812_0150_A: {
      min_pres_psi_ = 0.0f;
      max_pres_psi_ = 15.0f;
      break;
    }
    case AMS5812_0300_A: {
      min_pres_psi_ = 0.0f;
      max_pres_psi_ = 30.0f;
      break;
    }
  }
  pres_range_psi_ = max_pres_psi_ - min_pres_psi_;
}
bool Ams5812::Begin() {
  /* Checking to see if we can communicate with sensor */
  for (size_t tries = 0; tries < MAX_TRIES_; tries++) {
    if (Read()) {
      return true;
    }
    delay(10);
  }
  return false;
}
bool Ams5812::Read() {
  bytes_rx_ = bus_->requestFrom(addr_, sizeof(buf_));
  if (bytes_rx_ != sizeof(buf_)) {
    return false;
  }
  for (size_t i = 0; i < bytes_rx_; i++) {
    buf_[i] = bus_->read();
  }
  pres_cnts_ = static_cast<uint16_t>(buf_[0] & 0x7F) << 8 | buf_[1];
  temp_cnts_ = static_cast<uint16_t>(buf_[2] & 0x7F) << 8 | buf_[3];
  pres_psi_ = static_cast<float>(pres_cnts_ - PMIN_) / PRANGE_ *
              pres_range_psi_ + min_pres_psi_;
  temp_ = static_cast<float>(temp_cnts_ - TMIN_) / TRANGE_ * T_RANGE_C_ +
          MIN_T_C_;
  if (temp_ > MAX_T_C_) {return false;}
  pres_pa_ = pres_psi_ * PSI2PA_;
  temp_c_ = temp_;
  return true;
}

}  // namespace bfs
