#include "net.h"
#include "constant.h"

struct sockaddr_in server_sock_addr(char *ip){
    struct sockaddr_in server_addr;
    memset( &server_addr, 0, sizeof(server_addr) );
    server_addr.sin_family = AF_INET;
    if(ip==NULL){
        server_addr.sin_family = htonl(INADDR_ANY);
    }
    else{
        inet_aton(ip, &server_addr.sin_addr);
    }
    server_addr.sin_port = htonl(1234);

    return server_addr;
}

struct sockaddr_in client_sock_addr(){
    struct sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr = INADDR_ANY;
    client_addr.sin_port = 0;
    return client_addr;
}

int addr_pos_in_tab(struct sockaddr_in new_addr, struct sockaddr_in old_addr_tab[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        if(compare_addr(&new_addr, &old_addr_tab[i])) {
            return i;
        }
    }
    return size;
}

int compare_addr(struct sockaddr_in *a, struct sockaddr_in *b) {
    if (a->sin_port == b->sin_port &&
            a->sin_family == b->sin_family &&
            a->sin_addr.s_addr == b->sin_addr.s_addr) {
        return true;
    } else {
        return false;
    }
}