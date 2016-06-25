#include "level.h"
#include "player.h"
#include "hud.h"
#include "environment.h"
#include "camera.h"
#include "enemy.h"

void level_start()
{
	//level_load(NULL);
	//level_load("testlevel.wmb");
	//level_load("testbed.wmb");
	level_load("space.wmb");
	init_star_cube();
	init_levelSounds();
	hud_init();
	spawn_player();
	hud_show();
	populate_space(100, 200);
	camera_init();
	spawn_enemies();

	sun_light = 0;
	vec_set(d3d_pointlightfalloff, vector(0, 0, 1));

	you = ent_create("sun.mdl", vector(-10000, 0, 0), NULL);
	vec_set(you.blue, vector(70, 80, 90));
	you.lightrange = 1000000;
	vec_set(you.scale_x, vector(50, 50, 50));

	you = ent_create("planet0.mdl", vector(10000, 0, 0), NULL);
	vec_set(you.scale_x, vector(50, 50, 50));
	
	camera_init();
}

void level_restart()
{
	init_levelSounds();
	hud_reinit();
	hud_show();
}

void level_stop()
{
	uninit_levelSounds();
	uninit_star_cube();
	hud_hide();
}