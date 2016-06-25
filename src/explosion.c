//
// Created by Slin on 25.06.2016.
//

void explosion_fire_particle_event(PARTICLE *particle)
{
	VECTOR temp;
	vec_set(temp, particle.vel_x);
	vec_scale(temp, time_step*30*particle.skill_a);
	vec_add(particle.x, temp);
	particle.size -= time_step*6*particle.skill_a;
	particle.alpha -= time_step*15;
	if(particle.alpha <= 0)
	{
		particle.lifespan = 0;
	}
}

void explosion_fire_particle(PARTICLE *particle)
{
	var size = particle.vel_x;
	particle.skill_a = size;
	vec_set(particle.blue, vector(100, 180, 250));
	vec_set(particle.vel_x, vector(random(2) - 1, random(2) - 1, random(2) - 1));
	set(particle, BRIGHT | TRANSLUCENT);
	particle.alpha = 100;
	particle.size = 80*size;
	particle.event = explosion_fire_particle_event;
}

void explosion_sparks_particle_event(PARTICLE *particle)
{
	VECTOR temp;
	vec_set(temp, particle.vel_x);
	vec_scale(temp, time_step*30*particle.skill_a);
	vec_add(particle.x, temp);
	particle.alpha -= time_step*5/particle.skill_a;
	if(particle.alpha <= 0)
	{
		particle.lifespan = 0;
	}
}

void explosion_sparks_particle(PARTICLE *particle)
{
	var size = particle.vel_x;
	particle.skill_a = size;
	vec_set(particle.blue, vector(80, 80, 255));
	vec_set(particle.vel_x, vector(random(2) - 1, random(2) - 1, random(2) - 1));
	set(particle, BRIGHT | TRANSLUCENT);
	particle.alpha = 100;
	particle.size = (5+random(10));
	particle.event = explosion_sparks_particle_event;
}

void explosion_smoke_particle_event(PARTICLE *particle)
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

void explosion_smoke_particle(PARTICLE *particle)
{
	var size = particle.vel_x;
	particle.skill_a = size;
	vec_set(particle.blue, vector(30, 30, 30));
	vec_set(particle.vel_x, vector(random(2) - 1, random(2) - 1, random(2) - 1));
	set(particle, TRANSLUCENT);
	particle.alpha = 50;
	particle.size = 100*size;
	particle.event = explosion_smoke_particle_event;
}

void start_explosion(VECTOR *position, var size)
{
	effect(explosion_fire_particle, 20+random(10), position, vector(size, 0, 0));
	effect(explosion_sparks_particle, (20+random(10))*size, position, vector(size, 0, 0));
	effect(explosion_smoke_particle, 20+random(10), position, vector(size, 0, 0));

	float timer = 0.0;
	while(timer < 4)
	{
		timer += time_step;
		camera.roll = (random(6)-3)*size;
		wait(1);
	}
	camera.roll = 0;
}

void smoke(VECTOR *position, var size)
{
	effect(explosion_smoke_particle, (20+random(10))*size, position, vector(size, 0, 0));
}

void sparks(VECTOR *position, var size)
{
	effect(explosion_sparks_particle, (20+random(10))*size, position, vector(size, 0, 0));
}