#include <SoftwareSerial.h>

SoftwareSerial esp8266(18, 19); // RX, TX
const int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
  esp8266.begin(9600);
}

void loop() {
  if (esp8266.available()) {
    String command = esp8266.readStringUntil('\n');
    command.trim();
    if (command == "ON") {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED ON");
    } else if (command == "OFF") {
      digitalWrite(ledPin, LOW);
      Serial.println("LED OFF");
    }
  }
}
