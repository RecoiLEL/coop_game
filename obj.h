#ifndef OBJECTS_H
#define OBJECTS_H

#include <SDL2/SDL.h>

typedef enum {LEFT, RIGHT, JUMP} DIRECTION;

typedef struct {
    int map_x;
    int map_y;
    int pixel_x;
    int pixel_y;
    int offset_x;
    int offset_y;
    int velocity_x;
    int velocity_y;
    DIRECTION direction;
    MOVING moving;
    CHARACTER_STATUS status;
} Player;

typedef struct {
    int mapchip_id;
    char mapchip_name[256];
    int movable;
    int change_locate;
    SDL_Texture *map_image;
} MAPCHIP;

/* phisics.c */
extern int void move_player(Player *player);

/* ani.h */
extern int clac_offset(int, int, int *, int *);

#endif
