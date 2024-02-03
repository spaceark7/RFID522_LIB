/*
    * This is a basic example
    * This example will read the RFID tag and print the tag number in the serial monitor
    * The RFID tag number is a 4 byte number
    * 
    * in the future, we will expand this library for more features
    * Just Basic things for now
*/

#include <rfid522.h>

#define SS_PIN D4
#define RST_PIN D3

RFID522 rfid522(SS_PIN, RST_PIN);


void setup() {
  Serial.begin(9600);

  // Start the RFID connection
  rfid522.beginConnection();

}

void loop() {
    // Read the RFID tag
    rfid522.readRFIDTag();
    delay(1000);
}