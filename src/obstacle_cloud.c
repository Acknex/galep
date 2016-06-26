#include "obstacle.h"

#define CLOUD_PENALTY_SPEED 6
#define CLOUD_PENALTY_TIME 5
#define CLOUD_PENALTY_TICK 8
#define is_locked FLAG8
#define lockTimer skill42
#define OBSTACLE_CLOUD_SCANRANGE 200

void obstacle_cloud__particle_event(PARTICLE *particle);
void obstacle_cloud__particle(PARTICLE *particle);
void obstacle_cloud__evt();

SOUND* sndSlowdown = "slowdown.wav";



action obstacle_cloud()
{
	obstacle_setup();	
	set(my, INVISIBLE);
	my->event = obstacle_cloud__evt;
	VECTOR vPos;
	vec_set (&vPos, &my->x);
	var vOffset = random(500);
	var vParticles = 0;
	while(!player) wait(1);
	
	while(1)
	{
		if (vec_dist (player.x, my.x) < 4000)
		{
			vParticles += time_step;
			if (vParticles > 10)
			{
				effect(obstacle_cloud__particle, 10, &my->x, vector(1.2,0,0));
				vParticles -= 10;
			}
		}
		
		if (is(me, is_locked))
		{
			if (my->lockTimer > 0)	
			{
				my->lockTimer -= time_step;	
			}
			else
			{
				reset(me, is_locked);
				my->event = obstacle_cloud__evt;
			}
		}
		wait(1);
	}
}


void obstacle_cloud__evt()
{
	if (is(me, is_locked))
	{
		return;
	}
	
	if (obstacle_event(OBSTACLE_CLOUD_SCANRANGE) != 0)
	{
		hud_addSpeed(-CLOUD_PENALTY_SPEED);	
		hud_addTime(-CLOUD_PENALTY_TIME);	
		my->lockTimer = CLOUD_PENALTY_TICK;
		set (me, is_locked);
		ent_playsound(me, sndSlowdown, 500);
	}
}


void obstacle_cloud__particle_event(PARTICLE *particle)
{
	VECTOR temp;
	vec_set(temp, particle.vel_x);
	vec_scale(temp, time_step*5*particle.skill_a);
	vec_add(particle.x, temp);
	particle.size += time_step*2*particle.skill_a;
	particle.alpha -= time_step*1/particle.skill_a;
	if(particle.alpha <= 0)
	{
		particle.lifespan = 0;
	}
}

void obstacle_cloud__particle(PARTICLE *particle)
{
	var size = particle.vel_x;
	particle.skill_a = size;
	vec_set(particle.blue, vector(14, 204, 40));
	vec_set(particle.vel_x, vector(random(2) - 1, random(2) - 1, random(2) - 1));
	set(particle, TRANSLUCENT | LIGHT);
	particle.alpha = 30;
	particle.size = 150*size;
	particle.event = obstacle_cloud__particle_event;
}

