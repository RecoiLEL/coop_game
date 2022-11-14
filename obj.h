#ifndef OBJECTS_H
#define OBJECTS_H

#include <SDL2/SDL.h>

struct Player {
    SDL_Rect position;
    SDL_Texture *texture;
    int map_x;
    int map_y;
    int offset_x;
    int offset_y;
    int velocity_x;
    int velocity_y;
    int pixel_x;
    int pixel_y;
    int left, right, jump;
    int can_jump;
    int left_button, right_button, jump_button;
    int dead, clear;
};

struct Map {
    SDL_Rect MapRect;
    SDL_Texture *Mtexture;
    int MAPCHIP;
}

#endif