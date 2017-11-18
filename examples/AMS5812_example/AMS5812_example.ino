/*
AMS5812_example.ino
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

#include "AMS5812.h"

// an AMS5812 object, which is a
// differential pressure sensure at I2C
// address of 0x06, on I2C bus 0,
// and is a AMS5812-0008-D
AMS5812 dPress(Wire,0x06,AMS5812::AMS5812_0008_D);

void setup() {
  // serial to display data
  Serial.begin(9600);
  while(!Serial){}

  // starting communication with the 
  // static pressure transducer
  if (dPress.begin() < 0) {
    Serial.println("Error communicating with sensor, check wiring and I2C address");
    while(1){}
  }
}

void loop() {
  // read the sensor
  dPress.readSensor();

  // displaying the data
  Serial.print(dPress.getPressure_Pa(),6);
  Serial.print("\t");
  Serial.println(dPress.getTemperature_C(),6);
  delay(10);
}

