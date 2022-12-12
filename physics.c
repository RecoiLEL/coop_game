#include "physics.h"
#include "constant.h"


/*経過時間*/
double t               =  0;
/*キャラクタ,マップの状態変数*/
int    charastts       =  0;
int    mapstts         =  0;
int    movemapstts     = 30;
/*キャラクタの初期座標*/
double chpos_Initial_x =  8;
double chpos_Initial_y = 38;

/*
int sensor(int check) {
    if (check < 0) {
        return -1;
    } else if (check > 0) {
        return 1;
    } else {
        return 0;
    }
}

void decrement_abs(int *check)
{
    *check -= sensor(*check);
}

int check_collisions(SDL_Rect *rect) 

int move_and_check_collisions(SDL_Rect *position, int axis, int mov) {
    SDL_Rect posi = *position;

    if (axis == X_AXIS) {
        posi.x += sign(mov);
    }

    if (axis == Y_AXIS) {
        posi.y += sign(mov);
    }

    if (check_collisions(&posi)) {
        return 0;
    } else {
        *position = posi;
        return 1;
    }
}

void move_player(struct Player *player) {
    int x_move = 0;
    int y_move = 0;
    if (player->LEFT) {     //左入力が押された場合
        velocity_y-= PLAYER_SPEED;     //左の速度を60にする
        player->head = -1;
    }
    if (player->RIGHT) {        //右入力が押された場合
        velocity_x += PLAYER_SPEED;     //右の速度を60にする
        player->head = 1;
    }
    if (player->UP) {       //上入力が押された場合
        if (player->can_jump) {     //
            player->can_jump = false;
            player->velocity_y = -PLAYER_JUMP_POWER;
        }
    }
    
    y_move = player->y_speed / 5;
    if (player->velocity_y < MAX_VERTICAL_SPEED) {
        player->velocity_y += GRAVITY;
    }

    while (x_move != 0 || y_move != 0) {
        if (x_move != 0 && move_and_check_collisions(&player->position, X_AXIS, x_move)) {
            decrement_abs(&x_move); //x_moveの絶対値を取る
        } else {
            x_move = 0;
        }

        if (y_move != 0 && move_and_check_collisions(&player->position, Y_AXIS, y_move)) {
            decrement_abs(&y_moving);  //y_moveの絶対値を取る
            player->can_jump = false;
        } else {
            if(y_move > 0) {
                player->can_jump = true;
                player->velocity_y = 0;
            }
            if(y_move < 0) {
                player->velocity_y = 0;
            }
            y_move = 0;
        }
    }
}

*/

int player_move(SDL_Event e) {

        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP){       //上入力が押された場合(ジャンプ処理)
         player.direction = UP;
            if ((is_movable(player.map_x, player.map_y - PLAYER_JUMP_POWER) == TRUE) && player.velocity_y == 0) {
                player.velocity_x = 0;
                player.velocity_y = -PLAYER_JUMP_POWER;　 //　初速度
                player.map_y = player.map_y - PLAYER_JUMP_POWER;   //　フレーム毎に速度を加算
                player.velocity_y = player.velocity_y + GRAVITY;    //　フレーム毎に加速度を速度に加算
            if ((is_movable(player.map_x, player.map_y + GRAVITY)) != TRUE) {    //　落下地点に障害物があれば
                player.velocity_x = 0;　　　　//　障害物に衝突したものとして速度を０に
                player.velocity_y = 0;　　　　//　障害物に衝突したものとして速度を０に
        } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT){    //右入力が押された場合
            player.direction = RIGHT;
            if (is_movable(player.map_x + PLAYER_SPEED, player.map_y) == TRUE) {
                player.velocity_x = PLAYER_SPEED;
                player.velocity_y = 0;
                player.moving = TRUE;
            }
        } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT){　　　//左入力が押された場合
            player.direction = LEFT;
            if (is_movable(player.map_x - PLAYER_SPEED, player.map_y) == TRUE) {
                player.velocity_x = -PLAYER_SPEED;
                player.velocity_y = 0;
                player.moving = TRUE;
            }
        }
    return 0;
    
    
    
      /*衝突判定*/
	    switch(Collision(player.map_x, player.map_y, movemapstts)){

		    /*床*/
		    case MS_Floor:
			    if(DIRECTION == JUMP){
				    chpos_Initial_x += (player.velocity_x*t)       / MAP_ChipSize;
				    chpos_Initial_y -= (player.velocity_y*t - t*t) / MAP_ChipSize;
				    CHARACTER_STATUS = 0;
			    }
			    break;

                    /*壁(右)*/
		    case MS_WallR:
		            if(DIRECTION == JUMP && player.velocity_x >= 0){
				    chpos_Initial_x += (player.velocity_x*t)       / MAP_ChipSize;
				    chpos_Initial_y -= (player.velocity_y*t - t*t) / MAP_ChipSize;
				    player.velocity_x            = -player.velocity_x          / 2;
				    player.velocity_y            = player.velocity_y           / 5;
				    t = 0;
			    }
			    break;

	            /*壁(左)*/
		    case MS_WallL:
                            if(DIRECTION == JUMP && player.velocity_x <= 0){
                                    chpos_Initial_x += (player.velocity_x*t)       / MAP_ChipSize;
                                    chpos_Initial_y -= (player.velocity_y*t - t*t) / MAP_ChipSize;
                                    player.velocity_x            = -player.velocity_x          / 2;
                                    player.velocity_y            = player.velocity_y           / 5;
                                    t = 0;
                            }
                            break;

		    /*天井*/	    
		    case MS_Roof:
			    if(DIRECTION == JUMP && player.velocity_y >= 0){
				    chpos_Initial_x += player.velocity_x*t         / MAP_ChipSize;
                                    chpos_Initial_y -= (player.velocity_y*t - t*t) / MAP_ChipSize;
				    player.velocity_y            = -player.velocity_y/2;
				    t = 0;
				    
			    }
			    break;

	    }

/*
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

}
*/
