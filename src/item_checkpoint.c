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
	my->event = item_speed__evt;
	var vZ = my->z;
	var vOffset = random(500);
	var vParticles = 0;
	//my->material = mtl_specBump;
	while(!player) wait(1);
	
	ANGLE vecAng;
	VECTOR vecTemp;
	while(!is(me, is_collected))
	{
		ent_animate(me, "Wave", 0.8 * total_ticks, ANM_CYCLE);
		vec_set(vecTemp, my.x);
		vec_sub(vecTemp, player.x);
		vec_to_angle(my.pan, vecTemp);
		wait(1);
	}
	item_fade();
}

void item_speed__evt()
{
	if (item_event() != 0)
	{
		hud_addTime(my->timeBonus);
	}
}

