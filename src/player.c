#ifndef PLAYER_C_
#define PLAYER_C_

void spawn_player() {
	
	if (player != NULL) {
		ent_remove(player);
	}
	player = ent_create("ufo.mdl", vector(20,0,0), act_player);
}

action act_player() {
	
	VECTOR vecMoveSpeed;
	
	while(me) {
		
		vecMoveSpeed.z = (key_w - key_s) * time_step * PLAYER_SPEED_E;
		vecMoveSpeed.y = (key_a - key_d) * time_step * PLAYER_SPEED_E;
		vecMoveSpeed.z = clamp(vecMoveSpeed.z, -20, 20);
		vecMoveSpeed.y = clamp(vecMoveSpeed.y, -20, 20);
		vecMoveSpeed.x = 0;
		
		if ((vecMoveSpeed.z + my.z >= LEVEL_LIMIT_Z_E) || (vecMoveSpeed.z + my.z <= -LEVEL_LIMIT_Z_E)) {
			vecMoveSpeed.z = 0;
		}
		
		if ((vecMoveSpeed.y + my.y >= LEVEL_LIMIT_Y_E) || (vecMoveSpeed.y + my.y <= -LEVEL_LIMIT_Y_E)) {
			vecMoveSpeed.y = 0;
		}
		
		c_move(me, vecMoveSpeed.x, nullvector, IGNORE_PASSABLE | IGNORE_PASSENTS | IGNORE_ME | GLIDE);
		wait(1);
	}
}

#endif