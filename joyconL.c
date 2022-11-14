#include constant.h

joyconlib_t jc;
joycon_open(&jc, JOYCON_L);   //Joy-Conのオープン

joycon_get_state(&jc);  //Joy-Conの操作
if(jc.button.btn.X){
  // Xが押されているとき
}
if(jc.button.btn.B){
  // Xが押されているとき
}
if(jc.button.btn.Y){
  // Xが押されているとき
}

joycon_close(&jc);  //Joy-Conのクローズ

joycon_elapsed et;
joycon_get_button_elapsed(&jc, &et);

