#include "net.h"
#include "constant.h"
#include <SDL2/SDL.h>

#define ALL_CLIENTS -1

int main(int argc, char *argv[]){
    int num;
    int endFlag = 1;

    if(argc != 2){
        fprintf(stderr,"Usage : number of clients\n");
        exit(-1);
    }

    if(num = atoi(argv[1]) < 0 || num > MAX_CLIENTS){
        fprintf(stderr, "Clients limit = %d\n",MAX_CLIENTS);
        exit(-1);
    }

    if(SDL_Init(SDL_INIT_TIMER) < 0){
        printf("Failed to init SDL\n");
        exit(-1);
    }

    if(server_set(num) == -1){
        fprintf(stderr, "Cannot setup server\n");
        exit(-1);
    }

    while(endFlag){
        endFlag = SendRecvManager();
    }
    
    return 0;
}

// uint8_t key_state_from_player(struct Player *player) {
//     int8_t key_state = 0;

//     if (player->left) {
//         key_state = key_state | B | Up;
//     }
//     if (player->right) {
//         key_state = key_state | X | Down;
//     }
//     if (player->jump) {
//         key_state = key_state | Y | Right;
//     }
    
//     return key_state;
// }

// void player_from_key_state(struct Player *player, int8_t key_state){
//     if(key_state & B | Up){
//         player->left = true;
//     }
//     else{
//         player->left = false;
//     }
//     if(key_state & X | Down){
//         player->right = true;
//     }
//     else{
//         player->right = false;
//     }
//     if(key_state & Y | Right){
//         player->jump = true;
//     }
//     else{
//         player->jump = false;
//     }
// }