#include constant.h

joyconlib_t jc;
joycon_open(&jc, JOYCON_L);   //Joy-Conのオープン

joycon_get_state(&jc);  //Joy-Conの操作

joycon_close(&jc);  //Joy-Conのクローズ

joycon_elapsed et;
joycon_get_button_elapsed(&jc, &et);

joycon_get_state(&jc);
if(jc.button.btn.X){
  // Xが押されているとき
}
if(jc.stick.y < 0.0){
  // スティックが下に…
}
