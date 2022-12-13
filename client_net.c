#include "client_net.h"

<<<<<<< HEAD
void prepare_server(int *sock, struct sockaddr_in *client_addr){
    if((*sock) = socket(AF_INET,SOCK_STREAM,0) < 0){
        perror("client socket failled");
=======
#define BUF_SIZE 100

static int sock;
static fd_set mask;
static int width;

static int crecv_data(void *data, int datasize);
static void cset_mask(void);

int client_setup(char* hostname,int *clientID,int *num,char clientname[][MAX_NAME_SIZE]){
    struct hostent *servhost;
    struct sockaddr_in server;
    int len;
    char str[BUF_SIZE];

    if((servhost = gethostbyname(hostname)) == NULL){
        fprintf(stderr, "Unknown host\n");
        return -1;
>>>>>>> 8ee87c739dc551370f5f709842ff38b0321d52c2
    }

    bzero((char*)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    bcopy(servhost->h_addr, (char*)&server.sin_addr, servhost->h_length);

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        fprintf(stderr, "socket alloc failed\n");
        return -1;
    }

    if(connect(sock, (struct sockaddr*)&server, sizeof(server)) == -1){
        fprintf(stderr, "Cannot connect\n");
        close(sock);
        return -1;
    }
    fprintf(stderr, "Connected\n");

    do{
        printf("Enter your name\n");
        fgets(str, BUF_SIZE, stdin);
        len = strlen(str) - 1;
        str[len] = '\0';
    }
    while(len > MAX_NAME_SIZE - 1 || len == 0);
    Csend_data(str, MAX_NAME_SIZE);

    printf("Please wait\n");

    cset_mask();

    return 0;
}

int CSendRecvManager(void){
    fd_set readok;
    char command;
    int i;
    int endFlag = 1;
    struct timeval timeout;

    timeout.tv_sec = 0;
    timeout.tv_usec = 20;

    readok = mask;

    select(width, &readok, NULL, NULL, &timeout);
    if(FD_ISSET(sock, &readok)){
        crecv_data(&command, sizeof(char));
        endFlag = ExecuteCommand(command);
    }
    return endFlag;
}

int Crecv_intdata(int *intdata){
    int n, tmp;
    
    assert(intdata != NULL);

    n = crecv_data(&tmp, sizeof(int));
    (*intdata) = ntohl(tmp);

    return n;
}

void Csend_data(void *data,int datasize){
    assert(data != NULL);
    assert(0 < datasize);

    write(sock, data, datasize);
}

void closesock(void){
    printf("Disconnected\n");
    close(sock);
}

/*static from here*/

static void cset_mask(void){
    int i;
    FD_ZERO(&mask);
    FD_SET(sock,&mask);

    width = sock + 1;
}

static int crecv_data(void *data, int datasize){
    assert(data != NULL);
    assert(0 < datasize);

    return read(sock, data, datasize);
}