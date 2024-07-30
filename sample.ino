#include <ESP8266WiFi.h>

// Replace these with your network credentials
const char* ssid = "Sjie";
const char* password = "sjie2002";

// Create an instance of the WiFiServer class
WiFiServer server(80);

// Define LED pin
const int ledPin = D1;  // Change to the pin you are using for the LED

void setup() {
  // Start serial communication
  Serial.begin(115200);
  // Initialize LED pin as output
  pinMode(ledPin, OUTPUT);
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  // Start the server
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();
    if (request.indexOf("/LED=ON") != -1) {
      digitalWrite(ledPin, HIGH);
    }
    if (request.indexOf("/LED=OFF") != -1) {
      digitalWrite(ledPin, LOW);
    }
    // Send a response to the client
    client.print("HTTP/1.1 200 OK\nContent-Type: text/html\nConnection: close\n\n");
    client.print("<!DOCTYPE HTML>\n<html>\n");
    client.print("<h1>ESP8266 Web Server</h1>\n");
    client.print("<p>LED Control: <a href=\"/LED=ON\">ON</a> <a href=\"/LED=OFF\">OFF</a></p>\n");
    client.print("</html>\n");
    delay(1);
  }
}
