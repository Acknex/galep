#include <acknex.h>
#include <default.c>

#define PRAGMA_PATH "include"
#define PRAGMA_PATH "src"
#define PRAGMA_PATH "models"

#include "level.h"
#include "player.h"
#include "startup.h"

#include "level.c"
#include "player.c"

void main() {
		
	//TODO: fancy menu
	level_start();
	
	while(1) {
		
		wait(1);
	}
	
	level_stop();
}