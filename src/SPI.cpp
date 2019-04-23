#include "SPI.h"

SPIObject SPI;

void SPIObject::beginTransaction(const SPISettings &s) {
  _address = 0;
  // std::cout << "Resetting address to 0 \n";
}

byte SPIObject::transfer(byte val) {
  byte data[2];

  if (_address == 0) {
    _address = val;
    data[0] = val & 0x7E;
    std::cout << "Setting address to " << std::hex << static_cast<int>(data[0])
              << "\n";
    return 0;
  }
  data[1] = val;
  wiringPiSPIDataRW(0, &data[0], 2);
  std::cout << "Wrote " << std::hex << static_cast<int>(val) << " and read "
            << std::hex << static_cast<int>(data[1]) << "\n";

  return data[1];
}

void SPIObject::endTransaction() {
  _address = 0;
  // std::cout << "Resetting address to 0 \n";
}