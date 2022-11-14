#ifndef OBJECTS_H
#define OBJECTS_H

#include <SDL2/SDL.h>

struct Player {
    SDL_Rect position;
    SDL_Texture *texture;
    int left, right, jump;
    int can_jump;
    int left_button, right_button, jump_button;
    int dead, clear;
};

#endif