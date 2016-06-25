#ifndef PLAYER_C_
#define PLAYER_C_

void spawn_player() {
	
	if (player != NULL) {
		ent_remove(player);
		ent_remove(entCrosshair);
	}
	player = ent_create("ufo.mdl", vector(1000,0,0), act_player);
	entCrosshair = ent_create("textures//crosshair.bmp", vector(1100, 0, 0), NULL);
	entEngineFx = ent_create("models/ufo_engine_fx.mdl", vector(1000,0,0), act_engine_fx);
	
	set(player, ENABLE_TRIGGER | PASSABLE);
	set(entCrosshair, PASSABLE);
	player.trigger_range = 20;
	player.alpha = 100;
	player.flags &= ~TRANSLUCENT;
}

action act_engine_fx() {
	my->flags |= BRIGHT;
	vec_scale(my->scale_x, 14.);
	while(1) {
		my->x = -2.4;
		my->y = 2.3;
		my->z = -50;
		vec_rotate(my->x, player->pan);
		vec_add(my->x, player->x);
		vec_set(my->pan, player->pan);
		wait(1);
	}
}

action act_player() {
	VECTOR vSplinePos, vLastPos, vDir, vScreen, vCam, vCrosshair, vCamAngle, vLerp, vScreenUfo;
	
	vec_zero(vSplinePos);
	vec_zero(vLastPos);
	vec_zero(vDir);
	vec_zero(vScreen);
	vec_zero(vCam);
	vec_zero(vCamAngle);
	vec_zero(vLerp);
	vec_zero(vScreenUfo);
	
	my.trigger_range = 20;
	
	vec_set(vCrosshair, vector(MAX_CROSSHAIR_X_E / 2, MAX_CROSSHAIR_Y_E / 2, 0));
	
	path_set(me, "path_000");
	var dist = 0;
	
	while(me) {

		var blubb = 0;
		while(blubb < path_length(my))
		{
			path_spline(me, vSplinePos, blubb);
			blubb += 20;
			draw_line3d(vSplinePos, vector(255, 200, 200), 100);
		}

		// Move camera
		path_spline(me, vSplinePos, dist);
		dist +=30  * time_step + vHudSpeed / 100 + player_boost / 100;
		
		// Turn camera towards path
		vec_diff(vDir, vSplinePos, vLastPos);
		vec_to_angle(camera.pan, vDir);
		vec_set(vLastPos, vSplinePos);
		
		vec_set(camera.x, vSplinePos);
		
		// Move crosshair
		if (entCrosshair != NULL) {
			
			vCrosshair.x += (key_d - key_a) * time_step * 50;
			vCrosshair.y += (key_s - key_w) * time_step * 50;
			
			if (((key_d - key_a) == 0) && ((key_s - key_w) == 0)) {
				vec_lerp(vCrosshair, vCrosshair, vector(MAX_CROSSHAIR_X_E / 2, MAX_CROSSHAIR_Y_E / 2, 0), 0.4 * time_step);
			}
			
			vCrosshair.x = clamp(vCrosshair.x, 0, MAX_CROSSHAIR_X_E);
			vCrosshair.y = clamp(vCrosshair.y, 0, MAX_CROSSHAIR_Y_E);
			
			vScreen.x = vCrosshair.x;
			vScreen.y = vCrosshair.y;
			vScreen.z = 500;
			vec_for_screen(vScreen, camera);
			
			vec_set(entCrosshair.x, vScreen);
			
			// Camera point to crosshair
			vec_set(vCam, entCrosshair.x);
			vec_sub(vCam, camera.x);
			vec_to_angle(vCamAngle.x, vCam.x);
			vec_lerp(camera.pan, camera.pan, vCamAngle.x, 0.8);
			
			// Move player
			vScreenUfo.x = vCrosshair.x * 0.8;
			vScreenUfo.y = vCrosshair.y * 0.8;
			vScreenUfo.z = 500;
			vec_for_screen(vScreenUfo, camera);
			vec_lerp(vLerp, camera.x, vScreenUfo.x, 0.8);
			vec_set(player.x, vLerp);
			
			// Rotate player
			vec_set(my.pan, vCamAngle.x);
			
			// Shoot
			if ((key_space) && (shootCooldown <= 0)) {
				shootCooldown = BULLET_COOLDOWN_E;
				player_fire();
			}
	
			if(key_e && shootCooldown == 0)
			{
				shootCooldown = BULLET_COOLDOWN_E;
				start_explosion(my.x, 0.5+random(3));
			}
	
			if (shootCooldown > 0) shootCooldown -=80 * time_step;
			
			// Boost
			if (boost_cooldown > 0) {
				boost_cooldown -=80 * time_step;
			} else {
				player_boost = 0;
				boost_cooldown = 0;
			}
			
			// Enable events
			c_scan(my.x, my.pan, vector(360, 0, 200), IGNORE_ME | IGNORE_WORLD | SCAN_ENTS);
		}
		
		// Smoke if ship is broken
		if (vHudEnergy < 50) {
			smoke(my.x, 0.25+random(0.5));
		}

		// sparks if ship is on boost
		if (player_boost > 0) {
			sparks(my.x, 0.25+random(0.5));
		}

		wait(1);
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
		c_move(me, vecTarget, nullvector, IGNORE_PASSABLE | IGNORE_PASSENTS);
		myAge +=1;
		if (myAge > BULLET_AGE_E) ptr_remove(me);
		wait(1);
	}
}

void player_fire() {
	if ((player == NULL) || (entCrosshair == NULL)) return;
	
	VECTOR vStartPos;
	vec_zero(vStartPos);
	
	vec_set(vStartPos, player.x);
	vec_rotate(vStartPos, player.pan);
	vec_add(vStartPos, vector(100,0,0));
	
	ENTITY* bullet = ent_create(CUBE_MDL, vector(player.x + 100, player.y, player.z), act_bullet);
	vec_set(bullet.blue, vector(0,255,0));
	set(bullet, LIGHT | PASSABLE);
}

void boost_player() {
	if (boost_cooldown > 0) return;
	boost_cooldown = BOOST_COOLDOWN_E;
	player_boost = 5;
}

#endif