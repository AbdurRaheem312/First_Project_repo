#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// Define pins
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo lockServo;

byte authorizedUID[] = { 0xDE, 0xAD, 0xBE, 0xEF }; Example UID

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
   lockServo.attach(7); // Attach servo to pin 7
  lockServo.write(0); // Lock position
  Serial.println("Place your RFID tag near the reader...");
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("Card UID: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  
  if (isAuthorized(mfrc522.uid.uidByte)) {
    Serial.println("Access Granted!");
    unlockDoor();
  } else {
    Serial.println("Access Denied!");
  }

  rfid.PICC_HaltA();
  delay(1000);  // Debounce delay
}

bool isAuthorized(byte *uid) {
  for (byte i = 0; i < 4; i++) {
    if (uid[i] != authorizedUID[i]) return false;
  }
  return true;
}
void unlockDoor() {
  lockServo.write(90);  // Unlock position
  delay(6000);          // Keep unlocked for 6 seconds
  lockServo.write(0);   // Lock again
}