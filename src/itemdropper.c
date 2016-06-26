#include "obstacle_cloud.h"
#include "obstacle_asteroid.h"
#include "item_boost.h"
#include "item_energy.h"
#include "item_speed.h"
#include "item_checkpoint.h"
#include "player.h"

#define ITEMDROPPER_DROPDIST_MIN 2500
#define ITEMDROPPER_DROPDIST_MAX 3500
#define ITEMDROPPER_DROPDIST_LIMIT 450000
//#define ITEMDROPPER_ACTIVE 1

#define ITEM_SPEED 0
#define ITEM_BOOST 1
#define ITEM_ENERGY 2
#define ITEM_TIME 3
#define OBSTACLE_CLOUD 4
#define OBSTACLE_ASTEROID 5
#define NUM_SPAWNABLES 6

void drop_items__new();
void drop_items__file();
void drop_item__spawn(var id, VECTOR* vecPos);


#define NUM_ITEM_WEIGHTS 22
typedef struct
{
	var from;
	var to;
	var weight[NUM_SPAWNABLES];
}WEIGHTING;

WEIGHTING sItemWeigths[NUM_ITEM_WEIGHTS];

void item_weighting_startup()
{
	var i = 0;
	sItemWeigths[i].from = 0;
	sItemWeigths[i].to = 0;
	sItemWeigths[i].weight[ITEM_SPEED] = 3;
	sItemWeigths[i].weight[ITEM_BOOST] = 2;
	sItemWeigths[i].weight[ITEM_ENERGY] = 3;
	sItemWeigths[i].weight[ITEM_TIME] = 3;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 4;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 4;	
	
	sItemWeigths[i].from = 5000;
	sItemWeigths[i].to = 40000;
	sItemWeigths[i].weight[ITEM_SPEED] = 3;
	sItemWeigths[i].weight[ITEM_BOOST] = 70;
	sItemWeigths[i].weight[ITEM_ENERGY] = 3;
	sItemWeigths[i].weight[ITEM_TIME] = 3;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 4;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 4;	
	
	sItemWeigths[i].from = 50000;
	sItemWeigths[i].to = 70000;
	sItemWeigths[i].weight[ITEM_SPEED] = 3;
	sItemWeigths[i].weight[ITEM_BOOST] = 2;
	sItemWeigths[i].weight[ITEM_ENERGY] = 3;
	sItemWeigths[i].weight[ITEM_TIME] = 70;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 1;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 1;	
	
	sItemWeigths[i].from = 84000;
	sItemWeigths[i].to = 92000;
	sItemWeigths[i].weight[ITEM_SPEED] = 3;
	sItemWeigths[i].weight[ITEM_BOOST] = 1;
	sItemWeigths[i].weight[ITEM_ENERGY] = 3;
	sItemWeigths[i].weight[ITEM_TIME] = 3;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 30;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 1;	
	
	sItemWeigths[i].from = 108000;
	sItemWeigths[i].to = 122000;
	sItemWeigths[i].weight[ITEM_SPEED] = 3;
	sItemWeigths[i].weight[ITEM_BOOST] = 1;
	sItemWeigths[i].weight[ITEM_ENERGY] = 3;
	sItemWeigths[i].weight[ITEM_TIME] = 3;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 1;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 30;	
	
	sItemWeigths[i].from = 130000;
	sItemWeigths[i].to = 140000;
	sItemWeigths[i].weight[ITEM_SPEED] = 3;
	sItemWeigths[i].weight[ITEM_BOOST] = 2;
	sItemWeigths[i].weight[ITEM_ENERGY] = 30;
	sItemWeigths[i].weight[ITEM_TIME] = 3;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 1;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 1;	
	
	sItemWeigths[i].from = 151000;
	sItemWeigths[i].to = 161000;
	sItemWeigths[i].weight[ITEM_SPEED] = 3;
	sItemWeigths[i].weight[ITEM_BOOST] = 70;
	sItemWeigths[i].weight[ITEM_ENERGY] = 3;
	sItemWeigths[i].weight[ITEM_TIME] = 3;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 4;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 4;	
	
	sItemWeigths[i].from = 161000;
	sItemWeigths[i].to = 172000;
	sItemWeigths[i].weight[ITEM_SPEED] = 10;
	sItemWeigths[i].weight[ITEM_BOOST] = 1;
	sItemWeigths[i].weight[ITEM_ENERGY] = 30;
	sItemWeigths[i].weight[ITEM_TIME] = 3;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 1;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 1;	
	
	sItemWeigths[i].from = 172000;
	sItemWeigths[i].to = 190000;
	sItemWeigths[i].weight[ITEM_SPEED] = 3;
	sItemWeigths[i].weight[ITEM_BOOST] = 2;
	sItemWeigths[i].weight[ITEM_ENERGY] = 3;
	sItemWeigths[i].weight[ITEM_TIME] = 3;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 1;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 70;	
	
	sItemWeigths[i].from = 190000;
	sItemWeigths[i].to = 200000;
	sItemWeigths[i].weight[ITEM_SPEED] = 30;
	sItemWeigths[i].weight[ITEM_BOOST] = 1;
	sItemWeigths[i].weight[ITEM_ENERGY] = 30;
	sItemWeigths[i].weight[ITEM_TIME] = 30;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 1;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 1;	
	
	sItemWeigths[i].from = 200000;
	sItemWeigths[i].to = 220000;
	sItemWeigths[i].weight[ITEM_SPEED] = 3;
	sItemWeigths[i].weight[ITEM_BOOST] = 70;
	sItemWeigths[i].weight[ITEM_ENERGY] = 3;
	sItemWeigths[i].weight[ITEM_TIME] = 3;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 1;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 15;	
	
	sItemWeigths[i].from = 220000;
	sItemWeigths[i].to = 235000;
	sItemWeigths[i].weight[ITEM_SPEED] = 3;
	sItemWeigths[i].weight[ITEM_BOOST] = 1;
	sItemWeigths[i].weight[ITEM_ENERGY] = 35;
	sItemWeigths[i].weight[ITEM_TIME] = 35;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 1;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 1;	
	
	sItemWeigths[i].from = 235000;
	sItemWeigths[i].to = 260000;
	sItemWeigths[i].weight[ITEM_SPEED] = 3;
	sItemWeigths[i].weight[ITEM_BOOST] = 1;
	sItemWeigths[i].weight[ITEM_ENERGY] = 3;
	sItemWeigths[i].weight[ITEM_TIME] = 3;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 70;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 1;	
	
	sItemWeigths[i].from = 266000;
	sItemWeigths[i].to = 272000;
	sItemWeigths[i].weight[ITEM_SPEED] = 3;
	sItemWeigths[i].weight[ITEM_BOOST] = 1;
	sItemWeigths[i].weight[ITEM_ENERGY] = 3;
	sItemWeigths[i].weight[ITEM_TIME] = 30;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 1;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 1;	
	
	sItemWeigths[i].from = 272000;
	sItemWeigths[i].to = 280000;
	sItemWeigths[i].weight[ITEM_SPEED] = 3;
	sItemWeigths[i].weight[ITEM_BOOST] = 1;
	sItemWeigths[i].weight[ITEM_ENERGY] = 30;
	sItemWeigths[i].weight[ITEM_TIME] = 3;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 1;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 1;	
	
	sItemWeigths[i].from = 290000;
	sItemWeigths[i].to = 305000;
	sItemWeigths[i].weight[ITEM_SPEED] = 3;
	sItemWeigths[i].weight[ITEM_BOOST] = 70;
	sItemWeigths[i].weight[ITEM_ENERGY] = 3;
	sItemWeigths[i].weight[ITEM_TIME] = 3;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 1;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 1;	
	
	sItemWeigths[i].from = 305000;
	sItemWeigths[i].to = 350000;
	sItemWeigths[i].weight[ITEM_SPEED] = 3;
	sItemWeigths[i].weight[ITEM_BOOST] = 1;
	sItemWeigths[i].weight[ITEM_ENERGY] = 50;
	sItemWeigths[i].weight[ITEM_TIME] = 50;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 1;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 1;	
	
	sItemWeigths[i].from = 323000;
	sItemWeigths[i].to = 350000;
	sItemWeigths[i].weight[ITEM_SPEED] = 3;
	sItemWeigths[i].weight[ITEM_BOOST] = 70;
	sItemWeigths[i].weight[ITEM_ENERGY] = 3;
	sItemWeigths[i].weight[ITEM_TIME] = 3;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 70;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 1;	
	
	sItemWeigths[i].from = 360000;
	sItemWeigths[i].to = 385000;
	sItemWeigths[i].weight[ITEM_SPEED] = 3;
	sItemWeigths[i].weight[ITEM_BOOST] = 1;
	sItemWeigths[i].weight[ITEM_ENERGY] = 3;
	sItemWeigths[i].weight[ITEM_TIME] = 3;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 1;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 70;	
	
	sItemWeigths[i].from = 400000;
	sItemWeigths[i].to = 420000;
	sItemWeigths[i].weight[ITEM_SPEED] = 3;
	sItemWeigths[i].weight[ITEM_BOOST] = 1;
	sItemWeigths[i].weight[ITEM_ENERGY] = 70;
	sItemWeigths[i].weight[ITEM_TIME] = 30;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 1;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 1;	
	
	sItemWeigths[i].from = 420001;
	sItemWeigths[i].to = 431000;
	sItemWeigths[i].weight[ITEM_SPEED] = 30;
	sItemWeigths[i].weight[ITEM_BOOST] = 1;
	sItemWeigths[i].weight[ITEM_ENERGY] = 3;
	sItemWeigths[i].weight[ITEM_TIME] = 3;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 1;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 1;	
	
	sItemWeigths[i].from = 432000;
	sItemWeigths[i].to = 450000;
	sItemWeigths[i].weight[ITEM_SPEED] = 70;
	sItemWeigths[i].weight[ITEM_BOOST] = 1;
	sItemWeigths[i].weight[ITEM_ENERGY] = 3;
	sItemWeigths[i].weight[ITEM_TIME] = 3;
	sItemWeigths[i].weight[OBSTACLE_CLOUD] = 1;
	sItemWeigths[i++].weight[OBSTACLE_ASTEROID] = 1;	
	
}

