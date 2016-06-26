#ifndef PLAYER_C_
#define PLAYER_C_

#include "../include/player.h"

void spawn_player() {
	
	player = ent_create("ufo_lotti.mdl", vector(1000,0,0), act_player);
	entCrosshair = ent_create("textures//crosshair.bmp", vector(1100, 0, 0), NULL);
	entCrosshair2 = ent_create("textures//crosshair.bmp", vector(1100, 0, 0), NULL);
	entEngineFx = ent_create("models/ufo_engine_fx.mdl", vector(1000,0,0), act_engine_fx);
	entEngineFx->skill1 = player;
	

	set(entCrosshair, PASSABLE | LIGHT | ZNEAR);
	set(entCrosshair2, PASSABLE | LIGHT | ZNEAR);
	set(player, ENABLE_TRIGGER | ZNEAR);
	vec_scale(entCrosshair.scale_x, 2.0);
	vec_scale(entCrosshair2.scale_x, 2.0);
	player.trigger_range = 20;
	player.alpha = 100;
	player.flags &= ~TRANSLUCENT;
	//player.skill1 = ent_playloop2(player, sndUfo, 100, 2000);
}

action act_engine_fx() {
	my->flags |= BRIGHT;
	vec_scale(my->scale_x, 14.);
	var time_passed;
	wait(1);
	while(me) {
		my->x = -2.4;
		my->y = 2.3;
		my->z = -50;
		vec_rotate(my->x, ((ENTITY*)my->skill1)->pan);
		vec_add(my->x, ((ENTITY*)my->skill1)->x);
		vec_set(my->pan, ((ENTITY*)my->skill1)->pan);
		wait(1);
	}
}

void playerEvent() {
	if (event_type == EVENT_SHOOT) {
		if (player_hit_cooldown <= 0) {
			snd_play(sndDie, 100, 0);
			vHudEnergy -=ENEMY_DAMAGE;
			player_hit_cooldown = 100;
		}
	}
}

