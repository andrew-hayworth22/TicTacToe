// CS4-53203: Systems Programming
// Name: Michael Hayworth
// Date: 5/1/2022
// server.h

// Implementation of server.h

#include       "server.h"
#include       <stdio.h>
#include       <sys/types.h>
#include       <sys/socket.h>
#include       <netinet/in.h>
#include       <netdb.h>
#include       <strings.h>
#include       <unistd.h>
#include       <string.h>

///////////////////////////////////////////////////////////////////////
// make_server_socket() -> creates a socket for game server
//   -> Param: portnum -> number of port to open socket on
//   -> Returns: a server socket or -1 on error
///////////////////////////////////////////////////////////////////////
int make_server_socket(int portnum) {
    struct sockaddr_in  saddr;          // Build the address here
    struct hostent*     hp;             // Part of our address
    char                hostname[256];  // Part of our address
    int                 sock_id;        // Line id, file desc

    // STEP 1
    // -> Build network address
    //////////////////////////////////////

    // Get host information
    gethostname(hostname, 256);
    hp = gethostbyname(hostname);
    if(hp == NULL) return -1;

    // Fill out socket information
    bzero((char*)&saddr, sizeof(saddr));
    bcopy((char *)hp->h_addr, (char *)&saddr.sin_addr, hp->h_length);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(portnum);

    // STEP 2
    // -> Ask kernel for socket and bind address
    //////////////////////////////////////

    // Get the socket
    sock_id = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_id == -1) return -1;

    // Give socket an address
    if(bind(sock_id, (struct sockaddr*) &saddr, sizeof(saddr)) != 0)
        return -1;

    // STEP 3
    // -> Tell kernel we want to listen for calls
    //////////////////////////////////////

    if(listen(sock_id, 1) != 0) return -1;

    return sock_id;
}

///////////////////////////////////////////////////////////////////////
// connect_to_server() -> connects client to a server
//   -> Param: hostname -> name of host to connect to
//   -> Param: portnum  -> port on host to connect to
//   -> Returns: a server socket or -1 on error
///////////////////////////////////////////////////////////////////////
int connect_to_server(char* hostname, int portnum) {
    struct sockaddr_in  servadd;    // Number to call
    struct hostent*     hp;         // Used to get number
    int                 sock_id;    // The socket

    // STEP 1
    // -> Build address that we want to call
    //////////////////////////////////////

    // Get host info
    hp = gethostbyname(hostname);
    if(hp == NULL) return -1;

    // Fill in address info
    bzero((char *) &servadd, sizeof(servadd));
    servadd.sin_family = AF_INET ;
    bcopy((char *) hp->h_addr, (char *) &servadd.sin_addr, hp->h_length);
    servadd.sin_port = htons(portnum);

    // STEP 2
    // -> Make the connection
    //////////////////////////////////////

    // Get a socket
    sock_id = socket(AF_INET, SOCK_STREAM, 0);
    if(hp == NULL) return 0;

    // Set address of socket and return
    if(connect(sock_id, (struct sockaddr*) &servadd, sizeof(servadd)) != 0)
        return -1;
    
    return sock_id;

}

///////////////////////////////////////////////////////////////////////
// SCconnect() -> connect to a server
//   -> Param: host -> host to connect to
//   -> Returns: -1 on error
///////////////////////////////////////////////////////////////////////
int SCconnect(char* host, int portnum) {
    char buf[MAXMSG];

    // Connect to the server
    if((pop_fd = connect_to_server(host, portnum)) == -1)
        return -1;
    
    // Buffer reading part
    if((infp = fdopen(pop_fd, "r")) == NULL)
        return -1;

    return 0;
}

///////////////////////////////////////////////////////////////////////
// SCtell_server() -> send a message to the server
//   -> Param: str -> message to send
//   -> Returns: -1 on error
///////////////////////////////////////////////////////////////////////
int SCtell_server(char* str) {
    char	buf[MAXMSG + 1];
	int	    len = strlen(str);
	
	if(pop_fd == -1)
		return -1;
	if(len + 3 > MAXMSG)
		return -1;

	sprintf(buf, "%s\r\n", str);
	if(write(pop_fd, buf, len + 2) != len + 2)
		return -1;

	return 0;
}

///////////////////////////////////////////////////////////////////////
// SCgetstr() -> retrieve a line from server
//   -> Param: buf -> place to store response
//   -> Param: len -> length of buffer
//   -> Returns: -1 on error
///////////////////////////////////////////////////////////////////////
int SCgetstr(char* buf, int len) {
    char* rv = NULL;

    if(pop_fd == -1)
        return -1;

    if(fgets(buf, len, infp) == NULL)
        return -1;

    #ifdef CRLF_NEEDED
    if(strcmp(buf + strlen(buf) - 2, "\r\n") != 0 )	/* ends with CRLF? */
		return -1;
    #endif

    if (*buf == '.' && strlen(buf) > 3 ) {
		char *s = buf + 1, *d = buf;
		while(*d++ = *s++);
	}

	buf[strlen(buf) - 2] = '\0';
	return 0;
}