void drop_items()
{
	#ifdef ITEMDROPPER_ACTIVE
	drop_items__new();
	#else
	drop_items__file();
	#endif
}

void drop_items__file()
{
	var vHandle = file_open_read("level.dat");
	VECTOR vecTemp;
	var id;
	if (vHandle)
	{
		var ok;
		do
		{
			id = file_var_read(vHandle);
			vecTemp.x = file_var_read(vHandle);	
			vecTemp.y = file_var_read(vHandle);	
			vecTemp.z = file_var_read(vHandle);	
			if (id == 0 && vecTemp.x == 0 && vecTemp.y == 0 && vecTemp.z == 0)
			{
				ok = 0;
			}
			else
			{
				ok = 1;
				drop_item__spawn(id, vecTemp);	
			}
		} while (ok == 1);
		file_close(vHandle);
	}
	else
	{
		error("level data not found! generating...");
		drop_items__new();
	}
	
}


void drop_items__new()
{
	ENTITY* entWalker;
	VECTOR vSplinePos;
	VECTOR vLastPos;
	ANGLE vAngle;
	var vDistance = 0;
	
	entWalker = ent_create(NULL, vector(1000,0,0), NULL);
	path_set(entWalker, "path_000");
	var vLength = minv(path_length(entWalker), ITEMDROPPER_DROPDIST_LIMIT);
	//printf("%f %f", (double)vDistance, (double)vLength);
	var vHandle = file_open_write("level.dat");
	while (vDistance < vLength)
	{
		vec_set(&vLastPos, &vSplinePos);
		path_spline(entWalker, vSplinePos, vDistance);
		vDistance += ITEMDROPPER_DROPDIST_MIN + random(ITEMDROPPER_DROPDIST_MAX - ITEMDROPPER_DROPDIST_MIN);
		VECTOR vecTemp;
		vec_set(&vecTemp, &vSplinePos);
		vec_sub(&vecTemp, &vLastPos);
		vec_to_angle(vAngle, vecTemp);
		vecTemp.x = 0;
		vecTemp.y = random(900) - 450;
		vecTemp.z = random(700) - 350;
		vec_rotate(vecTemp, vAngle);
		vec_add(vecTemp, vSplinePos);
		
		var vRange = 0;
		var i;

		for (i = 0; i < NUM_ITEM_WEIGHTS; i++)
		{
			if (vDistance > sItemWeigths[i].from && vDistance < sItemWeigths[i].to)
			{
				vRange = i;
				break;
			}
		}
		
		var vNum = 0;
		for (i = 0; i < NUM_SPAWNABLES; i++)
		{
			vNum += sItemWeigths[vRange].weight[i];
		}
		
		var id = integer(random (vNum));
		vNum = 0;
		for (i = 0; i < NUM_SPAWNABLES; i++)
		{
			vNum += sItemWeigths[vRange].weight[i];
			if (id < vNum)
			{
				file_var_write(vHandle, i);
				file_var_write(vHandle, vecTemp.x);
				file_var_write(vHandle, vecTemp.y);
				file_var_write(vHandle, vecTemp.z);
				drop_item__spawn(i, vecTemp);
				break;
			}
		}
	}
	file_close(vHandle);	
	while(1)
	{
		DEBUG_VAR(splineDistance, 100);
		wait(1);
	}
}

void drop_item__spawn(var id, VECTOR* vecPos)
{
	switch (id)
	{
		case ITEM_SPEED:
		{
			ent_create("a9cube.mdl", vecPos, item_speed);
			break;
		}

		case ITEM_BOOST:
		{
			ent_create("jetpack_lotter.mdl", vecPos, item_boost);
			break;
		}

		case ITEM_ENERGY:
		{
			ent_create("battery.mdl", vecPos, item_energy);
			break;
		}

		case ITEM_TIME:
		{
			ent_create("flash.mdl", vecPos, item_checkpoint);
			break;
		}

		case OBSTACLE_CLOUD:
		{
			ent_create("a9cube.mdl", vecPos, obstacle_cloud);
			break;
		}

		case OBSTACLE_ASTEROID:
		{
			ent_create("asteroid0_obstacle.mdl", vecPos, obstacle_asteroid);
			break;
		}

		default:
		break;
	}
}

