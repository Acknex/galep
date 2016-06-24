#include "level.h"
#include "player.h"
#include "environment.h"

void level_start()
{
	//level_load(NULL);
	level_load("testlevel.wmb");
	init_star_cube();
	spawn_player();
	populate_space(200);
}

void level_restart()
{
}

void level_stop()
{
	uninit_star_cube();
}