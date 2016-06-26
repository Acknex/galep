//
// Created by Slin on 25.06.2016.
//



// ----------------------------------------------------------------------------------
// UFO enemy
// ----------------------------------------------------------------------------------

void enemy_shot()
{
	snd_play(sndExplosion, 100, 0);
	hud_addTime(2);
	start_explosion(my.x, 2);
	wait(1);
	ptr_remove(my);
}

action act_enemy_bullet() {
	VECTOR vecTarget;
	vec_set(vecTarget, player.x);
	vec_sub(vecTarget, my.x);
	vec_normalize(vecTarget, 1);
	vec_scale(vecTarget, time_step * BULLET_SPEED_E*0.15);
	
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
	my.skill1 = ent_playloop2(my, sndUfo, 100, 10000);
	var cooldown = 100;
	var shotsFired = 0;

	VECTOR argh;
	path_spline(my, argh, pathDistance);
	vec_set(my.x, argh);
	vec_add(my.x, pathOffset);
	path_spline(my, argh, pathDistance+50);
	var dist = c_trace(argh, my.x, IGNORE_ME | USE_POLYGON);
	if(dist > 0)
	{
		dist = maxv(dist-100, 0);
		vec_normalize(pathOffset, dist);
	}

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
		if((vec_dist(my.x, player.x) < 5000))
		{
			if ((cooldown <= 0) && pathDistance > splineDistance+500) {
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
		}


		if(pathDistance < splineDistance-10000)
		{
			ent_remove(my);
			my = NULL;
		}

		wait(1);
	}
}

// ----------------------------------------------------------------------------------
// Laser enemy
// ----------------------------------------------------------------------------------

action barrel_enemy() {
	var cooldown = 0;
	var shotsFired = 0;
	vec_scale(my.scale_x, 1.4);

	while(my)
	{		
		my.tilt +=time_step * 4;
		
		if (cooldown <= 0) {
			
			ent_playsound(me, sndLaser, 100);
			
			VECTOR vTemp1, vTemp2;
			vec_for_vertex(vTemp1, me, 57);
			vec_for_vertex(vTemp2, me, 33);
			
			draw_line3d(vTemp1, NULL, 100);
			draw_line3d(vTemp2, COLOR_RED, 100);
			
			c_trace(vTemp1, vTemp2, IGNORE_ME | ACTIVATE_SHOOT);
			
			vec_for_vertex(vTemp1, me, 63);
			vec_for_vertex(vTemp2, me, 39);
			
			draw_line3d(vTemp1, NULL, 100);
			draw_line3d(vTemp2, COLOR_RED, 100);
			
			c_trace(vTemp1, vTemp2, IGNORE_ME | ACTIVATE_SHOOT);
			
			vec_for_vertex(vTemp1, me, 69);
			vec_for_vertex(vTemp2, me, 45);
			
			draw_line3d(vTemp1, NULL, 100);
			draw_line3d(vTemp2, COLOR_RED, 100);
			
			c_trace(vTemp1, vTemp2, IGNORE_ME | ACTIVATE_SHOOT);
			
			vec_for_vertex(vTemp1, me, 75);
			vec_for_vertex(vTemp2, me, 51);
			
			draw_line3d(vTemp1, NULL, 100);
			draw_line3d(vTemp2, COLOR_RED, 100);
			
			c_trace(vTemp1, vTemp2, IGNORE_ME | ACTIVATE_SHOOT);
			
			
			
			shotsFired +=8 * time_step;
			if (shotsFired >= 50) {
				cooldown = 100;
				shotsFired = 0;
			}
		} else {
			cooldown -=8 * time_step;
		}

		wait(1);
	}	
}


void spawn_enemies()
{
	wait(1);
	proc_kill(4);

	while(player)
	{
		var blubb = (1-minv(splineDistance/350000, 1))*8;
		wait(-(2+blubb+random(10)));
		ent_create("ufo.mdl", nullvector, enemy);
	}
}