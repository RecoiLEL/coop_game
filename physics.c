#include "physics.h"
#include "constant.h"

void move_player(struct Player *player) {
    int x_move = 0;
    int y_move = 0;
    if (player->left) {     //左入力が押された場合
        x_move -= PLAYER_SPEED;     //左の速度を60にする
        player->head = -1;
    }
    if (player->right) {        //右入力が押された場合
        x_move += PLAYER_SPEED;     //右の速度を60にする
        player->head = 1;
    }
    if (player->up) {       //上入力が押された場合
        if (player->can_jump) {     //
            player->can_jump = false;
            player->y_speed = -PLAYER_JUMP_POWER;
        }
    }
    
    y_move = player->y_speed / 5;
    if (player->y_speed < MAX_VERTICAL_SPEED) {
        player->y_speed += GRAVITY;
    }

    while (x_move != 0 || y_move != 0) {
        if (x_move != 0 && move_and_check_collisions(&player->position, X_AXIS, x_move)) {
            decrement_abs(&x_move); //x_moveの絶対値を取る
        } else {
            x_move = 0;
        }

        if (y_move != 0 && move_and_check_collisions(&player->position, Y_AXIS, y_move)) {
            decrement_abs(&y_move);  //y_moveの絶対値を取る
            player->can_jump = false;
        } else {
            if(y_move > 0) {
                player->can_jump = true;
                player->y_speed = 0;
            }
            if(y_move < 0) {
                player->y_speed = 0;
            }
            y_move = 0;
        }
    }
}