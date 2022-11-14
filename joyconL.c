#include "constant.h"

joyconlib_t jc;
joycon_open(&jc, JOYCON_L);   //Joy-Conのオープン

joycon_get_state(&jc);  //Joy-Conの操作
if(jc.button.btn.X){
  player->right;     // Xが押されているとき
}
if(jc.button.btn.B){
  player->left;     // Bが押されているとき
}
if(jc.button.btn.Y){
  player->down;    // Yが押されているとき
}

joycon_close(&jc);  //Joy-Conのクローズ

joycon_elapsed et;
joycon_get_button_elapsed(&jc, &et);


(while (jc_is_open(&jc))){
    // メインループ
 
    if(SDL_PollEvent(&e)){
        // イベント処理
    }
 
    // 描画処理
}
