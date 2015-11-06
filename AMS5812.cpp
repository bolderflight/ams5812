//
// title:     AMS5812.cpp
// author:    Taylor, Brian R.
// email:     brian.taylor@bolderflight.com
// date:      2015-11-05 
// license: 
//

#include "Arduino.h"
#include "AMS5812.h"
#include <i2c_t3.h>  // I2C library

/* AMS5812 object, input the I2C address and chip name (i.e. "AMS5812-0150-B") */
AMS5812::AMS5812(int address, String type){
  _address = address; // I2C address
  _type = type; // string, transducer type
}

/* starts the I2C communication and sets the pressure and temperature ranges using getTransducer */
void AMS5812::begin(){

  // starting the I2C
  Wire.begin(I2C_MASTER, 0, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);

  // setting the min and max pressure and temperature based on the chip
  getTransducer();
}

/* reads pressure and temperature and returns values in counts */
void AMS5812::readBytes(uint16_t* pressureCounts, uint16_t* temperatureCounts){
  byte b[4]; // buffer

  // 4 bytes from address
  Wire.requestFrom(_address,4); 
  
  // put the data in buffer
  b[0] = Wire.read(); 
  b[1] = Wire.read();
  b[2] = Wire.read();
  b[3] = Wire.read();

  // assemble into a uint16_t
  *pressureCounts = (((uint16_t) (b[0]&0x7F)) <<8) + (((uint16_t) b[1]));
  *temperatureCounts = (((uint16_t) (b[2]&0x7F)) <<8) + (((uint16_t) b[3]));
}

/* reads pressure and returns values in counts */
uint16_t AMS5812::readPressureBytes(){
  byte b[2]; // buffer

  // 2 bytes from address
  Wire.requestFrom(_address,4); 
  
  // put the data in buffer
  b[0] = Wire.read(); 
  b[1] = Wire.read();

  // assemble into a uint16_t
  return (((uint16_t) (b[0]&0x7F)) <<8) + (((uint16_t) b[1]));
}

/* sets the pressure and temperature range based on the chip */
void AMS5812::getTransducer(){

  // setting the min and max temperature
  _tMin = AMS5812_T_MIN;
  _tMax = AMS5812_T_MAX;

  // setting the min and max pressures based on which transducer it is
  if(_type.equals("AMS5812-0000-D")){
    _pMin = AMS5812_0000_D_P_MIN;
    _pMax = AMS5812_0000_D_P_MAX;
  }

  if(_type.equals("AMS5812-0001-D")){
    _pMin = AMS5812_0001_D_P_MIN;
    _pMax = AMS5812_0001_D_P_MAX;
  }

  if(_type.equals("AMS5812-0000-D-B")){
    _pMin = AMS5812_0000_D_B_P_MIN;
    _pMax = AMS5812_0000_D_B_P_MAX;
  }

  if(_type.equals("AMS5812-0001-D-B")){
    _pMin = AMS5812_0001_D_B_P_MIN;
    _pMax = AMS5812_0001_D_B_P_MAX;
  }

  if(_type.equals("AMS5812-0003-D")){
    _pMin = AMS5812_0003_D_P_MIN;
    _pMax = AMS5812_0003_D_P_MAX;
  }

  if(_type.equals("AMS5812-0008-D")){
    _pMin = AMS5812_0008_D_P_MIN;
    _pMax = AMS5812_0008_D_P_MAX;
  }

  if(_type.equals("AMS5812-0015-D")){
    _pMin = AMS5812_0015_D_P_MIN;
    _pMax = AMS5812_0015_D_P_MAX;
  }

  if(_type.equals("AMS5812-0003-D-B")){
    _pMin = AMS5812_0003_D_B_P_MIN;
    _pMax = AMS5812_0003_D_B_P_MAX;
  }

  if(_type.equals("AMS5812-0008-D-B")){
    _pMin = AMS5812_0008_D_B_P_MIN;
    _pMax = AMS5812_0008_D_B_P_MAX;
  }

  if(_type.equals("AMS5812-0015-D-B")){
    _pMin = AMS5812_0015_D_B_P_MIN;
    _pMax = AMS5812_0015_D_B_P_MAX;
  }

  if(_type.equals("AMS5812-0030-D")){
    _pMin = AMS5812_0030_D_P_MIN;
    _pMax = AMS5812_0030_D_P_MAX;
  }

  if(_type.equals("AMS5812-0050-D")){
    _pMin = AMS5812_0050_D_P_MIN;
    _pMax = AMS5812_0050_D_P_MAX;
  }

  if(_type.equals("AMS5812-0150-D")){
    _pMin = AMS5812_0150_D_P_MIN;
    _pMax = AMS5812_0150_D_P_MAX;
  }

  if(_type.equals("AMS5812-0300-D")){
    _pMin = AMS5812_0300_D_P_MIN;
    _pMax = AMS5812_0300_D_P_MAX;
  }

  if(_type.equals("AMS5812-0600-D")){
    _pMin = AMS5812_0600_D_P_MIN;
    _pMax = AMS5812_0600_D_P_MAX;
  }

  if(_type.equals("AMS5812-1000-D")){
    _pMin = AMS5812_1000_D_P_MIN;
    _pMax = AMS5812_1000_D_P_MAX;
  }

  if(_type.equals("AMS5812-0030-D-B")){
    _pMin = AMS5812_0030_D_B_P_MIN;
    _pMax = AMS5812_0030_D_B_P_MAX;
  }

  if(_type.equals("AMS5812-0050-D-B")){
    _pMin = AMS5812_0050_D_B_P_MIN;
    _pMax = AMS5812_0050_D_B_P_MAX;
  }

  if(_type.equals("AMS5812-0150-D-B")){
    _pMin = AMS5812_0150_D_B_P_MIN;
    _pMax = AMS5812_0150_D_B_P_MAX;
  }

  if(_type.equals("AMS5812-0150-B")){
    _pMin = AMS5812_0150_B_P_MIN;
    _pMax = AMS5812_0150_B_P_MAX;
  }

  if(_type.equals("AMS5812-0150-A")){
    _pMin = AMS5812_0150_A_P_MIN;
    _pMax = AMS5812_0150_A_P_MAX;
  }

  if(_type.equals("AMS5812-0300-A")){
    _pMin = AMS5812_0300_A_P_MIN;
    _pMax = AMS5812_0300_A_P_MAX;
  }

}

