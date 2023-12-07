#include <SPI.h>
#include <LoRa.h>

#define SX1262_CS 5 // Replace with the GPIO pin number you connected to NSS (CS)
#define RECEIVER_ADDRESS 1 // Change this address to match the sender's address

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!LoRa.begin(SX1262_CS)) {
    Serial.println("LoRa initialization failed");
    while (1);
  }

  // Set the frequency to match your LoRa module (e.g., 868.0 for SX1262)
  LoRa.setFrequency(868.0);

  LoRa.setRxAddress(RECEIVER_ADDRESS); // Set the receiver address
}

void loop() {
  if (LoRa.parsePacket()) {
    int receivedValue = LoRa.parseInt();
    Serial.print("Received sensor value: ");
    Serial.println(receivedValue);
  }
}
