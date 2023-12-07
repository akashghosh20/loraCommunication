#include <RH_RF95.h>

RH_RF95 rf95;

const int sensorPin = A0; // Assuming analog sensor connected to A0
const uint8_t receiverAddress = 1; // Change this address for each receiver

void setup() {
  Serial.begin(9600);
  if (!rf95.init()) {
    Serial.println("LoRa initialization failed");
    while (1);
  }
}

void loop() {
  // Read sensor value
  int sensorValue = analogRead(sensorPin);

  // Convert sensor value to a string
  String message = "Sensor Value: " + String(sensorValue);

  // Send message via LoRa with receiver address
  rf95.setHeaderFrom(receiverAddress);
  rf95.setHeaderTo(receiverAddress);
  rf95.send((uint8_t*)message.c_str(), message.length());
  rf95.waitPacketSent();

  Serial.println("Sent: " + message);

  delay(5000); // Send every 5 seconds
}
