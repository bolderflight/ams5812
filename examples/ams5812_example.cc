/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
*/

#include "ams5812/ams5812.h"

sensors::Ams5812<&Wire, 0x06, sensors::Ams5812Type::AMS5812_0008_D> ams;

int main() {
  Serial.begin(115200);
  while(!Serial) {}
  Wire.begin();
  Wire.setClock(ams.i2c_clock());
  bool status = ams.Begin();
  if (!status) {
    Serial.println("Failed to communicate with sensor");
  } else {
    unsigned int t1, t2;
    while (1) {
      t1 = micros();
      status = ams.Read();
      t2 = micros();
      Serial.print(ams.pressure_pa());
      Serial.print("\t");
      Serial.print(ams.die_temperature_c());
      Serial.print("\t");
      Serial.print(status);
      Serial.print("\t");
      Serial.println(t2 - t1);
      delay(500);
    }
  }
}