/*
AMS5812.h
Brian R Taylor
brian.taylor@bolderflight.com

Copyright (c) 2017 Bolder Flight Systems

Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
