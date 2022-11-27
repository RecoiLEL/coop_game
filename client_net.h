#ifndef CLIENT_UDP_H
#define CLIENT_UDP_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdint.h>

#define SERVER_PORT 1234

void prepare_client(int *, struct sockaddr_in *);
void send_to_server(int , struct sockaddr_in , int16_t , int16_t);
int client_listen(int , int16_t *);


#endif