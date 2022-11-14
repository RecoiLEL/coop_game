#ifndef physics_h
#define physics_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include "objects.h"

void move_player(struct player *player);
SDL_Texture* get_map_texture(SDL_Renderer *renderer);
