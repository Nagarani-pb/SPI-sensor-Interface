#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

// Define pins for SPI
#define RST_PIN 20   // Reset pin
#define SS_PIN 17    // Slave Select (CS)

// Create instance
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  SPI.begin();               // Init SPI bus
  rfid.PCD_Init();           // Init MFRC522
  Serial.println("RC522 RFID Reader Ready");
}

void loop() {
  // Look for a new card
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  // Show UID
  Serial.print("UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();
  delay(1000); // Wait a bit before next read
}
