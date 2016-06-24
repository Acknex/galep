#ifndef PLAYER_H_
#define PLAYER_H_

#define PLAYER_SPEED_E 50
#define LEVEL_LIMIT_Z_E 500
#define LEVEL_LIMIT_Y_E 800

#define LEVEL_LIMIT_RADIUS_E 1600

void spawn_player();
void act_player();

BMAP* bmapCrosshair = "textures//crosshair.bmp";
ENTITY* entCrosshair = NULL;


#endif