/* gets only the pressure value, PA */
double AMS5812::getPressure(){
  uint16_t digOutPmin = 3277;   // digital output at minimum pressure
  uint16_t digOutPmax = 29491;  // digital output at maximum pressure
  double pressure;  // pressure, pa
  uint16_t pressureCounts; // pressure digital output, counts

  // get pressure off transducer
  pressureCounts = readPressureBytes();

  // convert counts to pressure, PA
  pressure = ((pressureCounts - digOutPmin)/((digOutPmax - digOutPmin)/(_pMax - _pMin)) + _pMin) * PSI2PA;

  return pressure;
}

/* gets only the temperature value, C */
double AMS5812::getTemperature(){
  uint16_t digOutTmin = 3277;   // digital output at minimum temperature
  uint16_t digOutTmax = 29491;  // digital output at maximum temperature
  double temperature;  // temperature, C
  uint16_t pressureCounts; // pressure digital output, counts
  uint16_t temperatureCounts; // temperature digital output, counts

  // get pressure and temperature off transducer
  readBytes(&pressureCounts, &temperatureCounts);

  // convert counts to temperature, C
  temperature = ((temperatureCounts - digOutTmin)/((digOutTmax - digOutTmin)/(_tMax - _tMin)) + _tMin);

  return temperature;
}

/* gets both the pressure (PA) and temperature (C) values */
void AMS5812::getData(double* pressure, double* temperature){
  uint16_t digOutPmin = 3277;   // digital output at minimum pressure
  uint16_t digOutPmax = 29491;  // digital output at maximum pressure
  uint16_t digOutTmin = 3277;   // digital output at minimum temperature
  uint16_t digOutTmax = 29491;  // digital output at maximum temperature
  uint16_t pressureCounts; // pressure digital output, counts
  uint16_t temperatureCounts; // temperature digital output, counts

  // get pressure and temperature off transducer
  readBytes(&pressureCounts, &temperatureCounts);

  // convert counts to pressure, PA
  *pressure = ((pressureCounts - digOutPmin)/((digOutPmax - digOutPmin)/(_pMax - _pMin)) + _pMin) * PSI2PA;

  // convert counts to temperature, C
  *temperature = ((temperatureCounts - digOutTmin)/((digOutTmax - digOutTmin)/(_tMax - _tMin)) + _tMin);
}
