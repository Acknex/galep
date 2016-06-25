#ifndef __INC_MENU_C
#define __INC_MENU_C

void showMenu()
{
	sky_color.red = 0;
	sky_color.green = 0;
	sky_color.blue = 0;
	wait(1);
	level_load("menu.wmb");
	var handle = media_loop("music/theme.mp3", NULL, 100);
}

action titleEntity() {
	float aleph = 0;
	wait(-1);
	while(aleph < 1) {
		aleph = clamp(aleph+time_step*.1, 0, 1);
		float alpha = pow(aleph,4);
		my->x = -20 + alpha*(536+20);
		my->y = 0;
		my->z = -30 + alpha*30;
		my->pan = -90;
		my->roll = -90 + alpha*90;
		wait(1);
	}
	aleph = 0;
	while(1) {
		aleph += time_step*.15;
		my->pan = -90 + sin(aleph)*5.;
		wait(1);
	}
}
#endif __INC_MENU_C