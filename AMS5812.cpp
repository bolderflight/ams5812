/*


*/

#include "Arduino.h"
#include "AMS5812.h"
#include <i2c_t3.h>  // I2C library

AMS5812::AMS5812(int address, String type){
  _address = address;
  _type = type;
}

void AMS5812::begin(){
  Wire.begin(I2C_MASTER, 0, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);
}

void AMS5812::readBytes(uint16_t* pressureCounts, uint16_t* temperatureCounts){
  byte b[4];

  // 4 bytes from address
  Wire.requestFrom(_address,4); 
  
  // put the data somewhere
  b[0] = Wire.read(); 
  b[1] = Wire.read();
  b[2] = Wire.read();
  b[3] = Wire.read();

  // assemble into a uint16_t
  *pressureCounts = (((uint16_t) (b[0]&0x7F)) <<8) + (((uint16_t) b[1]));
  *temperatureCounts = (((uint16_t) (b[2]&0x7F)) <<8) + (((uint16_t) b[3]));
}

