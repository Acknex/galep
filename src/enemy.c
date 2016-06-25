//
// Created by Slin on 25.06.2016.
//

void enemy()
{
	VECTOR pathPosition;
	VECTOR pathOffset;
	var pathDistance = splineDistance + 10000;

	vec_set(pathOffset, vector(random(1000)-500, random(1000)-500, random(1000)-500));

	path_set(my, "path_000");

	while(my)
	{
		path_spline(my, my.x, pathDistance);
		vec_add(my.x, pathOffset);
		pathDistance -= time_step*10;

		VECTOR temp;
		vec_set(temp, player.x);
		vec_sub(temp, my.x);
		vec_to_angle(my.pan, temp);

		wait(1);
	}
}

void spawn_enemies()
{
	while(player)
	{
		wait(-(5+random(10)));
		ent_create("ufo.mdl", nullvector, enemy);
	}
}