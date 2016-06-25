//
// Created by Slin on 25.06.2016.
//

void enemy_shot()
{
	start_explosion(my.x, 2);
	wait(1);
	ptr_remove(my);
}

action act_enemy_bullet() {
	VECTOR vecTarget;
	vec_set(vecTarget, player.x);
	vec_sub(vecTarget, my.x);
	vec_normalize(vecTarget, 1);
	vec_scale(vecTarget, time_step * BULLET_SPEED_E);
	
	int myAge = 0;
	while(me) {
		var dist = c_move(me, vecTarget, nullvector, IGNORE_PASSABLE | IGNORE_PASSENTS | ACTIVATE_SHOOT);
		myAge +=1;
		if (myAge > BULLET_AGE_E || dist < vec_length(vecTarget)*0.8) ptr_remove(me);
		wait(1);
	}
}

void enemy()
{
	VECTOR pathPosition;
	VECTOR pathOffset;
	var pathDistance = splineDistance + 10000;

	vec_set(pathOffset, vector(random(1000)-500, random(1000)-500, random(1000)-500));

	path_set(my, "path_000");
	my.emask |= ENABLE_SHOOT;
	my.event = enemy_shot;
	var cooldown = 0;
	var shotsFired = 0;

	while(my)
	{
		path_spline(my, my.x, pathDistance);
		vec_add(my.x, pathOffset);
		pathDistance -= time_step*10;

		VECTOR temp;
		vec_set(temp, player.x);
		vec_sub(temp, my.x);
		vec_to_angle(my.pan, temp);
		
		// Shoot
		if ((vec_dist(my.x, player.x) < 2000) && (cooldown <= 0)) {
			VECTOR vStartPos;
			vec_set(vStartPos, vector(100,0,0));
			vec_rotate(vStartPos, my.pan);
			vec_add(vStartPos, my.x);
			
			ENTITY* bullet = ent_create(CUBE_MDL, vStartPos, act_enemy_bullet);
			vec_set(bullet.blue, vector(0,0,255));
			set(bullet, LIGHT);
			shotsFired +=1;
		}
		
		if ((shotsFired >= 5) && (cooldown <= 0)) {
			cooldown = 100;
		}
		
		if (cooldown > 0) {
			cooldown -=5 * time_step;
		}

		if(pathDistance < splineDistance-10000)
		{
			ent_remove(my);
			my = NULL;
		}

		wait(1);
	}
}

void spawn_enemies()
{
	while(player)
	{
		wait(-(5+random(10)));
		ent_create("ufo.mdl", nullvector, enemy);
	}
}