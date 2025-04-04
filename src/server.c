#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

// This program creates a simple TCP server that binds to a specified port and listens for incoming connections.
// It demonstrates the use of socket programming in C.
// The server will run indefinitely, waiting for connections.


int main() {
    int server_fd;
    struct sockaddr_in server_addr;
    int port = 8080;

    // Step 1: Create a TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully.\n");

    // Step 2: Define the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Bind to all available interfaces
    server_addr.sin_port = htons(port);      // Convert port to network byte order

    // Step 3: Bind the socket to the specified IP and port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Socket bound to port %d successfully.\n", port);

    // Step 4: Put the socket into listening mode
    if (listen(server_fd, 5) == -1) { // 5 is the backlog size
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server is listening on port %d.\n", port);

    // Keep the server running (for testing purposes)
    while (1) {
        sleep(1);
    }

    // Close the socket (unreachable in this example)
    close(server_fd);
    return 0;
}