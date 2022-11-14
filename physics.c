#include "physics.h"
#include "constans.h"

int map[15][20] = { };

void move_player(struct Player *player) {
    int x_movement = 0;
    int y_movement = 0;
    if (player->left) {
        x_movement -= PLAYER_SPEED;
        player->face = -1;
    }
    if (player->right) {
        x_movement += PLAYER_SPEED;
        player->face = 1;
    }
    if (player->up) {
        if (player->can_jump) {
            player->can_jump = false;
            player->y_speed = -PLAYER_JUMP_POWER;
        }
    }
    
    y_movement = player->y_speed / 3;
    if (player->y_speed < MAX_VERTICAL_SPEED) {
        player->y_speed += GRAVITY;
    }

    while (x_movement != 0 || y_movement != 0) {
        if (x_movement != 0 && move_and_check_collisions(&player->position, X_AXIS, x_movement)) {
            decrement_abs(&x_movement);
        } else {
            x_movement = 0;
        }

        if (y_movement != 0 && move_and_check_collisions(&player->position, Y_AXIS, y_movement)) {
            decrement_abs(&y_movement);
            player->can_jump = false;
        } else {
            if(y_movement > 0) {
                player->can_jump = true;
                player->y_speed = 0;
            }
            if(y_movement < 0) {
                player->y_speed = 0;
            }
            y_movement = 0;
        }
    }
}