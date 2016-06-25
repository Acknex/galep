#ifndef __INC_MENU_H
#define __INC_MENU_H

BMAP* menu_bmap_fade = "textures/black_1px.tga";
PANEL* menu_pan_fade =
{
	pos_x = 0; pos_y = 0;
	window(0, 0, 1, 1, menu_bmap_fade, 0, 0);
	alpha = 0;
	layer = 999;
	flags = TRANSLUCENT | SHOW;
}
TEXT* menu_txt =	
{
  layer = 1;
  pos_x = 10;
  pos_y = 10;
  font = "Arial#20bi";
  string ("Team AckCon presents");
  flags = CENTER_X | CENTER_Y  | TRANSLUCENT | SHOW;
  alpha = 0;
}

var menu_hnd_music;
var menu_is_closed;
void showMenu();
void closeMenu();

#include "menu.c";

#endif