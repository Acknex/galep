#include <acknex.h>
#include <default.c>
#include <particles.c>

#define PRAGMA_PATH "include"
#define PRAGMA_PATH "src"
#define PRAGMA_PATH "models"
#define PRAGMA_PATH "sounds"
#define PRAGMA_PATH "textures"

#include "menu.h"
#include "level.h"
#include "player.h"
#include "startup.h"
#include "camera.h"
#include "item_boost.h"
#include "item_energy.h"
#include "item_speed.h"
#include "obstacle_asteroid.h"
#include "environment.h"
#include "explosion.h"

#include "level.c"
#include "player.c"
#include "camera.c"
#include "environment.c"
#include "explosion.c"



void main_exit()
{
	hud_close();
}

void main_close()
{
	sys_exit("");
}

void main_resize()
{
	resizeMenu();
}

void main() {
	//video_mode =	12;
	//video_screen = 1;
	on_exit = main_exit;
	on_close = main_close;
	on_resize = main_resize;
	randomize();

	showMenu();
	
	while(1) {
		wait(1);
	}
	
	level_stop();
}

