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