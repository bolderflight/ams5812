/*
AMS5812.cpp
Brian R Taylor
brian.taylor@bolderflight.com
2016-10-22

Copyright (c) 2016 Bolder Flight Systems

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

// Teensy 3.1/3.2 || Teensy 3.5
#if defined(__MK20DX256__) || defined(__MK64FX512__)

#include "Arduino.h"
#include "AMS5812.h"
#include <i2c_t3.h>  // I2C library

/* AMS5812 object, input the I2C address, I2C bus, and enumerated chip name (i.e. AMS5812_0150_B) */
AMS5812::AMS5812(uint8_t address, uint8_t bus, ams5812_transducer type){
  _address = address; // I2C address
  _bus = bus; // I2C bus
  _type = type; // transducer type
}

/* starts the I2C communication and sets the pressure and temperature ranges using getTransducer */
void AMS5812::begin(){
i2c_pins pins; 

	/* setting the I2C pins and protecting against _bus out of range */
	#if defined(__MK20DX256__) // Teensy 3.1/3.2
		if(_bus == 1) {
			pins = I2C_PINS_29_30;
		}
		else{
			pins = I2C_PINS_18_19;
			_bus = 0;
		}

	#endif

	#if defined(__MK64FX512__) // Teensy 3.5
		if(_bus == 2) {
			pins = I2C_PINS_3_4;
		}
		else if(_bus == 1) {
			pins = I2C_PINS_37_38;
		}
		else{
			pins = I2C_PINS_18_19;
			_bus = 0;
		}

	#endif

  	// starting the I2C
	i2c_t3(_bus).begin(I2C_MASTER, 0, pins, I2C_PULLUP_EXT, _i2cRate);

  	// setting the min and max pressure and temperature based on the chip
  	getTransducer();
}

/* reads pressure and temperature and returns values in counts */
void AMS5812::readBytes(uint16_t* pressureCounts, uint16_t* temperatureCounts){
	uint8_t b[4]; // buffer
	const uint8_t numBytes = 4;

    // 4 bytes from address
    i2c_t3(_bus).requestFrom(_address, numBytes); 
  
    // put the data in buffer
    b[0] = i2c_t3(_bus).readByte(); 
    b[1] = i2c_t3(_bus).readByte();
    b[2] = i2c_t3(_bus).readByte();
    b[3] = i2c_t3(_bus).readByte();

	// assemble into a uint16_t
	*pressureCounts = (((uint16_t) (b[0]&0x7F)) <<8) + (((uint16_t) b[1]));
	*temperatureCounts = (((uint16_t) (b[2]&0x7F)) <<8) + (((uint16_t) b[3]));
}

/* reads pressure and returns values in counts */
uint16_t AMS5812::readPressureBytes(){
	uint8_t b[2]; // buffer
	const uint8_t numBytes = 4;

    // 2 bytes from address
    i2c_t3(_bus).requestFrom(_address, numBytes); 
  
    // put the data in buffer
    b[0] = i2c_t3(_bus).readByte(); 
    b[1] = i2c_t3(_bus).readByte();

	// assemble into a uint16_t
	return (((uint16_t) (b[0]&0x7F)) <<8) + (((uint16_t) b[1]));
}

