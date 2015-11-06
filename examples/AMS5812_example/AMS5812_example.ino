//
// title:     AMS5812_example.ino
// author:    Taylor, Brian R.
// email:     brian.taylor@bolderflight.com
// date:      2015-11-05 
// license: 
//

#include "AMS5812.h"
#include <i2c_t3.h> // I2C library

// an AMS5812 object, which is a
// static pressure sensure at I2C
// address of 0x02 and is a
// AMS5812-0150-B
AMS5812 staticPress(0x02,"AMS5812-0150-B");

void setup() {
  // serial to display data
  Serial.begin(9600);

  // starting communication with the 
  // static pressure transducer
  staticPress.begin();
}

void loop() {
  double pressure;
  double temperature;

  // getting both the temperature (C) and pressure (PA)
  staticPress.getData(&pressure,&temperature);

  // displaying the data
  Serial.print(pressure,6);
  Serial.print("\t");
  Serial.println(temperature,6);
  delay(100);

  // getting just the pressure, PA
  pressure = staticPress.getPressure();
  delay(100);

  // getting just the temperature, C
  temperature = staticPress.getTemperature();
  delay(100);

  // displaying the data
  Serial.print(pressure,6);
  Serial.print("\t");
  Serial.println(temperature,6);
  delay(100);
}

