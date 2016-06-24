#include <acknex.h>
#include <default.c>

#define PRAGMA_PATH "include"
#define PRAGMA_PATH "src"

#include "level.h"

#include "level.c"

void main() {
	
	level_load("");
	
	init_star_cube();
	
	while(1) {
		
		wait(1);
	}
}