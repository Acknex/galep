#include "level.h"
#include "player.h"
#include "hud.h"
#include "environment.h"
#include "camera.h"
#include "enemy.h"
#include "itemdropper.h"

var hndMusicInGame = NULL;

void level_start()
{
	//level_load("testlevel.wmb");
	level_load("space.wmb");
	hndMusicInGame = media_loop("media\\DeathStone.ogg", NULL, 80);
	init_star_cube();
	init_levelSounds();
	hud_init();
	spawn_player();
	hud_show();
	populate_space(100, 200);
	camera_init();
	spawn_enemies();
	drop_items();

	sun_light = 0;
	vec_set(d3d_pointlightfalloff, vector(0, 0, 1));
}

void level_restart()
{
	if(hndMusicInGame != NULL)
		media_stop(hndMusicInGame);
	hndMusicInGame = media_loop("media\\DeathStone.ogg", NULL, 80);
	init_levelSounds();
	hud_reinit();
	hud_show();
}

void level_stop()
{
	if(hndMusicInGame != NULL)
		media_stop(hndMusicInGame);
	hndMusicInGame = NULL;
	uninit_levelSounds();
	uninit_star_cube();
	hud_hide();
}