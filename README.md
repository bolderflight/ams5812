# AMS5812
Library for communicating with [AMSYS AMS 5812](http://www.amsys.info/products/ams5812.htm) pressure transducers using Teensy 3.1/3.2 and 3.5 devices.

# Description
The AMSYS AMS 5812 pressure transducers are fully signal conditioned, amplified, and temperature compensated over a temperature range of -25 to +85 C. These sensors generate data with high precision, high stability and low drift. Digital measurements are sampled with a 14 bit resolution. The AMSYS AMS 5812 sensors are available in a wide variety of pressure ranges and in configurations suited for barometric, differential, and bidirectional differential measurement.

This library communicates with the AMS 5812 sensors using an I2C interface. The default I2C address for the AMS 5812 is 0x78; however, a USB starter kit may be purchased to enable programming additional slave addresses. Pressure and temperature data can be provided up to a rate of 2 kHz.

# Usage
This library uses the [i2c_t3 enhanced I2C library](https://github.com/nox771/i2c_t3) for Teensy 3.x/LC devices.

Simply clone or download and extract the zipped library into your Arduino/libraries folder.

**AMS5812(uint8_t address, uint8_t bus, String type)**
An AMS5812 object should be declared, specifying the AMS 5812 I2C address, the I2C bus, and the AMS 5812 sensor type. For example, the following code declares an AMS5812 object called *dPress* with an AMS5812-0008-D sensor located on I2C bus 0 and an I2C address of 0x06:

```C++
AMS5812 dPress(0x06,0,"AMS5812-0008-D");
```

**void begin()**
This should be called in your setup function. It initializes the I2C communication and sets the minimum and maximum pressure and temperature values based on the AMS 5812 sensor.

```C++
dPress.begin();
```

**float getPressure()**
*getPressure()* samples the AMS 5812 sensor and returns the pressure measurement as a float with units of Pascal (Pa).

```C++
float pressure;
pressure = dPress.getPressure();
```

**float getTemperature()**
*getTemperature()* samples the AMS 5812 sensor and returns the temperature measurement as a float with units of Celsius (C).

```C++
float temperature;
temperature = dPress.getTemperature();
```

**void getData(float* pressure, float* temperature)**
*getData(float&ast; pressure, float&ast; temperature)* samples the AMS 5812 sensor and returns the pressure measurement as a float with units of Pascal (Pa) and temperature measurement as a float with units of Celsius (C).

```C++
float pressure, temperature;
dPress.getData(&pressure,&temperature);
```

# Wiring and Pullups
Please refer to the [AMSYS AMS 5812 datasheet](https://github.com/bolderflight/AMS5812/blob/master/docs/ams5812.pdf) and the [Teensy pinout diagrams](https://www.pjrc.com/teensy/pinout.html).

The silver dot on the AMSYS AMS 5812 marks the location of Pin 1. The AMS 5812 pinout is:

   * Pin 2: Ground
   * Pin 4: SDA
   * Pin 5: SCL
   * Pin 7: VCC, this should be a 4.75V to 5.25V power source. If your Teensy is supplied with 5V power, this can be from Teensy Vin.

The Teensy pinout is:

   * Teensy 3.1/3.2:
      * Bus 0 - Pin 18: SDA, Pin 19: SCL
      * Bus 1 - Pin 29: SCL, Pin 30: SDA
   * Teensy 3.5:
      * Bus 0 - Pin 18: SDA, Pin 19: SCL
      * Bus 1 - Pin 37: SCL, Pin 38: SDA
      * Bus 2 - Pin 3: SCL, Pin 4: SDA

4.7 kOhm resistors should be used as pullups on SDA and SCL, these resistors should pullup with a 5V source.
