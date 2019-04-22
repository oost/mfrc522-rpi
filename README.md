C++11 Raspberry Pi library for MFRC522
=====


Why this library?
---
If you own a Raspberry Pi and want to connect a simple MFRC522 card reader, there are plenty of Python and Node.JS 
libraries but surprisingly no easy to use C/C++ libraryfor Raspberry Pi. There are a few for Arduino but using them is not straightforward (this is actually a fork of an Arduino library).
 Given the resource limitations on a RPI (and in particular the RPI Zero), 
NodeJS/Python interpreted code quickly consumes almost all the RAM... 

Dependencies
---
- This library is using CMake for the build. 
- Uses [WiringPi](http://wiringpi.com) for the SPI communications. 

Connecting the Mifare Reader
---



| Pins |   SPI    | RPI`*` |
| ---- | :------: | :----: |
| 1    | SDA (SS) |   24   |
| 2    |   SCK    |   23   |
| 3    |   MOSI   |   19   |
| 4    |   MISO   |   21   |
| 5    |   IRQ    |  `x`   |
| 6    |   GND    |   6    |
| 7    |   RST    |   22   |
| 8    |  +3.3V   |   1    |

`x` Not needed  
`*` Physical pin numbers (see here for the [Pinout guide](https://pinout.xyz))


### Wiring
![Screenshot](https://github.com/oost/mfrc522-rpi/blob/master/documentation/rpi-mfrc522-wiring2.PNG)

### Which hardware is used?

![Screenshot](https://github.com/oost/mfrc522-rpi/blob/master/documentation/RC522.jpg)

Link to Amazon: [Link](https://www.amazon.com/SunFounder-Mifare-Antenna-Proximity-Arduino/dp/B00E0ODLWQ)

### Sources

- https://github.com/miguelbalboa/rfid
- https://github.com/ljos/MFRC522
- https://github.com/firsttris/mfrc522-rpi


## License
See the [LICENSE](LICENSE.md) file for license rights and limitations (MIT).