/* sets the pressure and temperature range based on the chip */
void AMS5812::getTransducer(){

  // setting the min and max temperature
  _tMin = AMS5812_T_MIN;
  _tMax = AMS5812_T_MAX;

  // setting the min and max pressures based on which transducer it is
  switch(_type) {
    case AMS5812_0000_D:
        _pMin = AMS5812_0000_D_P_MIN;
        _pMax = AMS5812_0000_D_P_MAX;
        break;
    case AMS5812_0001_D:  
        _pMin = AMS5812_0001_D_P_MIN;
        _pMax = AMS5812_0001_D_P_MAX;
        break;
    case AMS5812_0000_D_B:
        _pMin = AMS5812_0000_D_B_P_MIN;
        _pMax = AMS5812_0000_D_B_P_MAX;
        break;
    case AMS5812_0001_D_B:
        _pMin = AMS5812_0001_D_B_P_MIN;
        _pMax = AMS5812_0001_D_B_P_MAX;
        break;
    case AMS5812_0003_D:
        _pMin = AMS5812_0003_D_P_MIN;
        _pMax = AMS5812_0003_D_P_MAX;
        break;
    case AMS5812_0008_D:
        _pMin = AMS5812_0008_D_P_MIN;
        _pMax = AMS5812_0008_D_P_MAX;
        break;
    case AMS5812_0015_D:
        _pMin = AMS5812_0015_D_P_MIN;
        _pMax = AMS5812_0015_D_P_MAX;
        break;
    case AMS5812_0003_D_B:
        _pMin = AMS5812_0003_D_B_P_MIN;
        _pMax = AMS5812_0003_D_B_P_MAX;
        break;
    case AMS5812_0008_D_B:
        _pMin = AMS5812_0008_D_B_P_MIN;
        _pMax = AMS5812_0008_D_B_P_MAX;
        break;
    case AMS5812_0015_D_B:
        _pMin = AMS5812_0015_D_B_P_MIN;
        _pMax = AMS5812_0015_D_B_P_MAX;
        break;
    case AMS5812_0030_D:
        _pMin = AMS5812_0030_D_P_MIN;
        _pMax = AMS5812_0030_D_P_MAX;
        break;
    case AMS5812_0050_D:
        _pMin = AMS5812_0050_D_P_MIN;
        _pMax = AMS5812_0050_D_P_MAX;
        break;
    case AMS5812_0150_D:
        _pMin = AMS5812_0150_D_P_MIN;
        _pMax = AMS5812_0150_D_P_MAX;
        break;
    case AMS5812_0300_D:
        _pMin = AMS5812_0300_D_P_MIN;
        _pMax = AMS5812_0300_D_P_MAX;
        break;
    case AMS5812_0600_D:
        _pMin = AMS5812_0600_D_P_MIN;
        _pMax = AMS5812_0600_D_P_MAX;
        break;
    case AMS5812_1000_D:
        _pMin = AMS5812_1000_D_P_MIN;
        _pMax = AMS5812_1000_D_P_MAX;
        break;
    case AMS5812_0030_D_B:
        _pMin = AMS5812_0030_D_B_P_MIN;
        _pMax = AMS5812_0030_D_B_P_MAX;
        break;
    case AMS5812_0050_D_B:
        _pMin = AMS5812_0050_D_B_P_MIN;
        _pMax = AMS5812_0050_D_B_P_MAX;
        break;
    case AMS5812_0150_D_B:
        _pMin = AMS5812_0150_D_B_P_MIN;
        _pMax = AMS5812_0150_D_B_P_MAX;
        break;
    case AMS5812_0150_B:
        _pMin = AMS5812_0150_B_P_MIN;
        _pMax = AMS5812_0150_B_P_MAX;
        break;
    case AMS5812_0150_A:
        _pMin = AMS5812_0150_A_P_MIN;
        _pMax = AMS5812_0150_A_P_MAX;
        break;
    case AMS5812_0300_A:
        _pMin = AMS5812_0300_A_P_MIN;
        _pMax = AMS5812_0300_A_P_MAX;
        break;
  }
}

/* gets only the pressure value, PA */
float AMS5812::getPressure(){
  uint16_t digOutPmin = 3277;   // digital output at minimum pressure
  uint16_t digOutPmax = 29491;  // digital output at maximum pressure
  float pressure;  // pressure, pa
  uint16_t pressureCounts; // pressure digital output, counts

  // get pressure off transducer
  pressureCounts = readPressureBytes();

  // convert counts to pressure, PA
  pressure = ((pressureCounts - digOutPmin)/((digOutPmax - digOutPmin)/(_pMax - _pMin)) + _pMin) * _psi2pa;

  return pressure;
}

/* gets only the temperature value, C */
float AMS5812::getTemperature(){
  uint16_t digOutTmin = 3277;   // digital output at minimum temperature
  uint16_t digOutTmax = 29491;  // digital output at maximum temperature
  float temperature;  // temperature, C
  uint16_t pressureCounts; // pressure digital output, counts
  uint16_t temperatureCounts; // temperature digital output, counts

  // get pressure and temperature off transducer
  readBytes(&pressureCounts, &temperatureCounts);

  // convert counts to temperature, C
  temperature = ((temperatureCounts - digOutTmin)/((digOutTmax - digOutTmin)/(_tMax - _tMin)) + _tMin);

  return temperature;
}

/* gets both the pressure (PA) and temperature (C) values */
void AMS5812::getData(float* pressure, float* temperature){
  uint16_t digOutPmin = 3277;   // digital output at minimum pressure
  uint16_t digOutPmax = 29491;  // digital output at maximum pressure
  uint16_t digOutTmin = 3277;   // digital output at minimum temperature
  uint16_t digOutTmax = 29491;  // digital output at maximum temperature
  uint16_t pressureCounts; // pressure digital output, counts
  uint16_t temperatureCounts; // temperature digital output, counts

  // get pressure and temperature off transducer
  readBytes(&pressureCounts, &temperatureCounts);

  // convert counts to pressure, PA
  *pressure = ((pressureCounts - digOutPmin)/((digOutPmax - digOutPmin)/(_pMax - _pMin)) + _pMin) * _psi2pa;

  // convert counts to temperature, C
  *temperature = ((temperatureCounts - digOutTmin)/((digOutTmax - digOutTmin)/(_tMax - _tMin)) + _tMin);
}

#endif
