/*



*/

#ifndef AMS5812_h
#define AMS5812_h

#include "Arduino.h"

class AMS5812{
  public:
    AMS5812(int address, String type);
    void begin();
  private:
    int _address;
    String _type;
    void readBytes(uint16_t* pressureCounts, uint16_t* temperatureCounts);
};

#endif
