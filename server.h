#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdint.h>

extern int server_set(int num);
extern int recvint_data(int pos, int *intdata);
extern void send_data(int pos,void *data,int datasize);
extern int sendrecvmanager(void);
