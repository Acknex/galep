#ifndef OBSTACLE_H
#define OBSTACLE_H
 
#define is_collided  FLAG4

void obstacle_setup();
var obstacle_event();
void obstacle_particle (PARTICLE *p);

#include "obstacle.c"

#endif