/*****************************************************************
ファイル名	: client_window.c
機能	: クライアントのユーザーインターフェース処理
*****************************************************************/
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include"constant.h"

static SDL_Window *gMainWindow;
static SDL_Renderer *gMainRenderer;

/*****************************************************************
関数名	: InitWindows
機能: メインウインドウの表示、設定を行う
引数	: int	clientID		: クライアント番号
出力	: 正常に設定できたとき0、失敗したとき-1
*****************************************************************/
int InitWindows(int clientID,int num,char name[])
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

	/* メインのウインドウを作成する */
	if((gMainWindow = SDL_CreateWindow("My Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 512, 0)) == NULL) {
		printf("failed to initialize videomode.\n");
		return -1;
	}

	/* ウインドウのタイトルをセット */
	sprintf(title,"co-jump! %d",clientID);
	SDL_SetWindowTitle(gMainWindow, title);

	/* 背景を白にする */
	SDL_SetRenderDrawColor(gMainRenderer, 0, 0, 0, 255);
  	SDL_RenderClear(gMainRenderer);

    return 0;
}