#ifndef LEVEL_C_
#define LEVEL_C_

var vLevelSounds = 0;
SOUND* sndLevelSounds[5];
var hndMusicInGame = NULL;

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
		snd_play(sndLevelSounds[vSound], 30 + random(20), random(100) - 50);
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

void press_enter_to_restart() {
	snd_play(sndAiaiaiai, 100, 0);
	
	while(!key_enter) {
		var textWidth = str_width("Press ENTER to restart", NULL);
		draw_text("Press ENTER to restart", (screen_size.x / 2) - (textWidth / 2), screen_size.y / 2, COLOR_WHITE);
		my.pan +=4 * time_step;
		wait(1);
	}
	while(key_enter) wait(1);
	hud_hide();
	level_restart();
}

#endif