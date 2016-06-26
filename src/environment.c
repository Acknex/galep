//
// Created by Slin on 24.06.2016.
//

int spaceParticleCount = 0;
int spaceJunkCount = 0;

void space_particle_event(PARTICLE *particle)
{
	vec_for_angle(particle.vel_x, player.pan);
	vec_normalize(particle.vel_x, 30);
	particle.lifespan = 100;
//	particle.alpha = minv(maxv(vec_dist(particle.x, player.x) - 50, 0)/100, 1)*100;
	VECTOR temp;
	vec_set(temp, particle.x);
	if(abs(particle.x-camera.x) > 2000 || abs(particle.y-camera.y) > 2000 || abs(particle.z-camera.z) > 2000 || !vec_to_screen(temp, camera))
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
	vec_add(particle.x, vector(random(4000) - 2000, random(4000) - 2000, random(4000) - 2000));
	vec_set(particle.blue, vector(255, 150, 150));
	set(particle, BRIGHT | TRANSLUCENT | BEAM);
	particle.alpha = 100;
	particle.size = 0.5 + random(1.0);
	particle.lifespan = 100;
	particle.event = space_particle_event;
}

void space_junk()
{
	vec_set(my.x, player.x);
	vec_add(my.x, vector(random(8000) - 4000, random(8000) - 4000, random(8000) - 4000));

	path_set(my, "path_000");
	var pathDist = splineDistance-4000;
	while(pathDist < splineDistance+4000)
	{
		VECTOR temp;
		path_spline(my, temp, pathDist);
		pathDist += 100;
		if(vec_dist(temp, my.x) < 2000)
		{
			spaceJunkCount -= 1;
			ptr_remove(my);
			my = NULL;
			return;
		}
	}

	vec_scale(my.scale_x, 3+random(5));
	vec_set(my.pan, vector(random(360), random(360), random(360)));
	set(my, TRANSLUCENT);
	my.alpha = 0;
	while(my)
	{
		my.alpha += time_step*5;
		if(my.alpha >= 100)
		{
			my.alpha = 100;
			reset(my, TRANSLUCENT);
		}
		if(abs(my.x-player.x) > 4000 || abs(my.y-player.y) > 4000 || abs(my.z-player.z) > 4000)
		{
			spaceJunkCount -= 1;
			ent_remove(my);
			my = NULL;
		}
		wait(1);
	}
}

void populate_space(int maxParticles, int maxSpaceJunk)
{
	STRING *junkModels[3];
	junkModels[0] = "asteroid0.mdl";
	junkModels[1] = "asteroid1.mdl";
	junkModels[2] = "asteroid2.mdl";

	spaceJunkCount = 0;
	spaceParticleCount = 0;

	wait(1);
	proc_kill(4);

	while(player)
	{
		if(spaceParticleCount < maxParticles)
		{
			effect(space_particle, maxParticles - spaceParticleCount, nullvector, nullvector);
			spaceParticleCount = maxParticles;
		}

		while(spaceJunkCount < maxSpaceJunk)
		{
			int object = (int)random(3);
			ent_create(junkModels[object], nullvector, space_junk);
			spaceJunkCount += 1;
		}

		wait(1);
	}
}

action environment_sun()
{
	vec_set(my.blue, vector(70, 80, 90));
	my.lightrange = 1000000;
}