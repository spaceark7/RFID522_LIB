#include "rfid522.h"
#include <SPI.h>
#include <MFRC522.h>

// Path: rfid522.cpp

RFID522::RFID522(int _SSPIN,  int _RSTPIN)
{
  _SSPIN = _SSPIN;
  _RSTPIN = _RSTPIN;
  if ( _SSPIN == 0 || _RSTPIN == 0) {
    Serial.println(F("RFID522: SS and RST pins are not defined"));
    return ;
  }
  // Create an instance of MFRC522
  MFRC522 mfrc522(_SSPIN, _RSTPIN);
  _rfid = mfrc522;
}
  


void printHex(byte *buffer, byte bufferSize);
/*
  Member Methods
*/
void RFID522::beginConnection()
{
  // Initialize the SPI bus
  SPI.begin();
  // Init MFRC522
  _rfid.PCD_Init();
  
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  // print if the RFID is connected or not
  if ( ! _rfid.PCD_PerformSelfTest()) {
    Serial.println(F("RFID connection failed"));
    return ;
  }
  Serial.println(F("RFID connection successful"));
}

void RFID522::readRFIDTag()
{
  // Look for new cards
  if ( ! _rfid.PICC_IsNewCardPresent()) {
    return;
    }
  // Select one of the cards
  if ( ! _rfid.PICC_ReadCardSerial()) {
    return;
  }
  // Dump debug info about the card; PICC_HaltA() is automatically called
  _rfid.PICC_DumpToSerial(&(_rfid.uid));
  // Halt PICC
  _rfid.PICC_HaltA();
  // Stop encryption on PCD
  _rfid.PCD_StopCrypto1();

  for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = _rfid.uid.uidByte[i];
  }

  printHex(_rfid.uid.uidByte, _rfid.uid.size);

  // return nuidPICC;
}

char *RFID522::getRFIDTagValue()
{
    static char str[20]; // Assuming nuidPICC has 10 bytes. Each byte will be represented by 2 hex characters.
    str[0] = '\0'; // Start with an empty string

    for(uint8_t i = 0; i < sizeof(nuidPICC); ++i) {
        char buffer[3];
        sprintf(buffer, "%02X", nuidPICC[i]);
        strcat(str, buffer);
    }

    return str;
}

/**
 * Helper function to print a byte array as hex values to Serial.
*/
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
};
