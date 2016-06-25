void hud__update();


BMAP* left_gauge_bmap = "gauge_blue.tga";
BMAP* right_gauge_bmap = "gauge_yellow.tga";
PANEL* hud_pan = 
{
	pos_x = 0;
	pos_y = 0;
	size_x = 1024;
	size_y = 256; 
	layer = 3;
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
var vHudTime;

void hud_show()
{
	if (vHudInitialized)
	{
		set(hud_left_gauge_pan, SHOW);
		set(hud_right_gauge_pan, SHOW);
		while(is(hud_left_gauge_pan, SHOW) || is(hud_left_gauge_pan, SHOW))
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
	}
}

void hud_init()
{
	if (!vHudInitialized)
	{
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