#include "explosion.h"

#define OBSTACLE_PARTICLE_COLOR vector(0, 0, 255)

void obstacle__particleFader(PARTICLE *p);


void obstacle_setup()
{
	my->emask |= ENABLE_SCAN; 
	//set (me, PASSABLE);
	my->event = obstacle_event;
}

var obstacle_event(var range)
{
	if (!player || !you)
	{
		return 0;
	}
	
	if (event_type == EVENT_SHOOT)
	{
		my->event = NULL;
		set (me, is_collided);
		return 2;
	}
	
	if (event_type == EVENT_SCAN && you == player)
	{
		if (vec_dist(&your->x, &my->x) < range)
		{
			my->event = NULL;
			set (me, is_collided);
			return 1;
		}
		return 0;
	}
	
	return 0;	
}

void obstacle_particle (PARTICLE *p) 
{
	VECTOR vecTemp;
	vec_randomize(&vecTemp, 100);
	vec_normalize(&vecTemp, 40);
	vec_add (&p->x, &vecTemp);
	vec_set(&p->blue, OBSTACLE_PARTICLE_COLOR);
	set(p, TRANSLUCENT | BRIGHT);
	p->lifespan = 80;
	p->size  = 20 + random(15);
	p->event = obstacle__particleFader;
}

void obstacle__particleFader(PARTICLE *p) 
{
	p->alpha -= 5 * time_step;
	p->size += 7*time_step;
	if (p->alpha <= 0) 
	{
		p->lifespan = 0;
	}
}

