#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 1900

int main() {
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server;
    char message[100];

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");

    // Create a socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
    }

    printf("Socket created.\n");

    // Prepare the sockaddr_in structure
    server.sin_addr.s_addr = inet_addr("192.168.1.14");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    // Connect to server
    if (connect(client_socket, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");

    // Send and receive data
    while (1) {
        printf("Client: ");
        gets(message);
        send(client_socket, message, sizeof(message), 0);

        recv(client_socket, message, sizeof(message), 0);
        printf("Server: %s\n", message);
    }

    closesocket(client_socket);
    WSACleanup();

    return 0;
}
