#ifndef SPI_H
#define SPI_H

#include "Arduino.h"
#include <iostream>

#define MFRC522_SPICLOCK 0
#define MSBFIRST 0
#define SPI_MODE0 0

struct SPISettings {
  SPISettings(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}
  int a, b, c;
};

class SPIObject {
public:
  inline void beginTransaction(const SPISettings &s) {
    _address = 0;
    // std::cout << "Resetting address to 0 \n";
  }

  inline byte transfer(byte val) {
    byte data[2];

    if (_address == 0) {
      _address = val;
      data[0] = (val << 1) & 0x7E;
      std::cout << "Setting address to " << std::hex
                << static_cast<int>(data[0]) << "\n";
      return 0;
    }
    data[1] = val;
    wiringPiSPIDataRW(0, &data[0], 2);
    std::cout << "Wrote " << std::hex << static_cast<int>(val) << " and read "
              << std::hex << static_cast<int>(data[1]) << "\n";

    return data[1];
  }

  inline void endTransaction() {
    _address = 0;
    // std::cout << "Resetting address to 0 \n";
  }

  SPIObject() : _address{0} {

    if (wiringPiSPISetup(0, MFRC522_SPICLOCK) < 0)
      throw "Couldn't initialize SPI";

    wiringPiSetupGpio();
  }

private:
  byte _address;
};

extern SPIObject SPI;

#endif