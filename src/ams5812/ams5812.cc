/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
*/

#include "ams5812/ams5812.h"

namespace sensors {

Ams5812::Ams5812(i2c_t3 *bus, uint8_t addr, Transducer type) {
  bus_ = bus;
  addr_ = addr;
  switch (type) {
    case AMS5812_0000_D: {
      min_press_psi_ = 0.0f;
      max_press_psi_ = 0.075f;
      break;
    }
    case AMS5812_0001_D: {
      min_press_psi_ = 0.0f;
      max_press_psi_ = 0.15f;
      break;
    }
    case AMS5812_0000_D_B: {
      min_press_psi_ = -0.075f;
      max_press_psi_ = 0.075f;
      break;
    }
    case AMS5812_0001_D_B: {
      min_press_psi_ = -0.15f;
      max_press_psi_ = 0.15f;
      break;
    }
    case AMS5812_0003_D: {
      min_press_psi_ = 0.0f;
      max_press_psi_ = 0.3f;
      break;
    }
    case AMS5812_0008_D: {
      min_press_psi_ = 0.0f;
      max_press_psi_ = 0.8f;
      break;
    }
    case AMS5812_0015_D: {
      min_press_psi_ = 0.0f;
      max_press_psi_ = 1.5f;
      break;
    }
    case AMS5812_0003_D_B: {
      min_press_psi_ = -0.3f;
      max_press_psi_ = 0.3f;
      break;
    }
    case AMS5812_0008_D_B: {
      min_press_psi_ = -0.8f;
      max_press_psi_ = 0.8f;
      break;
    }
    case AMS5812_0015_D_B: {
      min_press_psi_ = -1.5f;
      max_press_psi_ = 1.5f;
      break;
    }
    case AMS5812_0030_D: {
      min_press_psi_ = 0.0f;
      max_press_psi_ = 3.0f;
      break;
    }
    case AMS5812_0050_D: {
      min_press_psi_ = 0.0f;
      max_press_psi_ = 5.0f;
      break;
    }
    case AMS5812_0150_D: {
      min_press_psi_ = 0.0f;
      max_press_psi_ = 15.0f;
      break;
    }
    case AMS5812_0300_D: {
      min_press_psi_ = 0.0f;
      max_press_psi_ = 30.0f;
      break;
    }
    case AMS5812_0600_D: {
      min_press_psi_ = 0.0f;
      max_press_psi_ = 60.0f;
      break;
    }
    case AMS5812_1000_D: {
      min_press_psi_ = 0.0f;
      max_press_psi_ = 100.0f;
      break;
    }
    case AMS5812_0030_D_B: {
      min_press_psi_ = -3.0f;
      max_press_psi_ = 3.0f;
      break;
    }
    case AMS5812_0050_D_B: {
      min_press_psi_ = -5.0f;
      max_press_psi_ = 5.0f;
      break;
    }
    case AMS5812_0150_D_B: {
      min_press_psi_ = -15.0f;
      max_press_psi_ = 15.0f;
      break;
    }
    case AMS5812_0150_B: {
      min_press_psi_ = 11.0f;
      max_press_psi_ = 17.5f;
      break;
    }
    case AMS5812_0150_A: {
      min_press_psi_ = 0.0f;
      max_press_psi_ = 15.0f;
      break;
    }
    case AMS5812_0300_A: {
      min_press_psi_ = 0.0f;
      max_press_psi_ = 30.0f;
      break;
    }
  }
}
bool Ams5812::Begin() {
  bus_->begin();
  bus_->setClock(I2C_CLOCK_);
  /* Checking to see if we can communicate with sensor */
  for (unsigned int tries = 0; tries < MAX_TRIES_; tries++) {
    if (Read()) {
      return true;
    }
    delay(10);
  }
  return false;
}
bool Ams5812::Read() {
  uint8_t buffer[4];
  unsigned int bytes_rx = bus_->requestFrom(addr_, sizeof(buffer), I2C_STOP, I2C_TIMEOUT_US_);
  if (bytes_rx != sizeof(buffer)) {
    return false;
  }
  bus_->read(buffer, sizeof(buffer));
  uint16_t pressure_counts =  static_cast<uint16_t>(buffer[0] & 0x7F) << 8 | buffer[1];
  uint16_t temperature_counts = static_cast<uint16_t>(buffer[2] & 0x7F) << 8 | buffer[3];
  float pressure_psi = static_cast<float>(pressure_counts - DIG_OUT_PMIN_) / static_cast<float>(DIG_OUT_PMAX_ - DIG_OUT_PMIN_) * (max_press_psi_ - min_press_psi_) + min_press_psi_;
  float temperature_c = static_cast<float>(temperature_counts - DIG_OUT_TMIN_) / static_cast<float>(DIG_OUT_TMAX_ - DIG_OUT_TMIN_) * (MAX_T_C_ - MIN_T_C_) + MIN_T_C_;
  p_.psi(pressure_psi);
  t_.c(temperature_c);
  return true;
}
Pressure Ams5812::pressure() {
  return p_;
}
Temperature Ams5812::die_temperature() {
  return t_;
}

}  // namespace sensors
