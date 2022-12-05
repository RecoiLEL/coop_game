/*****************************************************************
ファイル名	: client_window.c
機能	: クライアントのユーザーインターフェース処理
*****************************************************************/
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "constant.h"
#include "obj.h"
#include "client.h"
#include "load.h"
#include "ani.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Surface *surface = NULL;
static SDL_Texture *player_image = NULL;
static TTF_Font *font = NULL;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int IMAGE_WIDTH = 41;
const int IMAGE_HEIGHT = 41;
const int CHARA_WIDTH = 25;
const int CHARA_HEIGHT = 41;
const int MAGNIFICATION = 1;
const int GRID_SIZE = 41;
const char* WINDOW_TITLE = "co-jump";

/* 関数 */
static int MakeMap(void);
static int move_map(SDL_Renderer *renderer, SDL_Texture *player_image);
static int MakeMessage(void);


int ROW = 15;
int COL = 20;
int OUT_OF_MAP = 0;

MAPCHIP mapchip[256] = {0};
int map_array[65536] = {0};
int number_of_map_image = 0;


int InitWindows(int clientID)
{
    int i;
	SDL_Texture *texture;
	SDL_Surface *image;
	char *s,title[10];

	/* SDLの初期化 */
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("failed to initialize SDL.\n");
		return -1;
	}

    /* フォントの初期化 */
    if ( TTF_Init() < 0 ) {
        printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
    }
    
    font = TTF_OpenFont("font/Pixeboy.ttf", 64);
    if ( font == NULL ) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

	/* メインのウインドウを作成する */
	if((window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0)) == NULL) {
		printf("failed to initialize videomode.\n");
		return -1;
	}
	/* 背景を一旦黒にする */
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  	SDL_RenderClear(renderer);

    load_image(renderer, &player_image, "images/chara.png");

    load_mapchip(renderer, mapchip, number_of_map_image);
    load_map("data/field.map", map_array, &COL, &ROW, &OUT_OF_MAP);

	/* マップの作成 */
    /*if (MakeMap())
        return -1;*/

    return 0;
}

void DestroyWindow(void)
{
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    for (int i = 0;i < number_of_map_image;i++) {
        SDL_DestroyTexture(mapchip[i].map_image);
    }

    SDL_DestroyTexture(player_image);
}

int player_update(SDL_Renderer *renderer, SDL_Event e, SDL_Texture *player_image) {

    if (player.moving == TRUE) {
        player.pixel_x = player.pixel_x + player.velocity_x;
        player.pixel_y = player.pixel_y + player.velocity_y;

        if (player.pixel_x % GRID_SIZE == 0 && player.pixel_y % GRID_SIZE == 0){
            player.moving = FALSE;
            player.map_x = player.pixel_x / GRID_SIZE;
            player.map_y = player.pixel_y / GRID_SIZE;
            move_map(renderer,player_image);
            player_move(e);
        }

    } else {
        player_move(e);
    }

}

int move_map(SDL_Renderer *renderer, SDL_Texture *player_image) {
    char event_path[256] = {0};

    sprintf(event_path, "data/%s.evt", MAP_EVENT_NAME);

    FILE *fp;
    char event[256] = {0};
    int event_point_x;
    int event_point_y;
    DIRECTION direction_of_penetration;
    char buf[256] = {0};
    char new_map_name[256] = {0};
    char map_path[256] = {0};
    int new_x;
    int new_y;
    int i = 0;
    int current_loc = 0;

    fp = fopen(event_path, "r");
    if (fp == NULL) {
        printf("file open error. %d\n", __LINE__);
        return 1;
    }

    for(i = 0;fgets(buf, sizeof(buf), fp) != NULL;i++) {

        if (strncmp(buf, "#", 1) != 0){
            if (strncmp(buf, "MOVE", 4) == 0) {
                sscanf(buf,
                   "%[^,],%d,%d,%u,%[^,],%d,%d",
                       event, &event_point_x, &event_point_y, &direction_of_penetration, new_map_name, &new_x, &new_y);

                if (player.map_x == event_point_x && player.map_y == event_point_y) {
                    if (player.direction == direction_of_penetration) {

                        sprintf(MAP_EVENT_NAME, "%s", new_map_name);

                        sprintf(map_path, "%s.map", new_map_name);
                        load_map(map_path, map_array, &COL, &ROW, &OUT_OF_MAP);

                        player.map_x = new_x;
                        player.map_y = new_y;
                        player.pixel_x = player.map_x * GRID_SIZE;
                        player.pixel_y = player.map_y * GRID_SIZE;

                        fade_out(renderer, player_image);
                        limit_move++;

                        break;
                    }
                }
            }
        }
    }

    fclose(fp);

    return 0;
}

/*****************************************************************
関数名	: RenderWindow
機能: ウインドウの更新
引数	: なし
出力	: なし
*****************************************************************/
int RenderWindow(void)
{
    SDL_RenderClear(renderer);

    /* マップ描画 */
    int x, y;
    int start_x = player.offset_x / GRID_SIZE - 1;
    int end_x = start_x + SCREEN_WIDTH / GRID_SIZE + 2;
    int start_y = player.offset_y / GRID_SIZE - 1;
    int end_y = start_y + SCREEN_HEIGHT/ GRID_SIZE + 2;

    for(y = start_y;y < end_y;y++){
        for(x = start_x; x < end_x;x++){
            SDL_Rect imageRect=(SDL_Rect){0, 0, IMAGE_WIDTH, IMAGE_HEIGHT};
            SDL_Rect drawRect=(SDL_Rect){(x * GRID_SIZE) - player.offset_x,
                                         (y * GRID_SIZE) - player.offset_y,
                                         IMAGE_WIDTH*MAGNIFICATION, IMAGE_HEIGHT*MAGNIFICATION};

            if ((x < 0) || (x > COL - 1) || (y < 0) || (y > ROW - 1)){
                SDL_RenderCopy(renderer, mapchip[OUT_OF_MAP].map_image, &imageRect, &drawRect);
            } else {
                SDL_RenderCopy(renderer, mapchip[map_array[y*COL+x]].map_image, &imageRect, &drawRect);
            }

        }
    }

    /* キャラ */
    player_animation(renderer, player_image);

    /* 描画更新 */
    SDL_RenderPresent(renderer);

    return ret;
}
