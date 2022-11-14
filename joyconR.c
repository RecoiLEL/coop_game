#include constant.h

joyconlib_t jc;
joycon_open(&jc, JOYCON_R);   //Joy-Conのオープン

joycon_get_state(&jc);  //Joy-Conの操作

joycon_close(&jc);  //Joy-Conのクローズ

joycon_elapsed et;
joycon_get_button_elapsed(&jc, &et);

