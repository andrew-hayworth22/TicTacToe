// CS4-53203: Systems Programming
// Name: Michael Hayworth
// Date: 5/1/2022
// server.h

// Interface with all server methods and globals

#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>

//#define POP_PORT    8080
#define MAXMSG      512

static int pop_fd = -1;
static FILE* infp = NULL;

int make_server_socket(int);
int connect_to_server(char*, int);
int SCconnect(char*, int);
int SCtell_server(char*);
int SCgetstr(char*, int);

#endif