/*****************************************************************
ファイル名	: client_main.c
機能	: クライアントのメインルーチン
*****************************************************************/
#include"constant.h"
#include"client.h"
#include"obj.h"

/* 関数 */
static Uint32 AniTimer(Uint32 interval, void* param);
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
	if(InitWindows(clientID,num,name)==-1){
		PrintError("setup failed : InitWindows\n");
    goto DESTROYALL;
	}

  /* スレッドセーフな整数変数を扱う 
     * スレッドの生存確認(0以下でスレッドを終了させる)と
     * 簡易フレームカウンタとして利用 */
    SDL_atomic_t atm;
    SDL_AtomicSet(&atm, 1);
    /* スレッド */
    SDL_Thread* thread = SDL_CreateThread(InputEvent, "InputEvent", &atm);
    if (thread == NULL) {
        PrintError("setup failed : SDL_CreateThread\n");
        goto DESTROYALL;
    }
    SDL_DetachThread(thread);
    /* タイマー */
    SDL_TimerID timer = SDL_AddTimer(100, AniTimer, &atm);
    if (timer == 0) {
        PrintError("setup failed : SDL_AddTimer\n");
        goto RELEASETHREAD;
    }

    /* メインイベントループ */
    while(SDL_AtomicGet(&atm) > 0){
		WindowEvent(num);
        SetInput();
        player_update();
		RenderWindow();

        /* 少し待つ*/
        SDL_Delay(10);
        /* フレームカウント */
        SDL_AtomicIncRef(&atm);
    }

  /* 終了処理 */
  SDL_RemoveTimer(timer);
RELEASETHREAD:
    SDL_AtomicSet(&atm, -10);
DESTROYALL:
	DestroyWindow();
	CloseSoc();

    return 0;
}

/* タイマー処理(アニメーションの更新) */
Uint32 AniTimer(Uint32 interval, void* param)
{

    /* 時間増分の更新 */
    if (SDL_AtomicGet((SDL_atomic_t*)param) > 0) {
        gGame.timeStep = 0.1 / SDL_AtomicGet((SDL_atomic_t*)param);
        printf("FPS: %d\r", SDL_AtomicGet((SDL_atomic_t*)param) * 10);
        SDL_AtomicSet((SDL_atomic_t*)param, 1);
    }

    /* 転送元範囲の更新(アニメーション) */
    player_animation();
    return interval;
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