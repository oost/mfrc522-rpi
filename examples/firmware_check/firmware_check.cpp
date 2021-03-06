/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program to test your firmware.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples
 * see: https://github.com/miguelbalboa/rfid
 *
 * This example test the firmware of your MFRC522 reader module, only known
 * version can be checked. If the test passed it do not mean that your module is
 * faultless! Some modules have bad or broken antennas or the PICC is broken.
 * NOTE: for more informations read the README.rst
 *
 * @author Rotzbua
 * @license Released into the public domain.
 *
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro
 * Pro Micro Signal      Pin          Pin           Pin       Pin        Pin Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5 RST
 * SPI SS      SDA(SS)      10            53        D10        10 10 SPI MOSI
 * MOSI         11 / ICSP-4   51        D11        ICSP-4           16 SPI MISO
 * MISO         12 / ICSP-1   50        D12        ICSP-1           14 SPI SCK
 * SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include "MFRC522.h"
#include <SPI.h>
#include <Serial.h>

#define RST_PIN 25 // Configurable, see typical pin layout above
#define SS_PIN 8   // Configurable, see typical pin layout above

/**
 * Check firmware only once at startup
 */
int main() {
  SPI.begin();
  MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

  mfrc522.PCD_Init(); // Init MFRC522 module

  Serial.println(F("*****************************"));
  Serial.println(F("MFRC522 Digital self test"));
  Serial.println(F("*****************************"));
  mfrc522
      .PCD_DumpVersionToSerial(); // Show version of PCD - MFRC522 Card Reader
  Serial.println(F("-----------------------------"));
  Serial.println(F("Only known versions supported"));
  Serial.println(F("-----------------------------"));
  Serial.println(F("Performing test..."));
  bool result = mfrc522.PCD_PerformSelfTest(); // perform the test
  Serial.println(F("-----------------------------"));
  Serial.print(F("Result: "));
  if (result)
    Serial.println(F("OK"));
  else
    Serial.println(F("DEFECT or UNKNOWN"));
  Serial.println();
}
