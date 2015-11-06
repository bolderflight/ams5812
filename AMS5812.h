/*



*/

#ifndef AMS5812_h
#define AMS5812_h

#include "Arduino.h"

class AMS5812{
  public:
    AMS5812(int address, String type);
    boolean begin();
  private:
    int _address;
    String _type;
    uint16_t readPresRegister();
};

#endif
