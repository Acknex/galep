#include "items.h"
#include "hud.h"

#define timeBonus skill1
void item_checkpoint__evt();

//uses timeBonus
action item_checkpoint()
{
	if (my->timeBonus == 0)
	{
		my->timeBonus = 30;
	}
	item_setup();	
	my->event = item_checkpoint__evt;
	var vZ = my->z;
	var vOffset = random(500);
	var vParticles = 0;
	//my->material = mtl_specBump;
	while(!player) wait(1);
	
	while(!is(me, is_collected))
	{
		/*ent_animate(me, "Wave", 0.8 * total_ticks, ANM_CYCLE);
		vec_set(vecTemp, my.x);
		vec_sub(vecTemp, player.x);
		vec_to_angle(my.pan, vecTemp);*/
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

void item_checkpoint__evt()
{
	if (item_evt() != 0)
	{
		hud_addTime(my->timeBonus);
	}
}

