#include "constant.h"

joyconlib_t jc;
joycon_open(&jc, JOYCON_R);   //Joy-Conのオープン

joycon_get_state(&jc);  //Joy-Conの操作
if(jc.button.btn.X){
  player->right;    // Xボタンが押されているとき
}
if(jc.button.btn.B){
  player->left;    // Bボタンが押されているとき
}
if(jc.button.btn.Y){
  player->up;    // Yボタンが押されているとき
}

joycon_close(&jc);  //Joy-Conのクローズ

joycon_elapsed et;
joycon_get_button_elapsed(&jc, &et);

(while (jc_is_open(&jc))){
    // メインループ
 
    if(SDL_PollEvent(&e)){
        // イベント処理
    }
}