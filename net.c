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

uint8_t key_state_from_player(struct Player *player) {
    int8_t key_state = 0;

    if (player->left) {
        key_state = key_state | B | Up;
    }
    if (player->right) {
        key_state = key_state | X | Down;
    }
    if (player->jump) {
        key_state = key_state | Y | Right;
    }
    
    return key_state;
}

void player_from_key_state(struct Player *player, int8_t key_state){
    if(key_state & B | Up){
        player->left = true;
    }
    else{
        player->left = false;
    }
    if(key_state & X | Down){
        player->right = true;
    }
    else{
        player->right = false;
    }
    if(key_state & Y | Right){
        player->jump = true;
    }
    else{
        player->jump = false;
    }
}