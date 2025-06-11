#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// Define pins
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);