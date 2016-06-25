#ifndef __INC_MENU_C
#define __INC_MENU_C

#include "level.h"
#include "startup.h"

void resizeMenu() {
	menu_txt->pos_x = screen_size.x / 2;
	menu_txt->pos_y = screen_size.y / 2;
}

void keyMenu() {
	closeMenu();
}
void showMenu()
{
	menu_is_closed = false;
	on_anykey = keyMenu;
	sky_color.red = 0;
	sky_color.green = 0;
	sky_color.blue = 0;
	wait(1);
	level_load("menu.wmb");
	init_star_cube();
	menu_hnd_music = media_loop("media\\theme.mp3", NULL, 100);
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
	menu_txt = welcome_txt;
	
	menu_txt->pos_x = screen_size.x / 2;
	menu_txt->pos_y = screen_size.y / 2;
	
	float aleph = 0;
	while(aleph < 1) {
		if(menu_is_closed)
			return;
		aleph = clamp(aleph+time_step*.05, 0, 1);
		menu_txt.alpha = aleph*100;
		wait(1);
	}
	wait(-2);
	while(aleph > 0) {
		if(menu_is_closed)
			return;
		aleph = clamp(aleph-time_step*.05, 0, 1);
		menu_txt.alpha = aleph*100;
		wait(1);
	}
	if(menu_is_closed)
			return;
	str_cpy((menu_txt->pstring)[0], "a \"Skeleton Crew\" production");
	while(aleph < 1) {
		if(menu_is_closed)
			return;
		aleph = clamp(aleph+time_step*.05, 0, 1);
		menu_txt.alpha = aleph*100;
		wait(1);
	}
	wait(-2);
	while(aleph > 0) {
		if(menu_is_closed)
			return;
		aleph = clamp(aleph-time_step*.05, 0, 1);
		menu_txt.alpha = aleph*100;
		wait(1);
	}
	wait(-2);
	if(menu_is_closed)
			return;
	str_cpy((menu_txt->pstring)[0], "Press button to start");
	VECTOR vv;
	vv.x = 536;
	vv.y = 0;
	vv.z = -100;
	if (vec_to_screen(vv,camera)) // if visible on screen
	{
	  menu_txt->pos_y = vv.y;
	}

	while(aleph < 1) {
		if(menu_is_closed)
			return;
		aleph = clamp(aleph+time_step*.05, 0, 1);
		menu_txt.alpha = aleph*100;
		wait(1);
	}
}

void closeMenu() {
	on_anykey = NULL;
	menu_is_closed = true;
	var volume = 100;
	while(volume > 0) {
		volume -= 5.*time_step;
		media_tune(menu_hnd_music, volume, 100, 0);
		wait(1);
	}
	media_stop(volume);
	ptr_remove(menu_txt);
	level_start();
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