/*
 *******************************************************************************
 * timer.c
 * Creation date: 19.07.2014
 * Author:        Firoball
 *
 *******************************************************************************
 * $Date: 2014-07-19 17:49:17 +0200 (Sa, 19 Jul 2014) $
 * $Revision: 177 $
 * $Author: Firoball $
 *
 *******************************************************************************
 * Description
 *
 * definition script for head up display
 *
 * Comments
 * 
 * for short descriptions see comments in timer.h
 *
 *******************************************************************************
 */

var vTimeTicks;
var vTimerPaused;

void timer_startup()
{
	reset_timer();
	while(1)
	{
		if (vTimerPaused == 0)
		{
			vTimeTicks += time_step;
		}
		wait(1);
	}
}

void reset_timer()
{
	vTimeTicks = 0;
}

void pause_timer()
{
	vTimerPaused = 1;	
}

void unpause_timer()
{
	vTimerPaused = 0;	
}

var timer_getHundreds()
{
	return integer(((vTimeTicks / 16) * 100) % 100);
}

var timer_getSeconds()
{
	return integer((vTimeTicks / 16) % 60);
}

var timer_getMinutes()
{
	return integer((vTimeTicks / (60 * 16)) % 60);
}