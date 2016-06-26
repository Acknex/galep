#ifndef __INC_MENU_C
#define __INC_MENU_C

#include "level.h"
#include "startup.h"

void resizeMenu() {
	if(menu_show_button) {
		VECTOR vv;
		vv.x = 536;
		vv.y = 0;
		vv.z = -100;
		if (vec_to_screen(vv,camera)) // if visible on screen
		{
		  menu_txt->pos_y = vv.y;
		}
		menu_txt->pos_x = screen_size.x / 2;
	}
	else {
		menu_txt->pos_x = screen_size.x / 2;
		menu_txt->pos_y = screen_size.y / 2;
	}
	
	menu_pan_fade->scale_x = screen_size.x*2;
	menu_pan_fade->scale_y = screen_size.y*2;
}

void keyMenu() {
	closeMenu();
}

void menu_magic_startup() {
	// stop everything, start level
	while(!stop_intro) {
		wait(4);
	}
	
	on_anykey = NULL;
	float volume = 100;
	while(volume > 0) {
		volume -= 5.*time_step;
		menu_pan_fade->alpha = 100-volume;
		wait(1);
	}
	menu_pan_fade->flags &= ~SHOW;
	str_cpy((menu_txt->pstring)[0], "");
	menu_txt->flags &= ~SHOW;
	media_stop(volume);
	uninit_star_cube();
	level_start();
}

void showMenu()
{
	menu_is_closed = false;
	menu_show_button = false;
	stop_intro = false;
	on_anykey = keyMenu;
	camera.arc = 60;
	sky_color.red = 0;
	sky_color.green = 0;
	sky_color.blue = 0;
	wait(1);
	level_load("menu.wmb");
	init_star_cube();
	menu_hnd_music = media_loop("media\\theme.mp3", NULL, 100);
	menu_txt->pos_x = screen_size.x / 2;
	menu_txt->pos_y = screen_size.y / 2;
	menu_txt->flags |= SHOW;
	menu_txt->alpha = 0;
	menu_pan_fade->alpha = 0;
	
	float aleph = 0;	
	while(aleph < 1) {
		if(menu_is_closed || stop_intro)
			return;
		aleph = clamp(aleph+time_step*.05, 0, 1);
		menu_txt.alpha = aleph*100;
		wait(1);
	}
	wait(-2);
	while(aleph > 0) {
		if(menu_is_closed || stop_intro)
			return;
		aleph = clamp(aleph-time_step*.05, 0, 1);
		menu_txt.alpha = aleph*100;
		wait(1);
	}
	if(menu_is_closed)
			return;
	str_cpy((menu_txt->pstring)[0], "a\n Skeleton Crew / Core Team\nproduction");
	while(aleph < 1) {
		if(menu_is_closed || stop_intro)
			return;
		aleph = clamp(aleph+time_step*.05, 0, 1);
		menu_txt.alpha = aleph*100;
		wait(1);
	}
	wait(-2);
	while(aleph > 0) {
		if(menu_is_closed || stop_intro)
			return;
		aleph = clamp(aleph-time_step*.05, 0, 1);
		menu_txt.alpha = aleph*100;
		wait(1);
	}
	wait(-2);
	if(menu_is_closed || stop_intro)
			return;
	str_cpy((menu_txt->pstring)[0], "Press button to start");
	menu_show_button = true;
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
	startIntro();
}

void stopIntro() {
	stop_intro = true;
	on_anykey = NULL;
}

void startIntro() {
	intro_is_finished = false;
	float volume = 100;
	float start = camera.tilt;
	on_anykey = stopIntro;
	while(volume > 0) {
		menu_txt->alpha -= 30.*time_step;
		volume -= 2.*time_step;
		media_tune(menu_hnd_music, volume, 100, 0);
		camera.tilt = start - (100-volume)/100.0*(start+45);
		wait(1);
	}
	if(intro_is_finished  || stop_intro)
		return;
	ENTITY* ufo = ent_create("models/ufo_lotti.mdl", vector(-530, 806, 058), actMenuUFO);
	ENTITY* entEngineFx = ent_create("models/ufo_engine_fx.mdl", vector(1000,0,0), act_engine_fx);
	entEngineFx->skill1 = ufo;
	
	str_cpy((menu_txt->pstring)[0], "Press button to skip");
	menu_txt->flags &= ~(CENTER_X | CENTER_Y);
	menu_txt->pos_x = 0;
	menu_txt->pos_y = screen_size.y-20;
	volume = 0;
	menu_txt->alpha = 0;
	menu_txt->flags |= SHOW;
	while(volume < 1) {
		if(intro_is_finished)
			return;
		volume = clamp(volume+time_step*.05, 0, 1);
		menu_txt->alpha = volume*100;
	}
}

action actMenuUFO() {
	int firstTime = 1;
	var hnd_transmission = NULL;
	if(intro_is_finished)
		return;
	if(!stop_intro)
	{
		media_play("media//priority_juan.ogg", NULL, 100);
	}
	VECTOR* vecDir = vector(20,-40, -40);
	float time_passed = 0;
	while(my) {
		my->roll = sin(total_ticks*.04)*5;
		vecDir.x = 1.80696;
		vecDir.y = -1.04042;
		vecDir.z = -0.83887;
		vec_scale(vecDir.x, time_step*24.);
		vec_add(my->x, vecDir);
		time_passed += time_step/16.;
		if(hnd_transmission != NULL && !media_playing(hnd_transmission)) {
			hnd_transmission = NULL;
			my->skill4 = 1;
			stopIntro();
		}
		if(time_passed > 4 && !stop_intro)
		{
			if(firstTime == 1) {
				hnd_transmission = media_play("media//intro_transmission.ogg", NULL, 100);
				vecDir.x = 1.80696;
				vecDir.y = -1.04042;
				vecDir.z = -0.83887;
				vec_scale(vecDir.x, 24.*80.);
				vec_add(my->x, vecDir);
				firstTime = 0;
			}
			if(my->skill4 != 1) {
				camera->x = 200*2;
				camera->y = 60*2;
				camera->z = 40*2;
				camera->pan = 185;
				camera->tilt = -11;
				camera->roll = 0;
				vec_add(camera->x, my->x);
			}
		}
		wait(1);
	}
}
action titleEntity() {
	float aleph = 0;
	while(aleph < 100) {
		aleph = clamp(aleph+time_step/(16.*9./100.), 0, 100);
		if(menu_is_closed) {
			//my->flags |= INVISIBLE;
			return;
		}
		camera->tilt = 40 - pow(aleph/100.0, 0.5)*40;
		wait(1);
	}
	aleph = 0;
	
	// 9 seconds
	while(aleph < 1) {
		if(menu_is_closed) {
			//my->flags |= INVISIBLE;
			return;
		}
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
		if(menu_is_closed) {
			//my->flags |= INVISIBLE;
			return;
		}
		aleph += time_step*.15;
		my->pan = -90 + sin(aleph)*5.;
		wait(1);
	}
}

action menuStarFlare() {
	my->flags &= ~INVISIBLE;
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