//
// Created by Slin on 25.06.2016.
//

void explosion_smoke_particle_event(PARTICLE *particle)
{
	VECTOR temp;
	vec_set(temp, particle.vel_x);
	vec_scale(temp, time_step*5);
	vec_add(particle.x, temp);
	particle.size += time_step*2;
	particle.alpha -= time_step*1;
	if(particle.alpha <= 0)
	{
		particle.lifespan = 0;
	}
}

void explosion_smoke_particle(PARTICLE *particle)
{
	vec_set(particle.blue, vector(30, 30, 30));
	vec_set(particle.vel_x, vector(random(2) - 1, random(2) - 1, random(2) - 1));
	set(particle, TRANSLUCENT);
	particle.alpha = 50;
	particle.size = 100;
	particle.event = explosion_smoke_particle_event;
}

void explosion_fire_particle_event(PARTICLE *particle)
{
	VECTOR temp;
	vec_set(temp, particle.vel_x);
	vec_scale(temp, time_step*30);
	vec_add(particle.x, temp);
	particle.size -= time_step*6;
	particle.alpha -= time_step*15;
	if(particle.alpha <= 0)
	{
		particle.lifespan = 0;
	}
}

void explosion_fire_particle(PARTICLE *particle)
{
	vec_set(particle.blue, vector(100, 180, 250));
	vec_set(particle.vel_x, vector(random(2) - 1, random(2) - 1, random(2) - 1));
	set(particle, BRIGHT | TRANSLUCENT);
	particle.alpha = 100;
	particle.size = 80;
	particle.event = explosion_fire_particle_event;
}

void explosion_sparks_particle_event(PARTICLE *particle)
{
	VECTOR temp;
	vec_set(temp, particle.vel_x);
	vec_scale(temp, time_step*30);
	vec_add(particle.x, temp);
	particle.alpha -= time_step*5;
	if(particle.alpha <= 0)
	{
		particle.lifespan = 0;
	}
}

void explosion_sparks_particle(PARTICLE *particle)
{
	vec_set(particle.blue, vector(80, 80, 200));
	vec_set(particle.vel_x, vector(random(2) - 1, random(2) - 1, random(2) - 1));
	set(particle, BRIGHT | TRANSLUCENT);
	particle.alpha = 100;
	particle.size = 10;
	particle.event = explosion_sparks_particle_event;
}

void start_explosion(VECTOR *position)
{
	effect(explosion_fire_particle, 20+random(10), position, nullvector);
	effect(explosion_sparks_particle, 20+random(10), position, nullvector);
	effect(explosion_smoke_particle, 20+random(10), position, nullvector);

	float timer = 0.0;
	while(timer < 4)
	{
		timer += time_step;
		camera.roll = random(10)-5;
		wait(1);
	}
	camera.roll = 0;
}