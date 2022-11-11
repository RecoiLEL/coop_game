#ifndef OBJECTS_H
#define OBJECTS_H

#include <SDL2/SDL.h>

struct Player {
    SDL_Rect position;
    SDL_Texture *texture;
    int left, right, up, down;
    int can_jump;
    int left_key, right_key, up_key, down_key, attack_key;
};

#endif