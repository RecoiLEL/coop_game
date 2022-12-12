#ifndef CLIENT_UDP_H
#define CLIENT_UDP_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <assert.h>
#include <math.h>

#define PORT (u_short) 1234
#define END_COMMAND	'E'
#define MAX_NAME_SIZE 10
#define MAX_CLIENTS 2
#define MAX_DATA 200

extern int send_flag;

extern int client_setup(char* hostname,int *clientID,int *num,char clientname[][MAX_NAME_SIZE]);
extern void closesock(void);
extern int Crecv_intdata(int *intdata);
extern void Csend_data(void *data,int datasize);
extern int CSendRecvManager(void);

/*command*/
extern int ExecuteCommand(char command);
extern void SendEndCommand(void);
extern void SetCharData2DataBlock(void *data,char charData,int *dataSize);

#endif