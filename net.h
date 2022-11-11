#ifndef NETWORK_H
#define NETWORK_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <objects.h>

struct sockaddr_in server_sock_addr();
struct sockaddr_in client_sock_addr();

#endif
