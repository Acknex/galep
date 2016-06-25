#include "level.h"
#include "player.h"
#include "hud.h"
#include "environment.h"

void level_start()
{
	//level_load(NULL);
	level_load("testlevel.wmb");
	init_star_cube();
	spawn_player();
	hud_init();
	hud_show();
	populate_space(50);
	you = ent_create("planet0.mdl", vector(10000, 0, 0), NULL);
	vec_set(you.scale_x, vector(50, 50, 50));
}

void level_restart()
{
	hud_reinit();
	hud_show();
}

void level_stop()
{
	uninit_star_cube();
	hud_hide();
}