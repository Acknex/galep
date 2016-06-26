#ifndef PLAYER_H_
#define PLAYER_H_

#define PLAYER_SPEED_E 50
#define LEVEL_LIMIT_Z_E 500
#define LEVEL_LIMIT_Y_E 800
#define BULLET_SPEED_E 400
#define BULLET_COOLDOWN_E 100
#define BULLET_AGE_E 800

#define BOOST_COOLDOWN_E 1000

#define ENEMY_DAMAGE 10

void spawn_player();
void act_player();
void act_engine_fx();
void player_fire();
void boost_player();
void player_reinit();
void move_crosshair(VECTOR* vMoveSpeed, VECTOR* vMoveDir);

BMAP* bmapCrosshair = "textures//crosshair.bmp";
ENTITY* entCrosshair = NULL;
ENTITY* entCrosshair2 = NULL;
ENTITY* entEngineFx = NULL;

SOUND* sndAiaiaiai = "aiaiaiai.ogg";
SOUND* sndInfinity = "infinity.wav";
SOUND* sndDie = "die.wav";
SOUND* sndLaser = "hit.wav";

int shootCooldown;
var smokeCooldown;

int sLeft = 0;
int sRight = 0;
int sTop = 0;
int sBottom = 0;

var width = 0;
var height = 0;
var splineDistance = 0;

var player_speed = PLAYER_SPEED_E;
var player_boost = 10;
var boost_cooldown = 0;

var player_hit_cooldown = 0;

#endif