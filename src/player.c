#ifndef PLAYER_C_
#define PLAYER_C_

void spawn_player() {
	
	if (player != NULL) {
		ent_remove(player);
		ent_remove(entCrosshair);
	}
	player = ent_create("ufo.mdl", vector(1000,0,0), act_player);
	entCrosshair = ent_create("textures//crosshair.bmp", vector(1100, 0, 0), NULL);
	set(player, ENABLE_TRIGGER);
	player.trigger_range = 20;
	player.alpha = 100;
	player.flags &= ~TRANSLUCENT;
}

void move_crosshair() {
	
}

action act_player() {
	
	VECTOR vSpeed, vecMoveSpeed, vForce, vLastPos, vDir, vSplinePos;
	
	vec_zero(vSpeed);
	vec_zero(vecMoveSpeed);
	vec_zero(vForce);
	vec_zero(vLastPos);
	vec_zero(vDir);
	vec_zero(vSplinePos);
	
	path_set(me, "path_000");
	var dist = 0;
	
	
	while(me) {
		
		path_spline(me, my.x, dist);
		dist +=30 * time_step;
		
		// Turn towards path
		vec_diff(vDir, my.x, vLastPos);
		vec_to_angle(my.pan, vDir);
		vec_set(vLastPos, my.x);
		
		// Calculate player movement
		vForce.z += (key_w - key_s) * PLAYER_SPEED_E;
		vForce.y += (key_a - key_d) * PLAYER_SPEED_E;
		vForce.x += 0;
		
		// Keep ufo in screen range
		//var dist_y = vec_dist(my.x, 
		
		
		
		/*if (abs(my.y) > LEVEL_LIMIT_Y_E / 100 * 80) {
			if ((my.y < 0) && (vForce.y < 0)) {
				vForce.y = 0;
			}
			
			if ((my.y > 0) && (vForce.y > 0)) {
				vForce.y = 0;
			}
		}
		
		if (abs(my.z) > LEVEL_LIMIT_Z_E / 100 * 80) {
			if ((my.z < 0) && (vForce.z < 0)) {
				vForce.z = 0;
			}
			
			if ((my.z > 0) && (vForce.z > 0)) {
				vForce.z = 0;
			}
		}*/
			
		
		// Accelerate movement
		vec_accelerate(vecMoveSpeed, vSpeed, vForce, 0.2);
		
		c_move(me, vecMoveSpeed.x, nullvector, IGNORE_PASSABLE | IGNORE_PASSENTS | IGNORE_ME | GLIDE | ACTIVATE_TRIGGER);
		
		if (entCrosshair != NULL) {
			entCrosshair.y = my.y * 0.5;
			entCrosshair.z = my.z * 0.5;
		}
		
		camera_move();
		
		if ((key_space) && (shootCooldown == 0)) {
			shootCooldown = BULLET_COOLDOWN_E;
			player_fire();
		}
		if (shootCooldown > 0) shootCooldown -=1;
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
	
	ENTITY* bullet = ent_create(CUBE_MDL, vector(player.x + 100, player.y, player.z), act_bullet);
	vec_set(bullet.blue, vector(0,255,0));
	set(bullet, LIGHT);
	set(bullet, PASSABLE);
}

#endif