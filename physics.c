#include "physics.h"
#include "constant.h"

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

        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP){       //上入力が押された場合
         player.direction = UP;
            if (is_movable(player.map_x, player.map_y - 1) == TRUE) {
                player.velocity_x = 0;
                player.velocity_y = -PLAYER_JUMP_POWER;
                player.moving = TRUE;
            }
        } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT){
            player.direction = RIGHT;
            if (is_movable(player.map_x + 1, player.map_y) == TRUE) {
                player.velocity_x = speed;
                player.velocity_y = 0;
                player.moving = TRUE;
            }
        } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT){
            player.direction = LEFT;
            if (is_movable(player.map_x - 1, player.map_y) == TRUE) {
                player.velocity_x = -speed;
                player.velocity_y = 0;
                player.moving = TRUE;
            }

    if (player->velocity_y < MAX_VERTICAL_SPEED) {
        player->velocity_y += GRAVITY;
    }
        }
    return 0;

    //x,yの移動可能かの判定
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
