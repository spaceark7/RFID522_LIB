/*
This Library is used to read the RFID tags and return the tag number.

*/

#ifndef RFID522_H
#define RFID522_H

#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>

class RFID522
{
  public: 
    RFID522(int _SSPIN,  int _RSTPIN);
    void beginConnection();
    void readRFIDTag();
    char* getRFIDTagValue();

    private:
      byte nuidPICC[4];
      int _SSPIN;
      int _RSTPIN;
      MFRC522 _rfid;
};



#endif