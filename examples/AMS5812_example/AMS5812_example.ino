/*
AMS5812_example.ino
Brian R Taylor
brian.taylor@bolderflight.com
2016-03-30

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

#include "AMS5812.h"
#include <i2c_t3.h> // I2C library

// an AMS5812 object, which is a
// static pressure sensure at I2C
// address of 0x10, on the Teensy
// LC I2C bus 1 (pins 22 and 23)
// and is a AMS5812-0150-B
AMS5812 staticPress(0x10,1,"teensyLC","AMS5812-0150-B");

void setup() {
  // serial to display data
  Serial.begin(9600);

  // starting communication with the 
  // static pressure transducer
  staticPress.begin();
}

void loop() {
  double pressure, temperature;
  uint16_t pressureCounts, temperatureCounts;

  // getting both the temperature (C) and pressure (PA)
  staticPress.getData(&pressure,&temperature);

  // displaying the data
  Serial.print(pressure,6);
  Serial.print("\t");
  Serial.println(temperature,6);
  delay(100);

  // getting just the pressure, PA
  pressure = staticPress.getPressure();
  delay(10);

  // getting just the temperature, C
  temperature = staticPress.getTemperature();
  delay(10);

  // displaying the data
  Serial.print(pressure,6);
  Serial.print("\t");
  Serial.println(temperature,6);
  delay(100);

  // getting the raw counts
  staticPress.readBytes(&pressureCounts, &temperatureCounts);
  Serial.print(pressureCounts);
  Serial.print("\t");
  Serial.println(temperatureCounts);
  delay(100);
}

