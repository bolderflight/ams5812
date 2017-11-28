# AMS5812
Arduino library for communicating with [Analog Microelectronics AMS 5812](http://www.analog-micro.com/en/products/sensors/pressuresensors/ams5812/) pressure transducers.

# Description
The Analog Microelectronics AMS 5812 pressure transducers are fully signal conditioned, amplified, and temperature compensated over a temperature range of -25 to +85 C. These sensors generate data with high precision, high stability and low drift. Digital measurements are sampled with a 14 bit resolution. The AMS 5812 sensors are available in a wide variety of pressure ranges and in configurations suited for barometric, differential, and bidirectional differential measurement.

# Usage
This library communicates with the AMS 5812 sensors using an I2C interface. The default I2C address for the AMS 5812 is 0x78; however, a USB starter kit may be purchased to enable programming additional slave addresses. Pressure and temperature data can be provided up to a rate of 2 kHz.

## Installation
Simply clone or download and extract the zipped library into your Arduino/libraries folder.

## Function Description
### Object Declaration
**AMS5812(TwoWire &bus,uint8_t address,AMS5915::Transducer type)**
An AMS5812 object should be constructed, specifying the I2C bus, AMS 5812 I2C address, and the AMS 5812 transducer type. The enumerated transducer types are:

| Sensor Name       | Enumerated Type  | Pressure Type              | Pressure Range       |
| -----------       | ---------------  | ---------------            | ---------------      |
| AMS 5812-0000-D   | AMS5812_0000_D   | differential / relative    | 0...517 Pa           |
| AMS 5812-0001-D   | AMS5812_0001_D   | differential / relative    | 0...1034 Pa          |
| AMS 5812-0000-D-B | AMS5812_0000_D_B | bidirectional differential | -517...+517 Pa       |
| AMS 5812-0001-D-B | AMS5812_0001_D_B | bidirectional differential | -1034...+1034 Pa     |
| AMS 5812-0003-D   | AMS5812_0003_D   | differential / relative    | 0...2068 Pa          |
| AMS 5812-0008-D   | AMS5812_0008_D   | differential / relative    | 0...5516 Pa          |
| AMS 5812-0015-D   | AMS5812_0015_D   | differential / relative    | 0...10342 Pa         |
| AMS 5812-0003-D-B | AMS5812_0003_D_B | bidirectional differential | -2068...+2068 Pa     |
| AMS 5812-0008-D-B | AMS5812_0008_D_B | bidirectional differential | -5516...+5516 Pa     |
| AMS 5812-0015-D-B | AMS5812_0015_D_B | bidirectional differential | -10342...+10342 Pa   |
| AMS 5812-0030-D   | AMS5812_0030_D   | differential / relative    | 0...20684 Pa         |
| AMS 5812-0050-D   | AMS5812_0050_D   | differential / relative    | 0...34474 Pa         |
| AMS 5812-0150-D   | AMS5812_0150_D   | differential / relative    | 0...103421 Pa        |
| AMS 5812-0300-D   | AMS5812_0300_D   | differential / relative    | 0...206843 Pa        |
| AMS 5812-0600-D   | AMS5812_0600_D   | differential / relative    | 0...413685 Pa        |
| AMS 5812-1000-D   | AMS5812_1000_D   | differential / relative    | 0...689476 Pa        |
| AMS 5812-0030-D-B | AMS5812_0030_D_B | bidirectional differential | -20684...+20684 Pa   |
| AMS 5812-0050-D-B | AMS5812_0050_D_B | bidirectional differential | -34474...+34474 Pa   |
| AMS 5812-0150-D-B | AMS5812_0150_D_B | bidirectional differential | -103421...+103421 Pa |
| AMS 5812-0150-B   | AMS5812_0150_B   | barometric                 | 75842...120658 Pa    |
| AMS 5812-0150-A   | AMS5812_0150_A   | absolute                   | 0...103421 Pa        |
| AMS 5812-0300-A   | AMS5812_0300_A   | absolute                   | 0...206843 Pa        |

For example, the following code declares an AMS5812 object called *dPress* with an AMS5812-0008-D sensor located on I2C bus 0 and an I2C address of 0x06:

```C++
AMS5812 dPress(Wire,0x06,AMS5812::AMS5812_0008_D);
```

### Setup Functions
**int begin()**
This should be called in your setup function. It initializes and tests the I2C communication and sets the minimum and maximum pressure and temperature values based on the AMS 5812 sensor. The return value is positive if successful in initializing communication with the pressure transducer and negative if it is not successful.

```C++
dPress.begin();
```

### Data Collection Functions
**int readSensor()** reads the sensor and stores the newest data in a buffer, it should be called every time you would like to retrieve the most current data from the sensor. This function returns a positive value if it's succesful in retrieving the data and negative if not succesful.

```C++
dPress.readSensor();
```

**float getPressure_Pa()** gets the pressure value from the data buffer and returns it in units of Pascal.

```C++
float pressure;
pressure = dPress.getPressure_Pa();
```

**float getTemperature_C()** gets the temperature value from the data buffer and returns it in units of degrees Celsius.

```C++
float temperature;
temperature = dPress.getTemperature_C();
```

## Example List
* **AMS5812_example**: demonstrates declaring an object, initializing the sensor, and collecting data. In this example the sensor is an AMS5812-0008-D with a sensor address of 0x06 located on I2C bus 0. 

# Wiring and Pullups
Please refer to the [Analog Microelectronics AMS 5812 datasheet](https://github.com/bolderflight/AMS5812/blob/master/docs/ams5812.pdf) and your microcontroller's pinout diagram.

The silver dot on the AMS 5812 marks the location of Pin 1. The AMS 5812 pinout is:

   * Pin 2: Ground
   * Pin 4: SDA
   * Pin 5: SCL
   * Pin 7: VCC, this should be a 4.75V to 5.25V power source.

4.7 kOhm resistors should be used as pullups on SDA and SCL, these resistors should pullup with a 5V source.
