#ifndef PLAYER_C_
#define PLAYER_C_

void spawn_player() {
	
	if (player != NULL) {
		ent_remove(player);
		ent_remove(entCrosshair);
	}
	player = ent_create("ufo.mdl", vector(1000,0,0), act_player);
	entCrosshair = ent_create("textures//crosshair.bmp", vector(1100, 0, 0), NULL);
	//vec_scale(entCrosshair.scale_x, 1);
	set(player, ENABLE_TRIGGER);
	player.trigger_range = 20;
}

void move_crosshair() {
	
}

action act_player() {
	
	VECTOR vecMoveSpeed;
	
	VECTOR vSpeed, vMove, vForce;
	
	vec_zero(vSpeed);
	vec_zero(vMove);
	vec_zero(vForce);
	
	while(me) {
		
		// Calculate player movement
		vForce.z = (key_w - key_s) * PLAYER_SPEED_E;
		vForce.y = (key_a - key_d) * PLAYER_SPEED_E;
		vForce.x = 0;
		
		//var dist = vec_dist(my.x, nullvector);
		
		//draw_text(str_for_num(NULL, dist), 10, 10, COLOR_RED);
		
		/*if (dist > LEVEL_LIMIT_RADIUS_E) {
			vec_lerp(vForce, nullvector, vForce, 0.5);
		}*/
		
		vec_accelerate(vecMoveSpeed, vSpeed, vForce, 0.2);
		
		// Keep player in screen
		if ((vecMoveSpeed.z + my.z >= LEVEL_LIMIT_Z_E) || (vecMoveSpeed.z + my.z <= -LEVEL_LIMIT_Z_E)) {
			vecMoveSpeed.z = 0;
		}
		
		if ((vecMoveSpeed.y + my.y >= LEVEL_LIMIT_Y_E) || (vecMoveSpeed.y + my.y <= -LEVEL_LIMIT_Y_E)) {
			vecMoveSpeed.y = 0;
		}
		
		c_move(me, vecMoveSpeed.x, nullvector, IGNORE_PASSABLE | IGNORE_PASSENTS | IGNORE_ME | GLIDE | ACTIVATE_TRIGGER);
		
		if (entCrosshair != NULL) {
			c_move(entCrosshair, vecMoveSpeed.x, nullvector, IGNORE_PASSABLE | IGNORE_PASSENTS | GLIDE);
		}
		
		camera_move();
		wait(1);
	}
}

#endif