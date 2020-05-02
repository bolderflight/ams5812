/*
  AMS5812.h
  Brian R Taylor
  brian.taylor@bolderflight.com

  Copyright (c) 2017 Bolder Flight Systems

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef AMS5812_h
#define AMS5812_h

#include "Wire.h"
#include "Arduino.h"

class AMS5812{
  public:
    enum Transducer
    {
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
    AMS5812(TwoWire &bus,uint8_t address,Transducer type);
    int begin();
    int readSensor();
    float getPressure_Pa();
    float getTemperature_C();
  private:
    // struct to hold sensor data
    struct Data {
      float Pressure_Pa;
      float Temp_C;
    };
    Data _data;
    // I2C bus
    TwoWire *_bus;
    // sensor address
    uint8_t _address;
    // transducer type
    Transducer _type;
    // buffer for I2C data
    uint8_t _buffer[4];
    // number of bytes received from I2C
    size_t _numBytes;
    // maximum number of attempts to talk to sensor
    const size_t _maxAttempts = 10;
    // track success of reading from sensor
    int _status;
    // pressure digital output, counts
    uint16_t _pressureCounts;      
    // temperature digital output, counts
    uint16_t _temperatureCounts;   
    // min and max pressure, millibar
    float _pMin;
    float _pMax;
    // i2c bus frequency
    const uint32_t _i2cRate = 400000;
    // conversion PSI to PA
    const float _psi2pa = 4.4482216152605f/(0.0254f*0.0254f); 
    // digital output at minimum pressure
    const int _digOutPmin = 3277;   
    // digital output at maximum pressure
    const int _digOutPmax = 29491;  
    // digital output at minimum temperature
    const int _digOutTmin = 3277;   
    // digital output at maximum temperature
    const int _digOutTmax = 29491; 
    // temperature ranges, C
    const float _tMin = -25.0f;
    const float _tMax = 85.0f;
    // min and max pressures, PSI
  	const float AMS5812_0000_D_P_MIN = 0.0f;
  	const float AMS5812_0000_D_P_MAX = 0.075f;
  	const float AMS5812_0001_D_P_MIN = 0.0f;
  	const float AMS5812_0001_D_P_MAX = 0.15f;
  	const float AMS5812_0000_D_B_P_MIN = -0.075f;
  	const float AMS5812_0000_D_B_P_MAX = 0.075f;
  	const float AMS5812_0001_D_B_P_MIN = -0.15f;
  	const float AMS5812_0001_D_B_P_MAX = 0.15f;
  	const float AMS5812_0003_D_P_MIN = 0.0f;
  	const float AMS5812_0003_D_P_MAX = 0.3f;
  	const float AMS5812_0008_D_P_MIN = 0.0f;
  	const float AMS5812_0008_D_P_MAX = 0.8f;
  	const float AMS5812_0015_D_P_MIN = 0.0f;
  	const float AMS5812_0015_D_P_MAX = 1.5f;
  	const float AMS5812_0003_D_B_P_MIN = -0.3f;
  	const float AMS5812_0003_D_B_P_MAX = 0.3f;
  	const float AMS5812_0008_D_B_P_MIN = -0.8f;
  	const float AMS5812_0008_D_B_P_MAX = 0.8f;
  	const float AMS5812_0015_D_B_P_MIN = -1.5f;
  	const float AMS5812_0015_D_B_P_MAX = 1.5f;
  	const float AMS5812_0030_D_P_MIN = 0.0f;
  	const float AMS5812_0030_D_P_MAX = 3.0f;
  	const float AMS5812_0050_D_P_MIN = 0.0f;
  	const float AMS5812_0050_D_P_MAX = 5.0f;
  	const float AMS5812_0150_D_P_MIN = 0.0f;
  	const float AMS5812_0150_D_P_MAX = 15.0f;
  	const float AMS5812_0300_D_P_MIN = 0.0f;
  	const float AMS5812_0300_D_P_MAX = 30.0f;
  	const float AMS5812_0600_D_P_MIN = 0.0f;
  	const float AMS5812_0600_D_P_MAX = 60.0f;
  	const float AMS5812_1000_D_P_MIN = 0.0f;
  	const float AMS5812_1000_D_P_MAX = 100.0f;
  	const float AMS5812_0030_D_B_P_MIN = -3.0f;
  	const float AMS5812_0030_D_B_P_MAX = 3.0f;
  	const float AMS5812_0050_D_B_P_MIN = -5.0f;
  	const float AMS5812_0050_D_B_P_MAX = 5.0f;
  	const float AMS5812_0150_D_B_P_MIN = -15.0f;
  	const float AMS5812_0150_D_B_P_MAX = 15.0f;
  	const float AMS5812_0150_B_P_MIN = 11.0f;
  	const float AMS5812_0150_B_P_MAX = 17.5f;
  	const float AMS5812_0150_A_P_MIN = 0.0f;
  	const float AMS5812_0150_A_P_MAX = 15.0f;
  	const float AMS5812_0300_A_P_MIN = 0.0f;
  	const float AMS5812_0300_A_P_MAX = 30.0f;
	  void getTransducer();
    int readBytes(uint16_t* pressureCounts, uint16_t* temperatureCounts);
};

#endif
