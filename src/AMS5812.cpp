/*
AMS5812.cpp
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

#include "Arduino.h"
#include "AMS5812.h"

/* constructor, I2C bus, sensor address, and transducer type */
AMS5812::AMS5812(TwoWire &bus,uint8_t address,Transducer type){
  // I2C bus
  _bus = &bus; 
  // I2C address
  _address = address; 
  // transducer type
  _type = type; 
}

/* starts the I2C communication and sets the pressure and temperature ranges using getTransducer */
int AMS5812::begin(){
  // starting the I2C bus
  _bus->begin();
  // setting the I2C clock
  _bus->setClock(_i2cRate);
  // setting the min and max pressure based on the chip
  getTransducer();
  // checking to see if we can talk with the sensor
  for (size_t i=0; i < _maxAttempts; i++) {
    _status = readBytes(&_pressureCounts,&_temperatureCounts);
    if (_status > 0) {break;}
    delay(10);
  }
  return _status;
}

/* reads data from the sensor */
int AMS5812::readSensor(){
  // get pressure and temperature off transducer
  _status = readBytes(&_pressureCounts, &_temperatureCounts);
  // convert counts to pressure, PA
  _data.Pressure_Pa = ((_pressureCounts - _digOutPmin)/((_digOutPmax - _digOutPmin)/(_pMax - _pMin)) + _pMin) * _psi2pa;
  // convert counts to temperature, C
  _data.Temp_C = ((_temperatureCounts - _digOutTmin)/((_digOutTmax - _digOutTmin)/(_tMax - _tMin)) + _tMin);
  return _status;
}

/* returns the pressure value, PA */
float AMS5812::getPressure_Pa(){
  return _data.Pressure_Pa;
}

/* returns the temperature value, C */
float AMS5812::getTemperature_C(){
  return _data.Temp_C;
}

/* sets the pressure and temperature range based on the chip */
void AMS5812::getTransducer(){
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

/* reads pressure and temperature and returns values in counts */
int AMS5812::readBytes(uint16_t* pressureCounts, uint16_t* temperatureCounts){
  // read from sensor
  _numBytes = _bus->requestFrom(_address,sizeof(_buffer));
  // put the data in buffer
  if (_numBytes == sizeof(_buffer)) {
    _buffer[0] = _bus->read(); 
    _buffer[1] = _bus->read();
    _buffer[2] = _bus->read();
    _buffer[3] = _bus->read();
    // assemble into a uint16_t
    *pressureCounts = (((uint16_t) (_buffer[0]&0x7F)) <<8) + (((uint16_t) _buffer[1]));
    *temperatureCounts = (((uint16_t) (_buffer[2]&0x7F)) <<8) + (((uint16_t) _buffer[3]));
    _status = 1;
  } else {
    _status = -1;
  }
  return _status;
}
