/*****************************************************************
ファイル名	: ani.h
機能	　　: アニメーションに必要なステータスの宣言
*****************************************************************/
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
    int pixel_x;
    int pixel_y;
    int offset_x;
    int offset_y;
    int status;
} CHARACTER;


int clac_offset(int, int, int *, int *);
int player_animation(SDL_Renderer *, SDL_Texture *, int);