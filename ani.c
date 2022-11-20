/*****************************************************************
ファイル名	: ani.c
機能	　　: キャラクターの表示,アニメーション処理
*****************************************************************/

#include "ani.h"

int frame      =  0;
int animecycle = 24;

CHARACTER player = {25, 41, 0, 0, 0};

/*****************************************************************
関数名	: clac_offset
機能　　: 画面中央を算出,キャラクタの表示場所の指定
*****************************************************************/
int clac_offset(int x, int y, int *offset_x, int *offset_y) {
    *offset_x = x - (SCREEN_WIDTH / 2);
    *offset_y = y - (SCREEN_HEIGHT / 2);

    return 0;
}

/*****************************************************************
関数名	: player_animation
機能	: アニメーションスプライトの切り替え
*****************************************************************/


/*キャラクタの状態を(第三)引数にしています。
　コマンド入力時にスプライトの段番号(0~5段)を指定してください。*/

/*0:静止(右)
  1:移動(右)
  2:踏まれ(右)
  3:静止(左)
  4:移動(左)
  5:踏まれ(左)*/
  
int player_animation(SDL_Renderer *renderer, SDL_Texture *player_image, int charastts) {

    int x = ((frame / animecycle) % 6) * 25;
    int y = charastts * 41;

    SDL_Rect imageRect=(SDL_Rect){x, y, 25, 41};
    SDL_Rect drawRect=(SDL_Rect){player.pixel_x - player.offset_x, player.pixel_y - player.offset_y,
                                 IMAGE_WIDTH*MAGNIFICATION, IMAGE_HEIGHT*MAGNIFICATION};

    SDL_RenderCopy(renderer, player_image, &imageRect, &drawRect);

    if (frame <= animecycle * 6) {
        frame += 1;
    } else{
        frame = 0;
    }

    return 0;
}
