#include "constant.h"

joyconlib_t jc;
joycon_open(&jc, JOYCON_R);   //Joy-Conのオープン

joycon_get_state(&jc);  //Joy-Conの操作
if(jc.button.btn.DOWN){
  player->right;    // 十字キー下が押されているとき
}
if(jc.button.btn.UP){
  player->left;    // 十字キー上が押されているとき
}
if(jc.button.btn.RIGHT){
  player->up;    // 十字キー右が押されているとき
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