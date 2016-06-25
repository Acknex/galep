#include "items.h"
#include "hud.h"

void item_speed__evt();

action item_speed()
{
	item_setup();	
	my->event = item_speed__evt;
	var vZ = my->z;
	var vOffset = random(500);
	var vParticles = 0;
	//my->material = mtl_specBump;
	my->pan = random(360);
	my->roll = random(360);
	while(!player) wait(1);
	
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
			my->pan -= 5 * time_step;
			my->tilt = 30 * sinv(total_ticks * 10 + vOffset);
		}
		wait(1);
	}
	item_fade();
}

void item_speed__evt()
{
	if (item_event() != 0)
	{
		hud_addSpeed(1);
	}
}

