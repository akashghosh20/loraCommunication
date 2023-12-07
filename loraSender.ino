#include <SPI.h>
#include <LoRa.h>

#define SX1262_CS 5 // Replace with the GPIO pin number you connected to NSS (CS)
#define RECEIVER_ADDRESS 1 // Change this address for the specific receiver

int sensorValuePin = 15;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!LoRa.begin(SX1262_CS)) {
    Serial.println("LoRa initialization failed");
    while (1);
  }

  // Set the frequency to match your LoRa module (e.g., 868.0 for SX1262)
  LoRa.setFrequency(868.0);
}

void loop() {
  int sensorValue = analogRead(sensorValuePin);

  LoRa.beginPacket();
  LoRa.setTxAddress(RECEIVER_ADDRESS); // Set the receiver address
  LoRa.print(sensorValue);
  LoRa.endPacket();

  Serial.println("Sent: " + String(sensorValue));

  delay(5000); // Send every 5 seconds
}
