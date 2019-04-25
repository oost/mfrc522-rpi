#include "constants.h"
#include <iostream>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define SDA_PIN 8 // SDA
#define RST_PIN 25
#define byt u_int_8

void init() {
  if (wiringPiSPISetup(0, 1000000) < 0)
    throw "Couldn't initialize SPI";

  wiringPiSetupGpio();

  pinMode(SDA_PIN, OUTPUT);
  digitalWrite(SDA_PIN, HIGH);
}

void writeToRegister(byte addr, byte val) {
  std::cout << "Write, " << static_cast<int>(addr) << ","
            << static_cast<int>(val) << "\n";

#ifdef SELECT
  digitalWrite(SDA_PIN, LOW);
#endif

  byte data[2]{(addr << 1) & 0x7E, val};
  wiringPiSPIDataRW(_channel, &data[0], 2);

#ifdef SELECT
  digitalWrite(SDA_PIN, HIGH);
#endif
}

byte readFromRegister(byte addr) {

#ifdef SELECT
  digitalWrite(SDA_PIN, LOW);
#endif
  byte data[2]{((addr << 1) & 0x7E) | 0x80, 0};

  wiringPiSPIDataRW(_channel, &data[0], 2);
  std::cout << "Read," << static_cast<int>(addr) << ","
            << static_cast<int>(data[1]) << "\n";
#ifdef SELECT
  digitalWrite(SDA_PIN, HIGH);
#endif
  return data[1];
}

int main() {
  init();

  std::cout << "Reset\n";
  writeToRegister(CommandReg, MFRC522_SOFTRESET);
  writeToRegister(TModeReg, 0x8D); // Tauto=1; f(Timer) = 6.78MHz/TPreScaler
  writeToRegister(TPrescalerReg, 0x3E); // TModeReg[3..0] + TPrescalerReg
  writeToRegister(TReloadRegL, 30);
  writeToRegister(TReloadRegH, 0);
  writeToRegister(TxAutoReg, 0x40); // 100%ASK
  writeToRegister(ModeReg, 0x3D);   // CRC initial value 0x6363
  setBitMask(TxControlReg, 0x03);   // Turn antenna on.

  std::cout << "Version: " << std::hex
            << static_cast<int>(readFromRegister(VersionReg));
}