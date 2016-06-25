
#include <windows.h>

#define HUD_FONT_SIZE 100

void (*HUD__resizeEv)();
void hud__update();
void HUD__resize();


BMAP* left_gauge_bmap = "gauge_blue.tga";
BMAP* right_gauge_bmap = "gauge_yellow.tga";
FONT* HUD__font = "Digital-7#30";

PANEL* hud_pan = 
{
	pos_x = 0;
	pos_y = 0;
	size_x = 1024;
	size_y = 256; 
	layer = 3;
//	alpha = 70;
//	flags = LIGHT | TRANSLUCENT;
}

PANEL* hud_left_gauge_pan = 
{
	pos_x = 0;
	pos_y = 0;
	layer = 3;
	bmap = left_gauge_bmap;
	alpha = 30;
	flags = LIGHT | FILTER | TRANSLUCENT;
}

PANEL* hud_right_gauge_pan = 
{
	pos_x = 0;
	pos_y = 0;
	layer = 3;
	bmap = right_gauge_bmap;
	alpha = 30;
	flags = LIGHT | FILTER | TRANSLUCENT;
}

var vHudInitialized = 0;
var vHudEnergy = 0;
var vHudMaxEnergy = 100;
var vHudSpeed = 0;
var vHudMaxSpeed = 50;
var vHudTime = 123;

void hud_show()
{
	if (vHudInitialized)
	{
		set(hud_left_gauge_pan, SHOW);
		set(hud_right_gauge_pan, SHOW);
		set(hud_pan, SHOW);
		while(is(hud_left_gauge_pan, SHOW) || is(hud_left_gauge_pan, SHOW) || is(hud_pan, SHOW))
		{
			hud__update();
			wait(1);
		}
	}
}

void hud_hide()
{
	if (vHudInitialized)
	{	
		reset(hud_left_gauge_pan, SHOW);
		reset(hud_right_gauge_pan, SHOW);
		reset(hud_pan, SHOW);
	}
}

void hud_init()
{
	if (!vHudInitialized)
	{
		HUD__resizeEv = on_resize;
		on_resize = HUD__resize;
		AddFontResource("media//digital-7.ttf");
		pan_setdigits(hud_pan, 0, 0, 0, "%1.0f", "*", 1, &vHudTime);
		HUD__resize();
		vHudInitialized = 1;
	}
	
	while(1)
	{
		//temp
		vHudEnergy = cycle(vHudEnergy + 5* time_step,0,vHudMaxEnergy);
		vHudSpeed = cycle(vHudSpeed + 3* time_step,0,vHudMaxSpeed);
		wait(1);
	}

}

void hud_close()
{
	RemoveFontResource("media//digital-7.ttf");
}

void hud__update()
{
	var width;
	var height;
	var value;

	width = bmap_width(hud_left_gauge_pan->bmap);
	height = bmap_height(hud_left_gauge_pan->bmap);
	value = width * vHudEnergy / vHudMaxEnergy;
	hud_left_gauge_pan->scale_x = screen_size.x / width * 0.4;
	hud_left_gauge_pan->scale_y = hud_left_gauge_pan->scale_x;
	hud_left_gauge_pan->size_y = height;
	hud_left_gauge_pan->size_x = clamp(value, 0, width);
	
	width = bmap_width(hud_right_gauge_pan->bmap);
	height = bmap_height(hud_right_gauge_pan->bmap);
	value = width * vHudSpeed / vHudMaxSpeed;
	hud_right_gauge_pan->scale_x = screen_size.x / width * -0.4;
	hud_right_gauge_pan->scale_y = -hud_right_gauge_pan->scale_x;
	hud_right_gauge_pan->size_y = height;
	hud_right_gauge_pan->size_x = clamp(value, 0, width);
	hud_right_gauge_pan->pos_x = screen_size.x * 0.6 + ((width - hud_right_gauge_pan->size_x) / width * screen_size.x * 0.4);//BÄH
	
}

void HUD__resize()
{
	var scale = screen_size.y / 1200;
	STRING* strTemp = "#64";	
	str_printf(strTemp, "Digital-7#%i", (int)(HUD_FONT_SIZE * scale));
	ptr_remove(HUD__font);
	HUD__font = font_create(strTemp);

	draw_textmode("Digital-7", 0, 70, 90);
	hud_pan->size_x = screen_size.x * 0.1;
	hud_pan->size_y = screen_size.y * 0.1;
	hud_pan->pos_x = screen_size.x * 0.45;
	hud_pan->pos_y = screen_size.y * 0.01;
	pan_setdigits(hud_pan, 1, 0, 0, "%1.0f", HUD__font, 1, &vHudTime);

	//trigger any chained resize event
	if (HUD__resizeEv != NULL)
	{
		HUD__resizeEv();
	}
}

