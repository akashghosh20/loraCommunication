#include <RH_RF95.h>
#include <SPI.h>

#define SX1278_CS 5 // Replace with the GPIO pin number you connected to NSS (CS)
#define RECEIVER_ADDRESS 1 // Change this address for the specific receiver

RH_RF95 rf95(SX1278_CS);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!rf95.init()) {
    Serial.println("LoRa initialization failed");
    while (1);
  }

  // Set the frequency to match your LoRa module (e.g., 433.0 for SX1278)
  rf95.setFrequency(433.0);
}

void loop() {
  const char* message = "Hello from the sender";

  rf95.setHeaderTo(RECEIVER_ADDRESS); // Set the receiver address
  rf95.send((uint8_t*)message, strlen(message));
  rf95.waitPacketSent();

  Serial.println("Sent: " + String(message));

  delay(5000); // Send every 5 seconds
}
