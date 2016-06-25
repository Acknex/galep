//
// Created by Slin on 25.06.2016.
//

void explosion_smoke_particle_event(PARTICLE *particle)
{

}

void explosion_smoke_particle(PARTICLE *particle)
{

}

void explosion_fire_particle_event(PARTICLE *particle)
{
	VECTOR temp;
	vec_set(temp, particle.vel_x);
	vec_scale(temp, time_step*16);
	vec_add(particle.x, temp);
}

void explosion_fire_particle(PARTICLE *particle)
{
	vec_set(particle.x, camera.x);
	vec_add(particle.x, vector(random(1000) - 500, random(1000) - 500, random(1000) - 500));
	vec_set(particle.blue, vector(100, 150, 200));
	vec_set(particle.vel_x, vector(random(2) - 1, random(2) - 1, random(2) - 1));
	set(particle, BRIGHT | TRANSLUCENT);
	particle.alpha = 100;
	particle.size = 20;
//	particle.lifespan = 100;
	particle.event = space_particle_event;
}

void start_explosion(VECTOR *position)
{
	effect(explosion_fire_particle, 20+random(10), position, nullvector);
}