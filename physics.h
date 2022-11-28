#ifndef physics_h
#define physics_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include "obj.h"

void move_player(struct player *player);
#define X_AXIS 1
#define Y_AXIS 0
#define GRAVITY 1