action act_player() {
	VECTOR vSplinePos, vLastPos, vDir, vScreen, vCam, vCrosshair, vCamAngle, vLerp, vScreenUfo, vCrossAngle, vNewCamAng, vOldScreenBorder;
	
	vec_zero(vSplinePos);
	vec_zero(vLastPos);
	vec_zero(vDir);
	vec_zero(vScreen);
	vec_zero(vCam);
	vec_zero(vCamAngle);
	vec_zero(vLerp);
	vec_zero(vScreenUfo);
	vec_zero(vCrossAngle);
	vec_zero(vNewCamAng);

	vec_set(vOldScreenBorder, vector(-screen_size.x*0.5, -screen_size.y*0.5, 0));
	
	my.trigger_range = 20;
	my.emask |= ENABLE_SHOOT;
	
	my.event = playerEvent;
	smokeCooldown = 0;
	
	vec_set(vCrosshair, vector(screen_size.x / 2, screen_size.y / 2, 0));
	
	path_set(me, "path_000");
	splineDistance = 0;
	
	while(me && (vHudEnergy > 0)) {

		// Move camera
		path_spline(me, vSplinePos, splineDistance);
		splineDistance += 70 * time_step + vHudSpeed / 100 + player_boost * 5 * time_step;
		
		// Turn camera towards path
		vec_diff(vDir, vSplinePos, vLastPos);
		vec_to_angle(camera.pan, vDir);
		vec_set(vLastPos, vSplinePos);
		
		vec_set(camera.x, vSplinePos);
		
		// Move crosshair
		if (entCrosshair != NULL) {
			
			vCrosshair.x += ((key_d || key_cur) - (key_a || key_cul)) * time_step * 35;
			vCrosshair.y += ((key_w || key_cuu) - (key_s || key_cud)) * time_step * 35;
			
			if ((((key_d || key_cur) - (key_a || key_cul)) == 0) && (((key_w || key_cuu) - (key_s || key_cud)) == 0)) {
				vec_lerp(vCrosshair, vCrosshair, vector(screen_size.x / 2, screen_size.y / 2, 0), 0.1 * time_step);
			}
			
			vCrosshair.x = clamp(vCrosshair.x, 0, screen_size.x);
			vCrosshair.y = clamp(vCrosshair.y, 0, screen_size.y);
			
			vScreen.x = vCrosshair.x;
			vScreen.y = vCrosshair.y;
			vScreen.z = 1200;
			vec_for_screen(vScreen, camera);
			
			vec_set(entCrosshair.x, vScreen);
			
			// Camera point to crosshair
			vec_set(vCam, entCrosshair.x);
			vec_sub(vCam, camera.x);
			vec_to_angle(vCamAngle.x, vCam.x);

			vec_set(entCrosshair.pan, vCamAngle.x);
			vec_set(entCrosshair2.pan, vCamAngle.x);
			
			VECTOR temp;
			ang_diff(temp, vCamAngle, camera.pan);
			vec_scale(temp, minv(time_step*5, 1.0));
			ang_add(camera.pan, temp);
			
			// Move player
			vScreenUfo.x = vCrosshair.x;
			vScreenUfo.y = vCrosshair.y;
			vScreenUfo.z = 500;

			vec_set(temp, my.x);
			vec_to_screen(temp, camera);
			temp.z = 500;
			var factor = minv(maxv(vec_dist(temp, vScreenUfo)-screen_size.x*0.2, 0)/(screen_size.x*0.1), 1);
			vec_lerp(vScreenUfo, temp, vScreenUfo, factor);
			vec_for_screen(vScreenUfo, camera);

			vec_lerp(my.x, my.x, vScreenUfo, minv(time_step*0.5, 1.0));

			//Place second crosshair
			vec_lerp(entCrosshair2.x, my.x, entCrosshair.x, 0.7);
			
			// Rotate player
			vec_set(temp, entCrosshair.x);
			vec_sub(temp, my.x);
			vec_to_angle(my.pan, temp);
			
			// Shoot
			if ((key_space || mouse_left) && (shootCooldown <= 0)) {
				shootCooldown = BULLET_COOLDOWN_E;
				player_fire();
			}
	
			if (shootCooldown > 0) shootCooldown -=80 * time_step;
			
			// Boost
			if (boost_cooldown > 0) {
				if (camera.arc < 120) {
					camera.arc +=5 * time_step;
				}
				boost_cooldown -=20 * time_step;
			} else {
				if (camera.arc > 90) {
					camera.arc -=5 * time_step;
				}
				player_boost = 0;
				boost_cooldown = 0;
			}
			
			// Enable events
			c_scan(my.x, my.pan, vector(360, 0, 200), IGNORE_ME | IGNORE_WORLD | SCAN_ENTS);
		}
		
		// Smoke if ship is broken
		if (vHudEnergy < 50 && smokeCooldown <= 0) {
			smoke(my.x, 0.25+(50.0-vHudEnergy)/100.0);
			smokeCooldown = (1.0-(50.0-vHudEnergy)/50.0)*5.0;
		}
		else
		{
			smokeCooldown -= time_step;
		}

		// sparks if ship is on boost
		if (player_boost > 0) {
			//sparks(my.x, 0.25+random(0.5));
		}
		
		if (player_hit_cooldown > 0) {
			set(me, TRANSLUCENT);
			my.alpha = 40 + 25 * cos(player_hit_cooldown * 50);
			player_hit_cooldown -=time_step;
			if (player_hit_cooldown <= 0) {
				reset(me, TRANSLUCENT);
				my.alpha = 50;
			}
		}

		wait(1);
	}
	
	if (vHudEnergy <= 0) {
		press_enter_to_restart();
	}
}

action act_bullet() {
	VECTOR vecTarget;
	vec_set(vecTarget, entCrosshair.x);
	vec_sub(vecTarget, player.x);
	vec_normalize(vecTarget, 1);
	vec_scale(vecTarget, time_step * BULLET_SPEED_E);
	
	int myAge = 0;
	while(me) {
		you = player;
		var dist = c_move(me, vecTarget, nullvector, IGNORE_PASSABLE | IGNORE_PASSENTS | ACTIVATE_SHOOT | IGNORE_YOU);
		myAge +=1;
		if (myAge > BULLET_AGE_E || dist < vec_length(vecTarget)*0.8) ptr_remove(me);
		wait(1);
	}
}

void player_fire() {
	if ((player == NULL) || (entCrosshair == NULL)) return;
	
	snd_play(sndLaser, 20, 0);
	
	VECTOR vStartPos;
	vec_set(vStartPos, vector(100,0,0));
	vec_rotate(vStartPos, player.pan);
	vec_add(vStartPos, player.x);
	
	ENTITY* bullet = ent_create(CUBE_MDL, vStartPos, act_bullet);
	vec_set(bullet.blue, vector(0,255,0));
	set(bullet, LIGHT);
}

void boost_player() {
	if (boost_cooldown > 0) return;
	snd_play(sndInfinity, 100, 0);
	boost_cooldown = BOOST_COOLDOWN_E;
	player_boost = 5;
}

void player_reinit() {
	player_speed = PLAYER_SPEED_E;
	player_boost = 10;
	boost_cooldown = 0;
	player_hit_cooldown = 0;
}

#endif