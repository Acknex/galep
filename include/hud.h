#ifndef HUD_H
#define HUD_H

void hud_show();
void hud_hide();
void hud_init();
void hud_reinit();
void hud_close();
void hud_addEnergy(var value);
void hud_addSpeed(var value);
void hud_addTime(var value);

#include "hud.c"

#endif