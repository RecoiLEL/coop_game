/*****************************************************************
ファイル名	: server_main.c
機能	: サーバーのメインルーチン
*****************************************************************/

#include<SDL2/SDL.h>
#include <stdio.h>

static Uint32 SignalHandler(Uint32 interval, void *param);

int main(int argc,char *argv[])
{
    return 0;
}

/*****************************************************************
関数名  : SignalHandler
機能   : 割り込み用関数 
引数    : Uint32	interval	: タイマー
		  void		*param		: 割り込み処理の引数
出力    : タイマーの次の間隔
*****************************************************************/
static Uint32 SignalHandler(Uint32 interval, void *param)
{
	SendDiamondCommand();

	return interval;
}