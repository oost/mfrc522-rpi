/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program to test your firmware.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * This example test the firmware of your MFRC522 reader module, only known version can be checked. If the test passed
 * it do not mean that your module is faultless! Some modules have bad or broken antennas or the PICC is broken.
 * NOTE: for more informations read the README.rst
 * 
 * @author Rotzbua
 * @license Released into the public domain.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         22          // Configurable, see typical pin layout above
#define SS_PIN          24         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

/**
 * Check firmware only once at startup
 */
int main() {
  
  mfrc522.PCD_Init();   // Init MFRC522 module
  
  std::cout << "*****************************";
  std::cout << "MFRC522 Digital self test";
  std::cout << "*****************************";
  mfrc522.PCD_DumpVersionToSerial();  // Show version of PCD - MFRC522 Card Reader
  std::cout << "-----------------------------";
  std::cout << "Only known versions supported";
  std::cout << "-----------------------------";
  std::cout << "Performing test...";
  bool result = mfrc522.PCD_PerformSelfTest(); // perform the test
  std::cout << "-----------------------------";
  std::cout << "Result: ";
  if (result)
    std::cout << "OK";
  else
    std::cout << "DEFECT or UNKNOWN";

}
