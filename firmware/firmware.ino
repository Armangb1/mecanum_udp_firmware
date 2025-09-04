#include "udp_interface.hpp"

void setup() {
  Serial.begin(9600);
  udp_init();
}

auto new_packet_time = millis();
auto prev_packet_time = millis();
auto dt = new_packet_time;
void loop() {
  // Example: send 4 floats every 1ms
  static float txVals[4] = {0, 1, 2, 3};
  udp_send(txVals);
  for (int i = 0; i < 4; i++) {
    txVals[i] += 0.001; // increment slowly
  }

  // Example: receive 4 floats if available
  float rxVals[4];
  
  if (udp_receive(rxVals)) {
    new_packet_time = millis();
    dt = new_packet_time - prev_packet_time; 
    prev_packet_time = new_packet_time;
    Serial.print("delta t: ");
    Serial.println(dt);
    // Serial.print("Received: ");
    // for (int i = 0; i < 4; i++) {
    //   Serial.print(rxVals[i], 6);
    //   Serial.print(" ");
    // }
    // Serial.println();
  }
}
