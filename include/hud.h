#ifndef HUD_H
#define HUD_H

void hud_show();
void hud_hide();
void hud_init();
void hud_register(var* energy, var* speed, var* time);

#include "hud.c"

#endif