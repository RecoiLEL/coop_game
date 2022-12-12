#ifndef NETWORK_H
#define NETWORK_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "joyconlib.h"

#define MAX_CLIENTS 2
#define MAX_NAME_SIZE 10
#define MAX_DATA 200
#define PORT (u_short)1234
#define ALL_CLIENTS -1
#define END_COMMAND	'E'

extern int client_num;

extern int server_set(int num);
extern int SendRecvManager(void);
extern int recv_intdata(int pos, int *intdata);
extern int ExecuteCommand(char command, int pos);
extern void send_data(int pos, void *data, int datasize);
extern void ending(void);

// struct sockaddr_in server_sock_addr();
// struct sockaddr_in client_sock_addr();
// uint8_t key_state_from_player(struct Player *player);
// void player_from_key_state(struct Player *player, int8_t key_state);

#endif
