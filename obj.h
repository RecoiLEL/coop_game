#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdio.h>
#include <SDL2/SDL.h>

typedef enum {LEFT, RIGHT, JUMP} DIRECTION;
typedef enum {OFF, ON} STATE;

/*0:静止(右)
  1:移動(右)
  2:踏まれ(右)
  3:静止(左)
  4:移動(左)
  5:踏まれ(左)*/
typedef struct {0, 1, 2, 3, 4, 5} CHARACTER_STATUS;

typedef struct {
    int map_x;
    int map_y;
    int pixel_x;
    int pixel_y;
    int offset_x;
    int offset_y;
    int velocity_x;
    int velocity_y;
    int face;
    DIRECTION direction;
    CHARACTER_STATUS status;
    SDL_Rect p_rect;
    SDL_Rect position;
} Player;

typedef struct {
    int mapchip_id;
    char mapchip_name[256];
    int movable;
    int change_locate;
    int player_move(SDL_Event);
    SDL_Texture *map_image;
} MAPCHIP;

/* ani.c */
extern int clac_offset(int, int, int *, int *);
extern int player_animation(SDL_Renderer *, SDL_Texture *, int);

#endif
