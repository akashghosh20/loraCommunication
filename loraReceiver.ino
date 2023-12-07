#include <RH_RF95.h>

RH_RF95 rf95;

const uint8_t receiverAddress = 1; // Change this address for each receiver

void setup() {
  Serial.begin(9600);
  if (!rf95.init()) {
    Serial.println("LoRa initialization failed");
    while (1);
  }

  if (!rf95.setThisAddress(receiverAddress)) {
    Serial.println("Address setting failed");
    while (1);
  }

  rf95.setPromiscuous(false); // Disable promiscuous mode
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
