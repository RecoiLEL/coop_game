/*****************************************************************
ファイル名	: client_main.c
機能	: クライアントのメインルーチン
*****************************************************************/
#include "constant.h"
#include "client.h"
#include "obj.h"

Player player = {10, 10, 25, 41, 0, 0, 0, 0, RIGHT, FALSE, 0};

/* 関数 */
static int InputEvent(void* data);

int main(int argc,char *argv[])
{
    int		num;
    char	name[MAX_PLAYER];
    int		endFlag=1;
    char	localHostName[]="localhost";
    char	*serverName;
    int		clientID;
    
    /* 引数チェック */
    /* ここのコメントアウトはサーバー実装時に外す
    if(argc == 1){
    	serverName = localHostName;
    }
    else if(argc == 2){
    	serverName = argv[1];
    }
    else{
		Printe("Usage: %s, Cannot find a Server Name.\n", argv[0]);
		return -1;
    }*/

    /* サーバーとの接続 */
    /* ここのコメントアウトはサーバー実装時に外す
    if(SetUpClient(serverName,&clientID,&num,name)==-1){
		PrintError("setup failed : SetUpClient\n");
		return -1;
	}*/

    /* ウインドウの初期化 */
	if(InitWindows(clientID)==-1){
		PrintError("setup failed : InitWindows\n");
    goto DESTROYALL;
	}

    /* メインイベントループ */
    while(1){
		WindowEvent(num);
        SetInput();
        player_update();
		RenderWindow();

        /* 少し待つ*/
        SDL_Delay(10);
    }

  /* 終了処理 */
DESTROYALL:
	DestroyWindow();
	CloseSoc();

    return 0;
}

/* 入力状態から方向の設定 */
void SetInput(void)
{
    player.velocity.x = 0.0;
    if (gGame.input.left && !gGame.input.right) {
        player.dir        = CD_Left;
        player.velocity.x = 20.0;
    }
    if (gGame.input.right && !gGame.input.left) {
        player.dir        = CD_Right;
        player.velocity.x = 20.0;
    }
}

/* エラーメッセージ表示
 * 引数
 *   str: エラーメッセージ
 * 返値: -1*/
int PrintError(const char* str)
{
    fprintf(stderr, "%s\n", str);
    return -1;
}