# AMS5812
Library for communicating with [AMSYS AMS 5812](http://www.amsys.info/products/ams5812.htm) pressure transducers using Teensy 3.1/3.2 devices.

# Description
The AMSYS AMS 5812 pressure transducers are fully signal conditioned, amplified, and temperature compensated over a temperature range of -25 to +85 C. These sensors generate data with high precision, high stability and low drift. Digital measurements are sampled with a 14 bit resolution. The AMSYS AMS 5812 sensors are available in a wide variety of pressure ranges and in configurations suited for barometric, differential, and bidirectional differential measurement.

This library communicates with the AMS 5812 sensors using an I2C interface. The default I2C address for the AMS 5812 is 0x78; however, a USB starter kit may be purchased to enable programming additional slave addresses. Pressure and temperature data can be provided up to a rate of 1 kHz.

# Usage
This library uses the [i2c_t3 enhanced I2C library](https://github.com/nox771/i2c_t3) for Teensy 3.1/3.2 devices.

Simply clone or download and extract the zipped library into your Arduino/libraries folder.

**AMS5812(int address, int bus, String type)**
An AMS5812 object should be declared, specifying the AMS 5812 I2C address, the I2C bus, and the AMS 5812 sensor type. For example, the following code declares an AMS5812 object called *dPress* with an AMS5812-0008-D sensor located on I2C bus 0 and an I2C address of 0x06:

```C++
AMS5812 dPress(0x06,0,"AMS5812-0008-D");
```

**void begin()**
This should be called in your setup function. It initializes the I2C communication and sets the minimum and maximum pressure and temperature values based on the AMS 5812 sensor.

```C++
dPress.begin();
```

**double getPressure()**
*getPressure()* samples the AMS 5812 sensor and returns the pressure measurement as a double with units of Pascal (Pa).

```C++
double pressure;
pressure = dPress.getPressure();
```

**double getTemperature()**
*getTemperature()* samples the AMS 5812 sensor and returns the temperature measurement as a double with units of Celsius (C).

```C++
double temperature;
temperature = dPress.getTemperature();
```

**void getData(double* pressure, double* temperature)**
*getData(double* pressure, double* temperature)* samples the AMS 5812 sensor and returns the pressure measurement as a double with units of Pascal (Pa) and temperature measurement as a double with units of Celsius (C).

```C++
double pressure, temperature;
dPress.getData(&pressure,&temperature);
```

# Wiring and Pullups
Please refer to the [AMSYS AMS 5812 datasheet](http://www.analogmicro.de/_pages/sens/ams5812/ams5812_data_sheet.pdf) and the [Teensy pinout diagrams](https://www.pjrc.com/teensy/pinout.html).

The silver dot on the AMSYS AMS 5812 marks the location of Pin 1. Ground (AMS 5812, Pin 2) should be connected to Teensy ground (GND) and VCC (AMS 5812, Pin 7) should be connected to 5V. If your Teensy is supplied with 5V power, this can be from Teensy Vin. AMS 5812 SDA (AMS 5812, Pin 4) and SCL (AMS 5812, Pin 5) should be connected to SDA and SCL on the Teensy. For Teensy 3.1/3.2 using I2C bus 0, these are pins 18 and 19, respectively. For Teensy 3.1/3.2 using I2C bus 1, these are pins 30 and 29.

4.7 kOhm resistors should be used as pullups on SDA and SCL. For Teensy 3.1/3.2, these resistors should pullup with a 5V source.
