#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 1900

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    char message[100];

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");

    // Create a socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
    }

    printf("Socket created.\n");

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.1.14");
    server.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed with error code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    puts("Bind done");

    // Listen to incoming connections
    listen(server_socket, 3);

    // Accept and incoming connection
    puts("Waiting for incoming connections...");

    int c = sizeof(struct sockaddr_in);
    client_socket = accept(server_socket, (struct sockaddr*)&client, &c);
    if (client_socket == INVALID_SOCKET) {
        printf("Accept failed with error code : %d", WSAGetLastError());
        return 1;
    }

    puts("Connection accepted");

    // Receive and send data
    while (1) {
        recv(client_socket, message, sizeof(message), 0);
        printf("Client: %s\n", message);

        printf("Server: ");
        gets(message);
        send(client_socket, message, sizeof(message), 0);
    }

    closesocket(server_socket);
    WSACleanup();

    return 0;
}
