
#include <windows.h>
#include "timer.h"

#define HUD_FONT_SIZE 100
#define HUD_MAX_ENERGY 100
#define HUD_MAX_SPEED 16
#define HUD_MAX_TIME 999
#define HUD_DEF_ENERGY 100
#define HUD_DEF_SPEED 0
#define HUD_DEF_TIME 999


void (*HUD__resizeEv)();
void hud__update();
void HUD__resize();


BMAP* left_gauge_bmap = "gauge_blue.tga";
BMAP* right_gauge_bmap = "gauge_yellow.tga";
FONT* HUD__font = "Digital-7#30";
SOUND* HUD__sndTimeout = "timeout.wav";

PANEL* hud_pan = 
{
	layer = 3;
	alpha = 90;
	flags = /*LIGHT |*/ TRANSLUCENT | CENTER_X | SHADOW;
}

PANEL* hud_left_gauge_pan = 
{
	pos_x = 0;
	pos_y = 0;
	layer = 3;
	bmap = left_gauge_bmap;
	alpha = 70;
	flags = /*LIGHT |*/ FILTER | TRANSLUCENT;
}

PANEL* hud_right_gauge_pan = 
{
	pos_x = 0;
	pos_y = 0;
	layer = 3;
	bmap = right_gauge_bmap;
	alpha = 70;
	flags = /*LIGHT |*/ FILTER | TRANSLUCENT;
}

var vHudInitialized = 0;
var vHudEnergy;
var vHudSpeed;
var vHudTime;
var vHudTimeInt;
var vHudMaxEnergy;
var vHudMaxSpeed;
var vHudMaxTime;
VECTOR vHudTimeColor;

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
		hud_reinit();
		HUD__resizeEv = on_resize;
		on_resize = HUD__resize;
		AddFontResource("media//digital-7.ttf");
		pan_setdigits(hud_pan, 0, 0, 0, "%1.0f", "*", 1, &vHudTimeInt);
		HUD__resize();
		vHudInitialized = 1;
	}
	
}

void hud_reinit()
{
	reset_timer();
	unpause_timer();
	vHudEnergy = HUD_DEF_ENERGY;
	vHudSpeed = HUD_DEF_SPEED;
	vHudTime = HUD_DEF_TIME;
	vHudMaxEnergy = HUD_MAX_ENERGY;
	vHudMaxSpeed = HUD_MAX_SPEED;
	vHudMaxTime = HUD_MAX_TIME;
	vec_set (vHudTimeColor, COLOR_WHITE);
}

void hud_close()
{
	RemoveFontResource("media//digital-7.ttf");
}

void hud_addEnergy(var value)
{
	vHudEnergy = clamp (vHudEnergy + value, 0, vHudMaxEnergy);
}

void hud_addSpeed(var value)
{
	vHudSpeed = clamp (vHudSpeed + value, 0, vHudMaxSpeed);
}

void hud_addTime(var value)
{
	var vCnt = 0;
	var vOldTime = vHudTime;
	var vHudTimeTarget = clamp (vHudTime + value, 0, vHudMaxTime);

	if (vHudTimeTarget < vOldTime)
	{
		pan_setcolor(hud_pan, 1, 1, COLOR_RED);
		wait(-0.5);		
		while (vCnt < 1)
		{
			vHudTime = (1 - vCnt) * vHudTime + vCnt * vHudTimeTarget;	
			vCnt = vCnt + 0.5 * time_step;
			wait(1);
		}
		vHudTime = vHudTimeTarget;
		wait(-1);		
		pan_setcolor(hud_pan, 1, 1, &vHudTimeColor);
	}
	else if (vHudTimeTarget > vOldTime)
	{
		pan_setcolor(hud_pan, 1, 1, COLOR_GREEN);
		wait(-0.5);		
		while (vCnt < 1)
		{
			vHudTime = (1 - vCnt) * vHudTime + vCnt * vHudTimeTarget;	
			vCnt = vCnt + 0.5 * time_step;
			wait(1);
		}
		vHudTime = vHudTimeTarget;
		//wait(-1);		//geht net, WTF!?
		pan_setcolor(hud_pan, 1, 1, &vHudTimeColor);
		return;
	}
	else
	{
		vHudTime = vHudTimeTarget;
	}
	
}


void hud__update()
{
	var width;
	var height;
	var value;

	//left gauge
	width = bmap_width(hud_left_gauge_pan->bmap);
	height = bmap_height(hud_left_gauge_pan->bmap);
	value = width * vHudEnergy / vHudMaxEnergy;
	hud_left_gauge_pan->scale_x = screen_size.x / width * 0.4;
	hud_left_gauge_pan->scale_y = hud_left_gauge_pan->scale_x * 0.6;
	hud_left_gauge_pan->size_y = height;
	hud_left_gauge_pan->size_x = clamp(value, 1, width);
	hud_left_gauge_pan->pos_x = screen_size.x * 0.01;
	hud_left_gauge_pan->pos_y = screen_size.y * 0.01;
	
	//right gauge
	width = bmap_width(hud_right_gauge_pan->bmap);
	height = bmap_height(hud_right_gauge_pan->bmap);
	value = width * vHudSpeed / vHudMaxSpeed;
	hud_right_gauge_pan->scale_x = screen_size.x / width * -0.4;
	hud_right_gauge_pan->scale_y = -hud_right_gauge_pan->scale_x * 0.6;
	hud_right_gauge_pan->size_y = height;
	hud_right_gauge_pan->size_x = clamp(value, 1, width);
	hud_right_gauge_pan->pos_x = screen_size.x * 0.59 + ((width - hud_right_gauge_pan->size_x) / width * screen_size.x * 0.4);//BÄH
	hud_right_gauge_pan->pos_y = screen_size.y * 0.01;

	//timer
	var vPassed = (timer_getMinutes() * 60 + timer_getSeconds());
	vHudMaxTime = HUD_MAX_TIME + vPassed;
	var vHudTimeLeft = clamp(vHudTime - vPassed, 0, vHudMaxTime);
	var vOldTime = vHudTimeInt;
	vHudTimeInt = integer(vHudTimeLeft);
	if (vOldTime > 10 && vHudTimeInt <= 10)
	{
		pan_setcolor(hud_pan, 1, 1, COLOR_RED);
		vec_set (&vHudTimeColor, COLOR_RED);
	}

	if (vHudTimeInt > 10 && vOldTime <= 10)
	{
		pan_setcolor(hud_pan, 1, 1, COLOR_WHITE);
		vec_set (&vHudTimeColor, COLOR_WHITE);
	}

	if (vOldTime > vHudTimeInt && vHudTimeInt <= 5)
	{
		snd_play(HUD__sndTimeout, 100, 0);
	}
	
	if (/*vOldTime > 0 &&*/ vHudTimeInt == 0)
	{
		//draw_text("timeout",screen_size.x * 0.45,screen_size.y * 0.5, COLOR_WHITE);
		press_enter_to_restart();
		pause_timer();
	}
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
	hud_pan->pos_y = 0;//screen_size.y * 0.01;
	pan_setdigits(hud_pan, 1, hud_pan->size_x * 0.5, 0, "%03.0f", HUD__font, 1, &vHudTimeInt);

	//trigger any chained resize event
	if (HUD__resizeEv != NULL)
	{
		HUD__resizeEv();
	}
}

