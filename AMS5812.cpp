/*


*/

#include "Arduino.h"
#include "AMS5812.h"
#include <i2c_t3.h>  // I2C library

AMS5812::AMS5812(int address, String type){
  _address = address;
  _type = type;
}

boolean AMS5812::begin(){
  Wire.begin(I2C_MASTER, 0, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);

  return true;
}

uint16_t AMS5812::readPresRegister(){
  byte b[2];
  uint16_t counts;

  // 2 bytes from address
  Wire.requestFrom(_address,2); 
  
  // put the data somewhere
  b[0] = Wire.read(); 
  b[1] = Wire.read();

  // assemble into a uint16_t
  counts = (((uint16_t) (b[0]&0x7F)) <<8) + (((uint16_t) b[1]));

  return counts;
}

