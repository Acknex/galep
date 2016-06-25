#ifndef __INC_MENU_C
#define __INC_MENU_C

#include "level.h"

void showMenu()
{
	sky_color.red = 0;
	sky_color.green = 0;
	sky_color.blue = 0;
	wait(1);
	level_load("menu.wmb");
	init_star_cube();
	var handle = media_loop("media\\theme.mp3", NULL, 100);
	TEXT* welcome_txt =	
	{
	  layer = 1;
	  pos_x = 10;
	  pos_y = 10;
	  font = "Arial#20bi";
	  string ("Team AckCon presents");
	  flags = CENTER_X | CENTER_Y  | TRANSLUCENT | SHOW;
	  alpha = 0;
	} 
	
	// TODO: move to on_resize
	welcome_txt->pos_x = screen_size.x / 2;
	welcome_txt->pos_y = screen_size.y / 2;
	
	float aleph = 0;
	while(aleph < 1) {
		aleph = clamp(aleph+time_step*.05, 0, 1);
		welcome_txt.alpha = aleph*100;
		wait(1);
	}
	wait(-2);
	while(aleph > 0) {
		aleph = clamp(aleph-time_step*.05, 0, 1);
		welcome_txt.alpha = aleph*100;
		wait(1);
	}
	str_cpy((welcome_txt->pstring)[0], "a \"Minimal Staff\" production");
	while(aleph < 1) {
		aleph = clamp(aleph+time_step*.05, 0, 1);
		welcome_txt.alpha = aleph*100;
		wait(1);
	}
	wait(-2);
	while(aleph > 0) {
		aleph = clamp(aleph-time_step*.05, 0, 1);
		welcome_txt.alpha = aleph*100;
		wait(1);
	}
}

action titleEntity() {
	float aleph = 0;
	while(aleph < 100) {
		aleph = clamp(aleph+time_step/(16.*9./100.), 0, 100);
		camera->tilt = 40 - pow(aleph/100.0, 0.5)*40;
		wait(1);
	}
	aleph = 0;
	
	// 9 seconds
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

action menuStarFlare() {
	my->scale_x = my->scale_y = 0;
	my->skill1 = 0;
	wait(-(random(8)+9));
	while(my) {
		if(my->skill1 == 0) {
			my->scale_x += .03*time_step;
			if(my->scale_x > 0.4) {
				my->scale_x = 0.4;
				my->skill1 = 1;
			}
			my->scale_y = my->scale_x;
			wait(1);
		}
		else if(my->skill1 == 1) {
			my->scale_x -= .03*time_step;
			if(my->scale_x < 0.07) {
				my->scale_x = 0;
				my->skill1 = 2;
			}
			my->scale_y = my->scale_x;
			wait(1);
		}
		else {
			wait(-(random(4)+4));
			my->skill1 = 0;
		}
	}
}

action menuFlyThrough() {
	my->scale_x = 0.5;
	my->scale_y = 0.1;
	wait(-(random(4)+10));
	while(my) {
		my->y = -500;
		while(my->y < 500) {
			my->y += 150.*time_step;
			wait(1);
		}
		wait(-(random(4)+2));
	}
}
#endif __INC_MENU_C