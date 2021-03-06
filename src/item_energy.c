#include "items.h"

void item_energy__evt();

action item_energy()
{
	item_setup();
	my->event = item_energy__evt;
	var vZ = my->z;
	var vOffset = random(500);
	var vParticles = 0;
	my->roll = random(360);
	while (!player) wait(1);
	
	while(!is(me, is_collected))
	{
		if (vec_dist(player.x, my.x) < 5000)
		{
			vParticles += time_step;
			if (vParticles > 10)
			{
				effect(item_particle, 10, &my->x, nullvector);
				vParticles -= 10;
			}
			my->z = vZ + 10 * sinv(total_ticks * 20 + vOffset);
			my->pan += 20 * time_step;// * sinv(total_ticks * 2 - vOffset);
		}
		wait(1);
	}
	item_fade();
}

void item_energy__evt()
{
	if (item_evt() != 0)
	{
		hud_addEnergy(20);
	}
}
