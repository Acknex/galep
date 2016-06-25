#ifndef PLAYER_C_
#define PLAYER_C_

void spawn_player() {
	
	if (player != NULL) {
		ent_remove(player);
		ent_remove(entCrosshair);
	}
	player = ent_create("ufo.mdl", vector(1000,0,0), act_player);
	entCrosshair = ent_create("textures//crosshair.bmp", vector(1100, 0, 0), NULL);
	set(player, ENABLE_TRIGGER | PASSABLE);
	set(entCrosshair, PASSABLE);
	player.trigger_range = 20;
	player.alpha = 100;
	player.flags &= ~TRANSLUCENT;
}

void move_crosshair() {
	
}

action act_player() {
	
	VECTOR vSpeed, vecMoveSpeed, vForce, vLastPos, vDir, vSplinePos, vNewDir;
	
	vec_zero(vSpeed);
	vec_zero(vecMoveSpeed);
	vec_zero(vForce);
	vec_zero(vLastPos);
	vec_zero(vDir);
	vec_zero(vSplinePos);
	vec_zero(vNewDir);
	
	path_set(me, "path_000");
	var dist = 0;
	
	
	while(me) {
		
		path_spline(me, vSplinePos, dist);
		dist +=30 * time_step;
		
		// Turn towards path
		vec_diff(vDir, vSplinePos, vLastPos);
		vec_to_angle(my.pan, vDir);
		vec_set(vLastPos, vSplinePos);
		
		// Calculate player movement
		var facZ = 0;
		if (abs(width) < 200) facZ = 1;
		var facY = 0;
		if (abs(height) < 200) facY = 1;
		
		vForce.z += (key_w - key_s) * PLAYER_SPEED_E * facZ;
		vForce.y += (key_a - key_d) * PLAYER_SPEED_E * facY;
		vForce.x += 0;
		
		width += (key_w - key_s);
		height += (key_a - key_d);
	
		if (width < -200) width = -200;
		if (width > 200) width = 200;
		if (height < -200) height = -200;
		if (height > 200) height = 200;
		
		var dist = vec_dist(vSplinePos, my.x);
		dist = (100 / LEVEL_LIMIT_Y_E) * dist;
		
		// Accelerate movement
		vec_accelerate(vecMoveSpeed, vSpeed, vForce, 1.0 - dist / 100);
		
		vec_set(vNewDir, vSplinePos);
		vec_sub(vNewDir, my.x);
		//vec_sub(vSplinePos, my.x);
		
		c_move(me, vecMoveSpeed, vNewDir, IGNORE_PASSABLE | IGNORE_PASSENTS | IGNORE_ME | GLIDE | ACTIVATE_TRIGGER | IGNORE_WORLD);
		
		/*if (entCrosshair != NULL) {
			entCrosshair.y = my.y * 0.5;
			entCrosshair.z = my.z * 0.5;
		}*/
		
		if (entCrosshair != NULL) {
			vec_set(vNewDir, my.x);
			vec_rotate(vNewDir, camera.pan);
			vec_add(vNewDir, vector(1100, 0, 0));
			vec_set(entCrosshair.x, vNewDir);
			//entCrosshair.pan = player.pan;
		}
		
		camera_move();
		
		if ((key_space) && (shootCooldown == 0)) {
			shootCooldown = BULLET_COOLDOWN_E;
			player_fire();
		}

		if(key_e && shootCooldown == 0)
		{
			shootCooldown = BULLET_COOLDOWN_E;
			start_explosion(my.x);
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