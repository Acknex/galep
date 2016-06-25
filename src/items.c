#define ITEM_PARTICLE_COLOR vector(0, 255, 255)

SOUND* sndCollect = "collect.wav";

void item__particleFader(PARTICLE *p);


void item_setup()
{
	my->emask |= ENABLE_DETECT; 
//	my->emask |= ENABLE_TRIGGER; 
//	my->trigger_range = 20;
	set (me, PASSABLE);
	my->event = item_event;
}

var item_event()
{
	if (!player || !you)
	{
		return 0;
	}
	
//	if (event_type == EVENT_TRIGGER && you == player)
	if (event_type == EVENT_DETECT && you == player)
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
	var vLerp = 1;
	VECTOR vecPos;
	VECTOR vecScale;
	
	vec_set(&vecPos, &my->x);
	vec_set(&vecScale, &my->scale_x);
	
	while (vLerp > 0)
	{
		//move item towards player
		vec_lerp(&my->x, &player->x, &vecPos, vLerp);
		vec_set(&my->scale_x, &vecScale);
		vec_scale(&my->scale_x, vLerp);
		my->pan += (total_ticks - vTicks) * 10 * time_step;
		wait(1);

		vLerp -= maxv(0.001, 0.1 * time_step); 
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

