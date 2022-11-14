#ifndef CONSTANS_H
#define CONSTANS_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include "stdbool.h"
#include <joyconlib.h>

#define MAX_PLAYER 2
#define HEAD_JUMP 20
#define JUMP 15
#define GRAV 9.8
#define R_RIGHT_BUTTON
#define R_LEFT_BUTTON
#define R_JUMP_BUTTON
#define L_RIGHT_BUTTON
#define L_LEFT_BUTTON
#define L_JUMP_BUTTON


/* メッセージ */
typedef enum {
    MSG_None     = 0,
    MSG_GameOver = 1,
    MSG_Clear    = 2,
    MSG_NUM      = 3 /* メッセージの数 */
} Msg;

/* ゲームの状態 */
typedef enum {
    GS_End     = 0, /* 終了 */
    GS_Title   = 1, /*タイトル画面*/
    GS_Playing = 2, /* 通常 */
    GS_Dead    = 3 /* プレイヤー死亡済み */
} GameStts;

/* ゲームの情報 */
typedef struct {
    GameStts stts;
    int restTime;     /* 待ち時間 */
    float timeStep;   /* 時間の増分 */
    Msg msg;          /* メッセージ */
    SDL_Rect rectMap; /* 画面表示領域 */
    SDL_Rect rectBg;  /* 画面表示領域 */
    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Texture *bg;
    SDL_Texture *map;
} GameInfo;

#endif