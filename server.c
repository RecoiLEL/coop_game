#include "server.h"
#include "net.h"
#include "constant.h"
#include "obj.h"
#include <time.h>
#include <sys/time.h>

typedef struct{
	int		fd;
	char	name[MAX_NAME_SIZE];
}CLIENT;

static CLIENT clients[MAX_CLIENTS];
int client_num;

static fd_set mask;
static int width;

static int recv_data(int pos, void *data, int datasize);
static int multiaccept(int request_sock, int num);

int server_set(int num){
    struct sockaddr_in server;
    int request_sock;
    int maxfd;
    int val = 1;

    assert(0 < num && num <= MAX_CLIENTS)//check argument through assert func

    client_num = num;
    bzero((char*)&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT)

    if((request_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        fprintf(stderr,"Socket allocation failed\n");
        return -1;
    }
    setsockopt(request_sock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    if(bind(request_sock, (struct sockaddr*)&server, sizeof(server)) == -1){
		fprintf(stderr,"Cannot bind\n");
		close(request_sock);
		return -1;
    }
    fprintf(stderr,"Successfully bind!\n");

    if(listen(request_sock, client_num) == -1){
		fprintf(stderr,"Cannot listen\n");
		close(request_sock);
		return -1;
    }
    fprintf(stderr,"Listen OK\n");

    maxfd = multiaccept(request_sock,client_num);
    close(request_sock);

    return 0;
}

int recv_intdata(int pos, int *intdata){
  int n,tmp;

  assert(0 < pos && pos < client_num);
  assert(intdata != NULL);

  n = recv_data(pos, &tmp, sizeof(int));
  (*intdata) = ntohl(tmp);

  return n;
}

void send_data(int pos, void *data, int datasize){
  int i;

  assert(0 < pos && pos < client_num || pos == ALL_CLIENTS);
  assert(data != NULL);
  assert(0 < datasize);
  
}

static int multiaccept(int request_sock, int num){
  int i,j;
  int fd;

  for(i = 0; i < num; i++){
    if((fd = accept(request_sock, NULL, NULL)) == -1){
      fprintf(stderr,"Accept error\n");
      for(j = i - 1; j >= 0; j--)
      close(clients[j].fd);
      return -1;
    }
    Enter(i,fd);
  }
  return fd;
}

static int recv_data(int pos, void *data, int datasize){
  int n;

  assert(0 < pos && pos < client_num);
  assert(data != NULL);
  assert(0 < datasize);

  n = read()

  return n;
}
/*
todo
server connection
server data recv send
need move and send move data
*/