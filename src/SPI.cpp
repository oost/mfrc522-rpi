#include "SPI.h"

SPIObject SPI;

void SPIObject::beginTransaction(const SPISettings &s) {
  _address = 0;
  // std::cout << "Resetting address to 0 \n";
}

byte SPIObject::transfer(byte val) {

  if (_address == 0) {
    _address = val;
    return 0;
  }

  byte data[2]{_addres & 0x7E, val};
  wiringPiSPIDataRW(0, &data[0], 2);
  std::cout << "Address = " << std::hex << _address << "Wrote = " << std::hex
            << static_cast<int>(val) << " Read = " << std::hex
            << static_cast<int>(data[1]) << "\n";

  return data[1];
}

void SPIObject::endTransaction() {
  _address = 0;
  // std::cout << "Resetting address to 0 \n";
}