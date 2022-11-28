/*****************************************************************
ファイル名	: client_window.c
機能	: クライアントのユーザーインターフェース処理
*****************************************************************/
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "constant.h"
#include "client_func.h"

/* 画像ファイルパス */
static char gMapImgFile[]          = "";
static char gCharaImgFile[] = "";

static SDL_Window *gMainWindow;
static SDL_Renderer *gMainRenderer;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

/* 関数 */
static void PlaceChara(void);
static int AdjustXrange(int x);
static int MakeMap(void);
static int MakeMessage(void);


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

	/* メインのウインドウを作成する */
	if((gMainWindow = SDL_CreateWindow("My Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0)) == NULL) {
		printf("failed to initialize videomode.\n");
		return -1;
	}
	/* 背景を黒にする */
	SDL_SetRenderDrawColor(gMainRenderer, 0, 0, 0, 255);
  	SDL_RenderClear(gMainRenderer);

    load_image(renderer, &player_image, "images/chara.png");

    load_mapchip(renderer, mapchip, number_of_map_image);
    load_map("data/field.map", map_array, &COL, &ROW, &OUT_OF_MAP);

	/* マップの作成 */
    /*if (MakeMap())
        return -1;*/

    return 0;
}

/*****************************************************************
関数名	: DestroyWindow
機能: ウインドウを消す
引数	: なし
出力	: なし
*****************************************************************/
void DestroyWindow(void)
{
	SDL_Quit();
}

/*****************************************************************
関数名	: PlaceChara
機能: キャラの配置
引数	: なし
出力	: なし
*****************************************************************/
void PlaceChara(void)
{
    /* キャラのコピー */
    int i;
    for (i = 0; i < gCharaNum; i++) {
        if (gChara[i].stts != CS_Disable) {
            SDL_Rect dst = gChara[i].rect;
            /* 表示画面の左端がgGame.rectMap.xなので
               これを引くことで画面上の相対座標に変換 */
            dst.x -= gGame.rectMap.x;
            dst.x = AdjustXrange(dst.x);
            if (0 > SDL_RenderCopy(gGame.render, gChara[i].img->image, &(gChara[i].src), &dst)) {
                PrintError(SDL_GetError());
            }
        }
    }
}

/*****************************************************************
関数名	: AdjustXrange
機能: x座標のマップ範囲への補正
引数	: なし
出力	: なし
*****************************************************************/
int AdjustXrange(int x)
{
    while (x < 0) {
        x += MAP_Width * MAP_ChipSize;
    }
    return x % (MAP_Width * MAP_ChipSize);
}

/*****************************************************************
関数名	: RenderWindow
機能: ウインドウの更新
引数	: なし
出力	: なし
*****************************************************************/
int RenderWindow(void)
{
    /* メインウインドウへの転送 */
    int bgw = 0;
    int ret = SDL_QueryTexture(gGame.bg, NULL, NULL, &bgw, NULL);
    if (ret < 0) {
        PrintError(SDL_GetError());
    }

    /* マップ */
    gGame.rectMap.x = AdjustXrange(gChara[gGame.player].rect.x - (WD_Width * MAP_ChipSize - gChara[gGame.player].rect.w) / 2);
    src = dst = gGame.rectMap;
    if (src.x + src.w >= MAP_Width * MAP_ChipSize) {
        dst.x = MAP_Width * MAP_ChipSize - src.x;
        src.x = 0;
        src.w = dst.w = src.w - dst.x;

        ret = SDL_RenderCopy(gGame.render, gGame.map, &src, &dst);
        if (ret < 0) {
            PrintError(SDL_GetError());
        }
        src.x = gGame.rectMap.x;
        src.w = dst.w = dst.x;
    }
    dst.x = 0;
    ret   = SDL_RenderCopy(gGame.render, gGame.map, &src, &dst);
    if (ret < 0) {
        PrintError(SDL_GetError());
    }

    /* キャラ */
    PlaceChara();

    /* 描画更新 */
    SDL_RenderPresent(gGame.render);

    return ret;
}