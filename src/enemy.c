//
// Created by Slin on 25.06.2016.
//

void enemy()
{
	VECTOR pathPosition;

	path_set(my, "path_000");
	path_spline(my, my.x, splineDistance + 10000);
	vec_add(my.x, vector(random(1000)-500, random(1000)-500, random(1000)-500));

	while(my)
	{
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