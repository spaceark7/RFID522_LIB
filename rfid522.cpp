#include 'rfid522.h'

// Path: rfid522.cpp

RFID522::RFID522(int _SSPIN,  int _RSTPIN)
{
  _SSPIN = _SSPIN;
  _RSTPIN = _RSTPIN;
}

void RFID522::beginRFIDConnection()
{
  SPI.begin();
  MFRC522 mfrc522(_SSPIN, _RSTPIN);   // Create MFRC522 instance
  mfrc522.PCD_Init();
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  // print if the RFID is connected or not
  if ( ! mfrc522.PCD_PerformSelfTest()) {
    Serial.println(F("RFID connection failed"));
    return;
  }
}
