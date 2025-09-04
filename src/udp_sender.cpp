#include <iostream>
#include <chrono>
#include <thread>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // Create socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Define target address
    sockaddr_in dest_addr;
    std::memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(8888);
    inet_pton(AF_INET, "192.168.1.3", &dest_addr.sin_addr);

    // Data to send
    const float message[4] = {1.0, 2.0, 3.0, 4.0};

    while (true) {
        // Send UDP packet
        ssize_t sent = sendto(sock, message, sizeof(float)*4, 0,
                              (struct sockaddr*)&dest_addr, sizeof(dest_addr));
        if (sent < 0) {
            perror("Send failed");
        }

        // Sleep for 1ms
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    close(sock);
    return 0;
}
