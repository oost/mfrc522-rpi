#include "SPI.h"

SPIObject SPI;

void SPIObject::beginTransaction(const SPISettings &s) { _address = 0; }

byte SPIObject::transfer(byte val) {

  if (_address == 0) {
    _address = val;
    return 0;
  }

  byte data[2]{_address & 0x7E, val};
  wiringPiSPIDataRW(0, &data[0], 2);
  std::cout << "Address = " << std::hex << static_cast<int>(_address)
            << " Data[0] = " << std::hex << static_cast<int>(data[0])
            << " Data[1] = " << std::hex << static_cast<int>(data[1])
            << " Wrote = " << std::hex << static_cast<int>(val)
            << " Read = " << std::hex << static_cast<int>(data[1]) << "\n";

  return data[1];
}

void SPIObject::endTransaction() { _address = 0; }