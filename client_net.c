#include "constant.h"
#include "client_net.h"

void prepare_server(int *sock, struct sockaddr_in *client_addr){
    if((*sock) = socket(AF_INET,SOCK_DGRAM,0) < 0){
        perror("client socket failled");
    }
    if(bind(*sock))
}