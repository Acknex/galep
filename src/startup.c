#include "level.h"
#include "player.h"
#include "hud.h"

void level_start()
{
	//level_load(NULL);
	level_load("testlevel.wmb");
	init_star_cube();
	spawn_player();
	hud_init();
	hud_show();
}

void level_restart()
{
	hud_show();
}

void level_stop()
{
	uninit_star_cube();
	hud_hide();
}