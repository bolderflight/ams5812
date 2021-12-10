/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2021 Bolder Flight Systems Inc
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the “Software”), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#include "ams5812/ams5812.h"

bfs::Ams5812 ams(&Wire, 0x06, bfs::Ams5812::AMS5812_0008_D);

int main() {
  Serial.begin(115200);
  while(!Serial) {}
  bool status = ams.Begin();
  unsigned int t1, t2;
  while (1) {
    t1 = micros();
    status = ams.Read();
    t2 = micros();
    float p = ams.pressure_pa();
    float t = ams.die_temperature_c();
    Serial.print(p);
    Serial.print("\t");
    Serial.print(t);
    Serial.print("\t");
    Serial.print(status);
    Serial.print("\t");
    Serial.println(t2 - t1);
    delay(500);
  }
}