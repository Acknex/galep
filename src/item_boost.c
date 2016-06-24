#include "items.h"

void item_boost__evt();

action item_boost()
{
	item_setup();	
	my->event = item_boost__evt;
	var vZ = my->z;
	var vOffset = random(500);
	var vParticles = 0;
	//my->material = mtl_specBump;
	my->pan = random(360);
	
	while(!is(me, is_collected))
	{
		vParticles += time_step;
		if (vParticles > 10)
		{
			effect(item_particle, 10, &my->x, nullvector);
			vParticles -= 10;
		}
		my->z = vZ + 10 * sinv(total_ticks * 20 + vOffset);
		my->pan -= 5 * time_step;
		my->tilt = 30 * sinv(total_ticks * 10 + vOffset);
		wait(1);
	}
	item_fade();
}

void item_boost__evt()
{
	if (item_event() != 0)
	{
		error("boost!");
	}
}

