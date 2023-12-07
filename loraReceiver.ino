#include <RH_RF95.h>
#include <SPI.h>

#define SX1278_CS 5 // Replace with the GPIO pin number you connected to NSS (CS)
#define RECEIVER_ADDRESS 1 // Change this address to match the sender's address

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

  rf95.setHeaderFrom(RECEIVER_ADDRESS); // Set the receiver's own address
}

void loop() {
  if (rf95.available()) {
    // Should be a message for us now
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len)) {
      buf[len] = 0; // Null-terminate the string
      Serial.print("Received: ");
      Serial.println((char*)buf);
    } else {
      Serial.println("Receive failed");
    }
  }
}
