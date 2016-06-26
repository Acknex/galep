#include "obstacle.h"
#include "explosion.h"

#define ASTEROID_PENALTY_SPEED 2
#define ASTEROID_PENALTY_ENERGY 10
#define ASTEROID_SHARD_LIFETIME 32
#define OBSTACLE_ASTEROID_SCANRANGE 150
#define ASTEROID_DESTROY_SPEED 2

SOUND* sndCollide = "collide.ogg";


void obstacle_asteroid__evt();
void obstacle_asteroid__destroy();
void obstacle_asteroid__shard();

action obstacle_asteroid()
{
	obstacle_setup();	
	my->event = obstacle_asteroid__evt;
	my->emask |= ENABLE_SHOOT; 
	VECTOR vPos;
	vec_set (&vPos, &my->x);
	var vOffset = random(500);
	var vParticles = 0;
	//my->material = mtl_specBump;
	my->pan = random(360);
	my->roll = random(360);
	
	while(!player) wait(1);
	
	while(!is(me, is_collided))
	{
		if (vec_dist(player.x, my.x) < 5000)
		{
			vParticles += time_step;
			if (vParticles > 5)
			{
				effect(obstacle_particle, 10, &my->x, nullvector);
				vParticles -= 5;
			}
			my->x = vPos.x + 25 * sinv(total_ticks * 5 + vOffset);
			my->y = vPos.y + 25 * sinv(total_ticks * 5 + vOffset * 0.33);
			my->z = vPos.z + 25 * sinv(total_ticks * 5 + vOffset * 0.66);
			my->pan = 30 * sinv(total_ticks * 5 + vOffset * 0.5);
			my->tilt = 30 * sinv(total_ticks * 5 + vOffset);
		}
		wait(1);
	}
	obstacle_asteroid__destroy();
}

void obstacle_asteroid__evt()
{
	var vResult = obstacle_event(OBSTACLE_ASTEROID_SCANRANGE);
	//error(str_for_num(NULL, vResult));
	if (vResult == 1)
	{
		hud_addEnergy(-ASTEROID_PENALTY_ENERGY);	
		hud_addSpeed(-ASTEROID_PENALTY_SPEED);	
		ent_playsound(me, sndCollide, 1000);
//		snd_play(sndCollide, 100, 0);
		start_explosion(my.x, 1);
	}
	else if (vResult == 2)
	{
		hud_addSpeed(ASTEROID_DESTROY_SPEED);	
		snd_play(sndCollide, 100, 0);
	}
}

void obstacle_asteroid__destroy()
{
	var i;
	for (i = 0; i < 20; i++)
	{
		ent_create("asteroid_shard.mdl", &my->x, obstacle_asteroid__shard);
	}

	set (my, TRANSLUCENT);
	my->alpha = 100;
	while(my->alpha > 0)
	{
		wait(1);
		my->alpha -= 20* time_step;
	}
	my->alpha = 0;
	wait (-0.5);
	ptr_remove(me);
}

void obstacle_asteroid__shard()
{
	var vLifeTime = ASTEROID_SHARD_LIFETIME;
	VECTOR vecTemp;
	VECTOR vecPos;
	my->pan = random(360);
	my->roll = random(360);
	my->alpha = 100;
	set (my, PASSABLE);
	vec_randomize(&vecTemp, 1000);
	vec_normalize(&vecTemp, 300);
	vec_set(&vecPos, &my->x);
	vec_add(&vecTemp, &vecPos);
	
	while(vLifeTime > 0)
	{
		wait(1);
		vec_lerp(&my->x, &vecTemp, &vecPos, vLifeTime / ASTEROID_SHARD_LIFETIME);
		my->pan -= 15 * time_step;
		if (vLifeTime < 0.5 * ASTEROID_SHARD_LIFETIME)
		{
			set(my, TRANSLUCENT);
			my->alpha = maxv(0, vLifeTime * 100 / 0.5 * ASTEROID_SHARD_LIFETIME);
		}
		
		vLifeTime -= time_step;
	}
	ptr_remove (me);
}



