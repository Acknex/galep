#include "level.h"
#include "player.h"

void level_start()
{
	//level_load(NULL);
	level_load("testlevel.wmb");
	init_star_cube();
	spawn_player();
}

void level_restart()
{
}

void level_stop()
{
	uninit_star_cube();
}