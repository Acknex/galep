//
// Created by Slin on 24.06.2016.
//

int spaceParticleCount = 0;

void space_particle_event(PARTICLE *particle)
{
	particle.vel_x = -20;
	particle.lifespan = 100;
	particle.alpha = minv(maxv(vec_dist(particle.x, player.x), 0)/30, 1)*100;
	VECTOR temp;
	vec_set(temp, particle.x);
	if(abs(particle.x-camera.x) > 500 || abs(particle.y-camera.y) > 500 || abs(particle.z-camera.z) > 500 || !vec_to_screen(temp, camera))
	{
		spaceParticleCount -= 1;
		particle.lifespan = 0;
	}
}

void space_particle(PARTICLE* particle)
{
	vec_set(particle.x, camera.x);
	vec_add(particle.x, vector(random(1000) - 500, random(1000) - 500, random(1000) - 500));
	vec_set(particle.blue, vector(255, 150, 150));
	set(particle, BRIGHT | TRANSLUCENT | BEAM);
	particle.alpha = 100;
	particle.size = 0.7 + random(0.5);
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
