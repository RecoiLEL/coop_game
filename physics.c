#include "physics.h"
#include "constant.h"
#include <stdlib.h>

int map_array[65536] = {0};
MAPCHIP mapchip[256] = {0};




int player_move(SDL_Event e) {
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP) {	//上入力が押された場合(ジャンプ処理)
            player.direction = JUMP;
            if ((is_movable(player.map_x, player.map_y - PLAYER_JUMP_POWER) == TRUE) && player.velocity_y == 0) {
                player.velocity_x = 0;
                player.velocity_y = -PLAYER_JUMP_POWER;	//初速度
                player.map_y = player.map_y - PLAYER_JUMP_POWER;	//フレーム毎に速度を加算
                player.velocity_y = player.velocity_y + GRAVITY;	//フレーム毎に加速度を速度に加算
            }
                if ((is_movable(player.map_x, player.map_y + GRAVITY)) != TRUE) {	//落下地点に障害物があれば
                player.velocity_x = 0;	//障害物に衝突したものとして速度を０に
                player.velocity_y = 0;	//障害物に衝突したものとして速度を０に
                } 
        }
        else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT){		//右入力が押された場合
            player.direction = RIGHT;
            if (is_movable(player.map_x + PLAYER_SPEED, player.map_y) == TRUE) {
                player.velocity_x = PLAYER_SPEED;
                player.velocity_y = 0;
                player.moving = TRUE;
            }
        } 
        else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT){		//左入力が押された場合
            player.direction = LEFT;
            if (is_movable(player.map_x - PLAYER_SPEED, player.map_y) == TRUE) {
                player.velocity_x = -PLAYER_SPEED;
                player.velocity_y = 0;
                player.moving = TRUE;
            }
        }
        return 0;
}
    
   
    
    
  /*
      //衝突判定
	    switch(Collision(player.map_x, player.map_y, movemapstts)){
             
		    //床
		    
		    case MS_Floor:
			    if(DIRECTION == JUMP){
				    chpos_Initial_x += (player.velocity_x*t)       / MAP_ChipSize;
				    chpos_Initial_y -= (player.velocity_y*t - t*t) / MAP_ChipSize;
				    CHARACTER_STATUS = 0;
			    }
			    break;
			    

                    //壁(右)
		    case MS_WallR:
		            if(DIRECTION == JUMP && player.velocity_x >= 0){
				    chpos_Initial_x += (player.velocity_x*t)       / MAP_ChipSize;
				    chpos_Initial_y -= (player.velocity_y*t - t*t) / MAP_ChipSize;
				    player.velocity_x            = -player.velocity_x          / 2;
				    player.velocity_y            = player.velocity_y           / 5;
				    t = 0;
			    }
			    break;

	            //壁(左)
		    case MS_WallL:
                            if(DIRECTION == JUMP && player.velocity_x <= 0){
                                    chpos_Initial_x += (player.velocity_x*t)       / MAP_ChipSize;
                                    chpos_Initial_y -= (player.velocity_y*t - t*t) / MAP_ChipSize;
                                    player.velocity_x            = -player.velocity_x          / 2;
                                    player.velocity_y            = player.velocity_y           / 5;
                                    t = 0;
                            }
                            break;

		    //天井	    
		    case MS_Roof:
			    if(DIRECTION == JUMP && player.velocity_y >= 0){
				    chpos_Initial_x += player.velocity_x*t         / MAP_ChipSize;
                                    chpos_Initial_y -= (player.velocity_y*t - t*t) / MAP_ChipSize;
				    player.velocity_y            = -player.velocity_y/2;
				    t = 0;
				    
			    }
			    break;

	    }
	    
	    */


//x,yの移動可能かどうかの判定
int is_movable(int x, int y) {

    if ( x < 0 || x > COL - 1 || y  < 0 || y > ROW - 1) {
        return 2;
    }

    if (mapchip[map_array[y*COL+x]].movable == 1) {
        return 2;
    }

    if (player.map_x == x && player.map_y == y) {
        return 1;
    }

    return TRUE;
}










/*

//杉本君のものを参考に作成

 イベントループ 
    while(event_flg) {

	    //ジャンプ中以外
	    if (charastts == CS_Normal_R || charastts == CS_Normal_L){
		    tx = 0;
		    if(ty > 0){
                            ty += 0.1;
                    }
	    }

	    else if(charastts == CS_Walk_L || charastts == CS_Walk_R){
		    tx = 0.1;
		    chpos_Initial_x += vel_x*tx / MAP_ChipSize;
		    if(ty > 0){
			    ty += 0.3;
		    }
	    }

	    //ジャンプ中
	    else if(charastts == CS_Jump){
		    ty += 0.3;
		    chpos_Initial_x += vel_x*t / MAP_ChipSize;
		    chpos_Initial_y -= (vel_y*t - t*t) / MAP_ChipSize;
	    }

	    //移動後のキャラクタ座標を格納
	    ch_x = chpos_Initial_x * MAP_ChipSize + vel_x*tx;
	    ch_y = chpos_Initial_y * MAP_ChipSize- movemapstts*MAP_ChipSize - vel_y*ty + ty*ty;
	    
*/
	    
