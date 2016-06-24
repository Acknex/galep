#ifndef PLAYER_C_
#define PLAYER_C_

void spawn_player() {
	
	if (player != NULL) {
		ent_remove(player);
	}
	player = ent_create("ufo.mdl", vector(20,0,0), act_player);
	set(player, ENABLE_TRIGGER);
	player.trigger_range = 20;
}

action act_player() {
	
	VECTOR vecMoveSpeed;
	VECTOR speed;
	vec_set(speed, vector(0,1,1));
	
	while(me) {
		
		// Speed up movement - or slow down
		if (key_w || key_s) {
			if (speed.z < 1.5) {
				speed.z +=0.004;
			}
		} else {
			if (speed.z > 1.0) {
				speed.z -=0.004;
			}
		}
		
		if (key_a || key_d) {
			if (speed.y < 1.5) {
				speed.y +=0.004;
			}
		} else {
			if (speed.y > 1.0) {
				speed.y -=0.004;
			}
		}
		
		// Calculate player movement
		vecMoveSpeed.z = (key_w - key_s) * time_step * PLAYER_SPEED_E * speed.z;
		vecMoveSpeed.y = (key_a - key_d) * time_step * PLAYER_SPEED_E * speed.y;
		
		// Dont allow to move forward/backwards
		vecMoveSpeed.x = 0;
	
		
		// Keep player in screen
		if ((vecMoveSpeed.z + my.z >= LEVEL_LIMIT_Z_E) || (vecMoveSpeed.z + my.z <= -LEVEL_LIMIT_Z_E)) {
			vecMoveSpeed.z = 0;
		}
		
		if ((vecMoveSpeed.y + my.y >= LEVEL_LIMIT_Y_E) || (vecMoveSpeed.y + my.y <= -LEVEL_LIMIT_Y_E)) {
			vecMoveSpeed.y = 0;
		}
		
		/*var dist = vec_dist(nullvector, vector(0, vecMoveSpeed.y + my.y, vecMoveSpeed.z + my.z));
		
		draw_text(str_for_num(NULL, dist), 10, 10, COLOR_RED);
		
		var factor = 100 / LEVEL_LIMIT_RADIUS_E * dist;
		factor = (100 - factor) / 100;
		
		draw_text(str_for_num(NULL, factor), 10, 30, COLOR_RED);
		
		vec_lerp(vecMoveSpeed.x, nullvector, vecMoveSpeed.x, factor);*/
		
		c_move(me, vecMoveSpeed.x, nullvector, IGNORE_PASSABLE | IGNORE_PASSENTS | IGNORE_ME | GLIDE);
		
		camera_move();
		wait(1);
	}
}

#endif