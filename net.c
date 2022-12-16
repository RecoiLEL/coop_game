#include "net.h"
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