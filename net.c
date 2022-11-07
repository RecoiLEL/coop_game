#include "net.h"
#include "constant.h"

struct sockaddr_in server_sock_addr(char *ip){
    struct sockaddr_in server_addr;
    memset( &server_addr, 0, sizeof(server_addr) );
    server_addr.sin_family = AF_INET;
    if(ip==NULL){
        
    }
}