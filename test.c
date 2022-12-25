#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "server.h"

void oops(const char*);

int isServer = 0;
int server_sock;

///////////////////////////////////////////////////////////////////////
// main() -> main logic flow of the game
///////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
    // Determine if it is in server mode
    if(argc == 2)
        isServer = 1;
    else if(argc != 3)
        oops("Invalid input");

    // If it's a server, set up the server
    if(isServer == 1) {
        int sock_fd;

        // Create the socket
        if((server_sock = make_server_socket(atoi(argv[1]))) == -1)
            oops("Error starting server");

        // Wait for a call
        printf("Awaiting connection...\n");
        sock_fd = accept(server_sock, NULL, NULL);
        //Verify connection
        if(sock_fd == -1)
            oops("Error connecting");
        printf("Player successfully connected\n");
    }

    // If it's a client, connect to the server
    else {
        if(SCconnect(argv[1], atoi(argv[2])) == -1)
            oops("Failed to connect to server");
    }

    char buf[BUFSIZ];
    if(isServer) {
        sleep(3);
        if(write(server_sock, "HEY", 3) != 3) oops("Error writing to stream");
    }
    else {
        if(SCgetstr(buf, BUFSIZ) == -1) oops("Error getting message");
        printf("Message recieved: %s\n", buf);
    }

    close(server_sock);
}

void oops(const char* str) {
    perror(str);
    exit(1);
}