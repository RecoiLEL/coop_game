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
    client_num = num;

    assert(0 < num && num <= MAX_CLIENTS)//check argument through assert func

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

int SendRecvManager(void){
    char	command;
    fd_set	readOK;
    int		i;
    int		endFlag = 1;

    readOK = mask;
    if(select(width,&readOK,NULL,NULL,NULL) < 0){
        return endFlag;
    }

    for(i=0;i<client_num;i++){
		if(FD_ISSET(clients[i].fd,&readOK)){
			recv_data(i,&command,sizeof(char));
	    	endFlag = ExecuteCommand(command,i);
	    	if(endFlag == 0)break;
		}
    }
    return endFlag;
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

/*static from here*/

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

static void set_mask(int maxfd){
    int	i;

    width = maxfd+1;

    FD_ZERO(&mask);
    for(i=0;i<client_num;i++)FD_SET(clients[i].fd,&mask);
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
need move and send move data
*/