//
// Created by Slin on 24.06.2016.
//

int spaceParticleCount = 0;

void space_particle_event(PARTICLE *particle)
{
	vec_for_angle(particle.vel_x, player.pan);
	vec_normalize(particle.vel_x, 30);
	particle.lifespan = 100;
//	particle.alpha = minv(maxv(vec_dist(particle.x, player.x) - 50, 0)/100, 1)*100;
	VECTOR temp;
	vec_set(temp, particle.x);
	if(abs(particle.x-camera.x) > 1000 || abs(particle.y-camera.y) > 1000 || abs(particle.z-camera.z) > 1000 || !vec_to_screen(temp, camera))
	{
		spaceParticleCount -= 1;
		particle.lifespan = 0;
	}
	else
	{
		temp.x /= screen_size.x;
		temp.y /= screen_size.y;
		temp.z = 0;
		particle.alpha = clamp((vec_dist(temp, vector(0.5, 0.5, 0))-0.1)*200, 0, 100);
	}
}

void space_particle(PARTICLE* particle)
{
	vec_set(particle.x, camera.x);
	vec_add(particle.x, vector(random(2000) - 1000, random(2000) - 1000, random(2000) - 1000));
	vec_set(particle.blue, vector(255, 150, 150));
	set(particle, BRIGHT | TRANSLUCENT | BEAM);
	particle.alpha = 100;
	particle.size = 0.5 + random(1.0);
	particle.lifespan = 100;
	particle.event = space_particle_event;
}

void populate_space(int maxParticles)
{
	wait(1);
	while(1)
	{
		if(spaceParticleCount < maxParticles)
		{
			effect(space_particle, maxParticles - spaceParticleCount, nullvector, nullvector);
		}

		spaceParticleCount = maxParticles;
		wait(1);
	}
}
