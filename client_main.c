/*****************************************************************
ファイル名	: client_main.c
機能	: クライアントのメインルーチン
*****************************************************************/
#include"constant.h"
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
    if(argc == 1){
    	serverName = localHostName;
    }
    else if(argc == 2){
    	serverName = argv[1];
    }
    else{
		fprintf(stderr, "Usage: %s, Cannot find a Server Name.\n", argv[0]);
		return -1;
    }

    /* サーバーとの接続 */
    if(SetUpClient(serverName,&clientID,&num,name)==-1){
		fprintf(stderr,"setup failed : SetUpClient\n");
		return -1;
	}
    /* ウインドウの初期化 */
	if(InitWindows(clientID,num,name)==-1){
		fprintf(stderr,"setup failed : InitWindows\n");
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
        fprintf(stderr,"setup failed : SDL_CreateThread\n");
        goto DESTROYALL;
    }
    SDL_DetachThread(thread);
    /* タイマー */
    SDL_TimerID timer = SDL_AddTimer(100, AniTimer, &atm);
    if (timer == 0) {
        fprintf(stderr,"setup failed : SDL_AddTimer\n");
        goto RELEASETHREAD;
    }

    /* メインイベントループ */
    while(SDL_AtomicGet(&atm) > 0){
		  WindowEvent(num);
      /* 終了時は何もしない */
        if (gGame.stts) {
            SetInput();
            /*
            for (int i = 0; i < gCharaNum; i++) {
                UpdateCharaStatus(&(gChara[i]));
                move_player(&(gChara[i]));
            }
            for (int i = 0; i < gCharaNum; i++) {
                for (int j = i + 1; j < gCharaNum; j++)
                    Collision(&(gChara[i]), &(gChara[j]));
            }*/
        }
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

/* タイマー処理2(アニメーションの更新) */
Uint32 AniTimer(Uint32 interval, void* param)
{

    /* 時間増分の更新 */
    if (SDL_AtomicGet((SDL_atomic_t*)param) > 0) {
        gGame.timeStep = 0.1 / SDL_AtomicGet((SDL_atomic_t*)param);
        printf("FPS: %d\r", SDL_AtomicGet((SDL_atomic_t*)param) * 10);
        SDL_AtomicSet((SDL_atomic_t*)param, 1);
    }

    /* 転送元範囲の更新(アニメーション) */
    for (int i = 0; i < gCharaNum; i++) {
        /* アニメーションパターンの更新 */
        gChara[i].src.x = (gChara[i].src.x + gChara[i].src.w) % gChara[i].img->imgW;
    }
    return interval;
}