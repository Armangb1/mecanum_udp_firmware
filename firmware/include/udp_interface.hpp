
#ifndef UDP_INTERFACE_H
#define UDP_INTERFACE_H

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

// ------------------- CONFIG -------------------
extern byte mac[6];                          // Declaration only
extern IPAddress localIP;                    // Declaration only  
extern unsigned int localRxPort;       // Declaration only
extern unsigned int localTxPort;

extern IPAddress destIP;                         // Declaration only
extern unsigned int txPort;                // Declaration only
extern unsigned int rxPort;

// ---------------------------------------------

extern EthernetUDP txUdp;                     // Declaration only
extern EthernetUDP rxUdp;                     // Declaration only


// send timing
extern unsigned long lastSend;              // Declaration only
extern const unsigned long sendInterval;    // Declaration only

// ------------------- FUNCTIONS -------------------
void udp_init();
bool udp_receive(float rxValues[4]);
void udp_send(const float values[4]);
#endif