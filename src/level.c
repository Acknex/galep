#ifndef LEVEL_C_
#define LEVEL_C_

void init_star_cube() {
	skyCube = ent_createlayer("textures\\cubemaps\\uni2+6.bmp", SKY | CUBE | SHOW, 2);
}

void uninit_star_cube() {
	if (skyCube != NULL) {
		ent_remove(skyCube);
		skyCube = NULL;
	}
}
#endif