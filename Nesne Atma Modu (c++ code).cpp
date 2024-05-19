#include <Arduino.h>

// Sensör ve motor pin tanımlamaları
const int distanceSensorPin = A0;
const int leftMotorPin = 3;
const int rightMotorPin = 5;
const int buttonPin = 7;

// Zaman kontrolü için değişkenler
unsigned long startTime;

void setup() {
  pinMode(distanceSensorPin, INPUT);
  pinMode(leftMotorPin, OUTPUT);
  pinMode(rightMotorPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

bool detectObject() {
  int distance = analogRead(distanceSensorPin);
  return distance < 500; // Nesne algılama eşiği
}

void approachObject() {
  analogWrite(leftMotorPin, 255);
  analogWrite(rightMotorPin, 255);
}

void pushObjectOffPlatform() {
  analogWrite(leftMotorPin, 255);
  analogWrite(rightMotorPin, 255);
  delay(500); // Nesneyi itmek için ileri hareket
}

void sumoMode() {
  startTime = millis();
  int objectsPushed = 0;

  while (millis() - startTime < 60000) { // 60 saniye
    if (detectObject()) {
      approachObject();
      pushObjectOffPlatform();
      objectsPushed++;
      if (objectsPushed >= 5) {
        break; // 5 nesne itildiğinde çık
      }
    }
  }
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    sumoMode();
  }
}
