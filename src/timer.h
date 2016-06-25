/*
 *******************************************************************************
 * timer.h
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

#ifndef TIMER_H
#define TIMER_H

void reset_timer();
void pause_timer();
void unpause_timer();
var timer_getHundreds();
var timer_getSeconds();
var timer_getMinutes();

#include "timer.c"

#endif