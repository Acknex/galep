

void level_start()
{
	level_load(NULL);
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