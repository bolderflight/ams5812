//
// title:     AMS5812.h
// author:    Taylor, Brian R.
// email:     brian.taylor@bolderflight.com
// date:      2015-11-05 
// license: 
//

#ifndef AMS5812_h
#define AMS5812_h

#include "Arduino.h"

// min and max pressures, PSI
#define AMS5812_0000_D_P_MIN 0.0
#define AMS5812_0000_D_P_MAX 0.075
#define AMS5812_0001_D_P_MIN 0.0
#define AMS5812_0001_D_P_MAX 0.15
#define AMS5812_0000_D_B_P_MIN -0.075
#define AMS5812_0000_D_B_P_MAX 0.075
#define AMS5812_0001_D_B_P_MIN -0.15
#define AMS5812_0001_D_B_P_MAX 0.15
#define AMS5812_0003_D_P_MIN 0.0
#define AMS5812_0003_D_P_MAX 0.3
#define AMS5812_0008_D_P_MIN 0.0
#define AMS5812_0008_D_P_MAX 0.8
#define AMS5812_0015_D_P_MIN 0.0
#define AMS5812_0015_D_P_MAX 1.5
#define AMS5812_0003_D_B_P_MIN -0.3
#define AMS5812_0003_D_B_P_MAX 0.3
#define AMS5812_0008_D_B_P_MIN -0.8
#define AMS5812_0008_D_B_P_MAX 0.8
#define AMS5812_0015_D_B_P_MIN -1.5
#define AMS5812_0015_D_B_P_MAX 1.5
#define AMS5812_0030_D_P_MIN 0.0
#define AMS5812_0030_D_P_MAX 3.0
#define AMS5812_0050_D_P_MIN 0.0
#define AMS5812_0050_D_P_MAX 5.0
#define AMS5812_0150_D_P_MIN 0.0
#define AMS5812_0150_D_P_MAX 15.0
#define AMS5812_0300_D_P_MIN 0.0
#define AMS5812_0300_D_P_MAX 30.0
#define AMS5812_0600_D_P_MIN 0.0
#define AMS5812_0600_D_P_MAX 60.0
#define AMS5812_1000_D_P_MIN 0.0
#define AMS5812_1000_D_P_MAX 100.0
#define AMS5812_0030_D_B_P_MIN -3.0
#define AMS5812_0030_D_B_P_MAX 3.0
#define AMS5812_0050_D_B_P_MIN -5.0
#define AMS5812_0050_D_B_P_MAX 5.0
#define AMS5812_0150_D_B_P_MIN -15.0
#define AMS5812_0150_D_B_P_MAX 15.0
#define AMS5812_0150_B_P_MIN 11.0
#define AMS5812_0150_B_P_MAX 17.5
#define AMS5812_0150_A_P_MIN 0.0
#define AMS5812_0150_A_P_MAX 15.0
#define AMS5812_0300_A_P_MIN 0.0
#define AMS5812_0300_A_P_MAX 30.0

// temperature ranges, C
#define AMS5812_T_MIN -25.0
#define AMS5812_T_MAX 85.0

// conversion PSI to PA
#define PSI2PA 6894.76

class AMS5812{
  public:
    AMS5812(int address, String type);
    void begin();
    double getPressure();
    double getTemperature();
    void getData(double* pressure, double* temperature);
  private:
    int _address;
    String _type;
    double _pMin;
    double _pMax;
    double _tMin;
    double _tMax;
    void getTransducer();
    void readBytes(uint16_t* pressureCounts, uint16_t* temperatureCounts);
};

#endif
