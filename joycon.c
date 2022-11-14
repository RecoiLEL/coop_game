#include <joyconlib.h>   //ヘッダファイルのインクルード

joycon_open(&jc, JOYCON_R);   //Joy-Conのオープン

joycon_get_state(&jc);  //Joy-Conの操作

joycon_close(&jc);  //Joy-Conのクローズ

joycon_get_button_elapsed()


SDL_INIT_JOYSTICK