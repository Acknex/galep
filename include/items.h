#ifndef ITEMS_H
#define ITEMS_H
 
#define is_collected  FLAG4

void item_setup();
var item_evt();
void item_fade();
void item_particle (PARTICLE *p);

#include "items.c"

#endif