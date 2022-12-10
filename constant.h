#ifndef CONSTANS_H
#define CONSTANS_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include "stdbool.h"
#include "joyconlib.h"
#include "obj.h"

//network
#define MAX_CLIENTS 2
#define MAX_NAME_SIZE 10
#define MAX_DATA 200
#define PORT (u_short)1234
//phys
#define HEAD_JUMP 20
#define JUMP 15
#define PLAYER_HEIGHT 41
#define PLAYER_WIDTH 25
#define PLAYER_JUMP_POWER  15
#define GRAVITY 10
#define X// joy_r right
#define B//joy_r left
#define Y//joy_r jump
#define Down//joy_l right
#define Up//joy_l left
#define Right//joy_l jump
#define X_AXIS 1
#define Y_AXIS 0
#define PLAYER_SPEED 60
#define MAX_VERTICAL_SPEED 15
 

#endif
