#ifndef NETWORK_H
#define NETWORK_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "joyconlib.h"
#include "constant.h"

struct sockaddr_in server_sock_addr();
struct sockaddr_in client_sock_addr();
uint8_t key_state_from_player(struct Player *player);
void player_from_key_state(struct Player *player, int8_t key_state);

#endif
