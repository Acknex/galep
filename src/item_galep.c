#ifndef ITEM_GALEP_C_
#define ITEM_GALEP_C_

//all dirty. I don't care.


#include "hud.h"

SOUND* sndVictory = "victory.ogg";
BMAP* bmapBlack = "black128.tga";
PANEL* panFade = 
{
	bmap = bmapBlack;
	flags = TRANSLUCENT;
	alpha = 0;
}

void galep_fade()
{
	set(panFade, SHOW);
	var vol = 80;
	while (panFade->alpha < 100)
	{
		panFade->scale_x = 1.1 * (screen_size.x / bmap_width(panFade->bmap));
		panFade->scale_y = 1.1 * (screen_size.y / bmap_height(panFade->bmap));
		wait(1);
		panFade->alpha += time_step;
		vol = maxv(vol-time_step, 0);
		//master_vol = maxv(master_vol-time_step,0);
		media_tune(hndMusicInGame, 0.8*vol, 0, 0);
	}
	panFade->alpha = 100;
	sys_exit("");
}

void galep_found()
{
	snd_play(sndVictory, 100,0);
	hud_hide();
	player.event = NULL;
	while(splineDistance < 530000)
	{
		wait(1);
	}
	galep_fade();
}

action act_galep() {
	item_setup();
	var vZ = my->z;
	var vOffset = random(500);
	var vParticles = 0;
	while (!player) wait(1);
	set(me, LIGHT);
	
	while(me)
	{
		//DEBUG_VAR(vec_dist(player.x, my.x), 200);
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
		
		if (vec_dist(player.x, my.x) < 4000 && !is(my, FLAG6))
		{
			set(my, FLAG6);
			galep_found();
		}
		wait(1);
	}
	item_fade();
}

#endif