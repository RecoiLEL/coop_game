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

void prepare_server(int *, struct sockaddr_in *);
struct sockaddr_in receive_data(int sock, int16_t data[]);
void send_data(int sock, struct sockaddr_in client, int16_t data[], int size);