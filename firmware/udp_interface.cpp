#include "udp_interface.hpp"

// Define all global variables (declared as extern in header)
byte mac[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress localIP(192, 168, 1, 3);
unsigned int localRxPort = 8888;
unsigned int localTxPort = 8889;
IPAddress destIP(192, 168, 1, 25);
unsigned int destRxPort = 8888;
unsigned int destTxPort = 8889;

EthernetUDP txUdp;
EthernetUDP rxUdp;
unsigned long lastSend = 0;
const unsigned long sendInterval = 1;

// ------------------- FUNCTIONS -------------------
void udp_init() {
  // Initialize Ethernet for esp32
  Ethernet.init(5);
  Ethernet.begin(mac, localIP);
  txUdp.begin(localTxPort);
  rxUdp.begin(localRxPort);

  Serial.print("Arduino IP: ");
  Serial.println(Ethernet.localIP());
  Serial.print("Listening on port: ");
  Serial.println(localRxPort);
  Serial.print("sending on port: ");
  Serial.println(localTxPort);
}

// Send 4 floats as 16 raw bytes
void udp_send(const float values[4]) {
  if (millis() - lastSend >= sendInterval) {
    lastSend = millis();

    // pack floats into byte array
    byte buffer[sizeof(float) * 4];
    memcpy(buffer, values, sizeof(buffer));

    txUdp.beginPacket(destIP, destRxPort);
    txUdp.write(buffer, sizeof(buffer));
    txUdp.endPacket();

    // Serial.print("Sent: ");
    // for (int i = 0; i < 4; i++) {
    //   Serial.print(values[i], 6);
    //   Serial.print(" ");
    // }
    // Serial.println();
  }
}


// Receive 4 floats if available
bool udp_receive(float rxValues[4]) {
  int packetSize = rxUdp.parsePacket();

  if (packetSize == sizeof(float) * 4) {
    byte buffer[sizeof(float) * 4];
    rxUdp.read(buffer, sizeof(buffer));

    memcpy(rxValues, buffer, sizeof(buffer));
    return true;
  }

  return false;
}
// -------------------------------------------------
