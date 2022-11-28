#include "server.h"
#include "net.h"
#include "constant.h"
#include "obj.h"
#include <time.h>
#include <sys/time.h>

struct sockaddr_in clients_addr[MAX_PLAYER]
struct Player players_server[MAX_PLAYER]
int num_of_connected_clients = 0;

void prepare_server(int *sock, struct sockaddr_in *server_sock){
    memset(clients_addr, 0, sizeof(struct sockaddr_in) * MAX_PLAYERS);
    if ((*sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("socket failed");
    }
    if (bind(*sock, (struct sockaddr*) server_sock, sizeof(struct sockaddr)) < 0) {
        perror("bind server error");
    }
}

void init_player_tab(){
    int i;
    for(i=0;i<MAX_PLAYER;i++){
        players_server[i].p_rect.w = PLAYER_WIDTH
        players_server[i].p_rect.h = PLAYER_HEIGHT
    }
}

struct sockaddr_in receive_data(int sock, int16_t data[]){
    struct sockaddr_in addr;
    socklen_t addr_size = sizeof(struct sockaddr);
    recvfrom(sock, data, sizeof(int16_t) * 2, 0, (struct sockaddr*)&addr, &addr_size);
    return addr;
}

void send_data(int sock, struct sockaddr_in client, int16_t data[], int size){
    socklen_t addr_size = sizeof(struct sockaddr);
    sendto(sock, data, sizeof(int16_t) * size, 0, (struct sockaddr*)&client, addr_size);
}

void* server_recv_loop(void *arg){
    int socket = *((int*) arg);
    int client_pos = 0;
    struct sockaddr_in clients_addr;
    int16_t tab[4];
    init_player_tab();
    while(1){
        client_addr = receive_data(socket, tab);
        client_pos = addr_pos_in_tab(client_addr, clients_addr, num_of_connected_clients)
    }

}

void* server_send_loop(void *arg){
    int socket = *((int*) arg);

}

int its_and_old_client(int client_pos){
    return (client_pos < num_of_connected_clients && clinet_pos >= 0)
}