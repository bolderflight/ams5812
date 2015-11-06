/*



*/

#ifndef AMS5812_h
#define AMS5812_h

#include "Arduino.h"

class AMS5812{
	public:
		AMS5812(int address);
		void initialize();
	private:
		int _address;
}

#endif
