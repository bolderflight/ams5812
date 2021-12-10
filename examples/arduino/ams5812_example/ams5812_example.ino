/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2021 Bolder Flight Systems
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
* and associated documentation files (the "Software"), to deal in the Software without restriction, 
* including without limitation the rights to use, copy, modify, merge, publish, distribute, 
* sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all copies or 
* substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "ams5812.h"

/*
* An AMS5812 object, which is a
* differential pressure sensure at I2C
* address of 0x06, on I2C bus 0,
* and is a AMS5812-0008-D
*/
bfs::Ams5812 diff_pres(&Wire, 0x06, bfs::Ams5812::AMS5812_0008_D);

void setup() {
  /* Serial to display data */
  Serial.begin(9600);
  while(!Serial){}
  Wire.begin();
  Wire.setClock(400000);
  /* Starting communication with the static pressure transducer */
  if (!diff_pres.Begin()) {
    Serial.println("Error communicating with sensor");
    while(1){}
  }
}

void loop() {
  /* Read the sensor */
  if (diff_pres.Read()) {
    /* Display the data */
    Serial.print(diff_pres.pres_pa(), 6);
    Serial.print("\t");
    Serial.println(diff_pres.die_temp_c(), 6);
  }
  delay(10);
}

