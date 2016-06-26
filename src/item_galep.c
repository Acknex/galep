#ifndef ITEM_GALEP_C_
#define ITEM_GALEP_C_

action act_galep() {
	item_setup();
	var vZ = my->z;
	var vOffset = random(500);
	var vParticles = 0;
	while (!player) wait(1);
	set(me, LIGHT);
	
	while(me)
	{
		if (vec_dist(player.x, my.x) < 15000)
		{
			vParticles += time_step;
			if (vParticles > 10)
			{
				effect(item_particle, 10, &my->x, nullvector);
				vParticles -= 10;
			}
			my->z = vZ + 10 * sinv(total_ticks * 20 + vOffset);
			my->tilt += 2 * time_step;
			my->red = 10 + sinv(total_ticks * 20) * 50;
			//DEBUG_VAR(my->red, 60);
		}
		
		wait(1);
	}
	item_fade();
}

#endif