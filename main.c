#include <acknex.h>
#include <default.c>

#define PRAGMA_PATH "include"
#define PRAGMA_PATH "src"
#define PRAGMA_PATH "models"

#include "level.h"
#include "player.h"

#include "level.c"
#include "player.c"

void main() {
	
	level_load(NULL);
	
	init_star_cube();
	
	spawn_player();
	
	while(1) {
		
		wait(1);
	}
}