#ifndef PLAYER_H_
#define PLAYER_H_

#define PLAYER_SPEED_E 50
#define LEVEL_LIMIT_Z_E 500
#define LEVEL_LIMIT_Y_E 800
#define BULLET_SPEED_E 200
#define BULLET_COOLDOWN_E 100
#define BULLET_AGE_E 800

#define MAX_CROSSHAIR_X_E 800
#define MAX_CROSSHAIR_Y_E 600

#define BOOST_COOLDOWN_E 1000

void spawn_player();
void act_player();
void player_fire();
void boost_player();
void move_crosshair(VECTOR* vMoveSpeed, VECTOR* vMoveDir);

BMAP* bmapCrosshair = "textures//crosshair.bmp";
ENTITY* entCrosshair = NULL;

int shootCooldown;

int sLeft = 0;
int sRight = 0;
int sTop = 0;
int sBottom = 0;

var width = 0;
var height = 0;

var player_speed = PLAYER_SPEED_E;
var player_boost = 10;
var boost_cooldown = 0;


#endif