#ifndef PLAYER_H_
#define PLAYER_H_

#define PLAYER_SPEED_E 50
#define LEVEL_LIMIT_Z_E 500
#define LEVEL_LIMIT_Y_E 800
#define BULLET_SPEED_E 200
#define BULLET_COOLDOWN_E 100
#define BULLET_AGE_E 800

//#define LEVEL_LIMIT_RADIUS_E 1600

void spawn_player();
void act_player();
void player_fire();

BMAP* bmapCrosshair = "textures//crosshair.bmp";
ENTITY* entCrosshair = NULL;

int shootCooldown;


#endif