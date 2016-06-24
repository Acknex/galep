#define ITEM_PARTICLE_COLOR vector(0, 255, 255)

SOUND* sndCollect = "collect.wav";

void item__particleFader(PARTICLE *p);


void item_setup()
{
	my->emask |= ENABLE_TRIGGER; 
	my->trigger_range = 20;
	set (me, PASSABLE);
	my->event = item_event;
}

var item_event()
{
	if (!player || !you)
	{
		return 0;
	}
	
	if (event_type == EVENT_TRIGGER && you == player)
	{
		my->event = NULL;
		set (me, is_collected);
		ent_playsound(me, sndCollect, 1000);
		return 1;
	}
	
	return 0;	
}

void item_fade()
{
	var vTicks = total_ticks;
	VECTOR vecDist;
	
	vec_set(&vecDist, &my->x);
	vec_sub(&vecDist, &player->x);
	while (my->scale_x > 0)
	{
		//scale down item
		my->scale_x = maxv(my->scale_x - 0.1 * time_step, 0);
		my->scale_y = my->scale_x;
		my->scale_z = my->scale_x;
		my->pan += (total_ticks - vTicks) * 10 * time_step;

		//move item towards player
		vec_set(&my->x, &vecDist);
		vec_scale(&my->x, my->scale_x);
		vec_add(&my->x, &player->x);
		wait(1);
	}
	ptr_remove(me);
}

void item_particle (PARTICLE *p) 
{
	VECTOR vecTemp;
	vec_randomize(&vecTemp, 10);
	vec_normalize(&vecTemp, 4);
	vec_add (&p->vel_x, &vecTemp);
	p->vel_y = 0;
	vec_set(&p->blue, ITEM_PARTICLE_COLOR);
	set(p, MOVE | TRANSLUCENT | BRIGHT);
	p->lifespan = 80;
	p->size  = 30 + random(5);
	p->event = item__particleFader;
}

void item__particleFader(PARTICLE *p) 
{
	p->alpha -= 5 * time_step;
	p->size += time_step;
	if (p->alpha <= 0) 
	{
		p->lifespan = 0;
	}
}
