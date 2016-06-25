#ifndef LEVEL_C_
#define LEVEL_C_

var vLevelSounds = 0;
SOUND* sndLevelSounds[5];

void init_star_cube() {
	skyCube = ent_createlayer("textures\\cubemaps\\uni2+6.bmp", SKY | CUBE | SHOW, 2);
}

void uninit_star_cube() {
	if (skyCube != NULL) {
		ent_remove(skyCube);
		skyCube = NULL;
	}
}

void init_levelSounds()
{
	if (vLevelSounds == 0)
	{
		vLevelSounds = 1;
	}
	while (vLevelSounds == 1)
	{
		var vWait = random(10) + 5;
		var vSound = integer(random(5));
		wait(-vWait);
		snd_play(sndLevelSounds[vSound], 50 + random(50), random(100) - 50);
	}
}

void uninit_levelSounds()
{
	vLevelSounds = 0;
}

void levelSounds_startup()
{
	sndLevelSounds[0] = snd_create("space1.wav");
	sndLevelSounds[1] = snd_create("space2.wav");
	sndLevelSounds[2] = snd_create("space4.wav");
	sndLevelSounds[3] = snd_create("space6.wav");
	sndLevelSounds[4] = snd_create("space7.wav");
}

#endif