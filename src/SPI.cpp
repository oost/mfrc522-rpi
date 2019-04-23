#include "SPI.h"

SPIObject SPI;

void SPIObject::beginTransaction(const SPISettings &s) { _address = 0; }

byte SPIObject::transfer(byte val) {

  if (_address == 0) {
    std::cout << "Set Address = " << static_cast<int>(val) << "\n";

    _address = val;
    return 0;
  }

  byte data[2]{_address & 0x7E, val};
  wiringPiSPIDataRW(0, &data[0], 2);
  std::cout << "Address = " << static_cast<int>(_address)
            << " Data[0] = " << static_cast<int>(data[0])
            << " Data[1] = " << static_cast<int>(data[1])
            << " Wrote = " << static_cast<int>(val)
            << " Read = " << static_cast<int>(data[1]) << "\n";

  return data[1];
}

void SPIObject::endTransaction() { _address = 0; }