#include "constant.h"
#include "client_net.h"

void prepare_server(int *sock, struct sockaddr_in *client_addr){
    if((*sock) = socket(AF_INET,SOCK_DGRAM,0) < 0){
        perror("client socket failled");
    }
    if(bind(*sock, (struct sockaddr*)client_addr, sizeof(struct sockaddr)) < 0){
        perror("bind client error");
    }
}

void send_to_server(int sock, struct sockaddr_in serv_addr, int16_t id, int16_t keys){
    
}