#ifndef SPI_H
#define SPI_H

#include "Arduino.h"

#define MFRC522_SPICLOCK 0
#define MSBFIRST 0
#define SPI_MODE0 0

struct SPISetting {
  SPISettings(int a, int b, int c) : a(a), b(b), c(c) {}
  int a, b, c;
};

class SPIObject {
public:
  inline void beginTransaction(const SPISettings &s) {}

  inline byte transfer(byte val) {
    byte data[2];

    if (_address == 0) {
      data[0] = (val << 1) & 0x7E;
      return 0;
    }
    data[1] = val;
    wiringPiSPIDataRW(0, &data[0], 2);
    return data[1];
  }

  inline void endTransaction() { _address = 0; }

  SPIObject() : _address{0} {

    if (wiringPiSPISetup(0, MFRC522_SPICLOCK) < 0)
      throw "Couldn't initialize SPI";

    wiringPiSetupGpio();
  }

private:
  byte _address;
};

SPIObject SPI;

#endif