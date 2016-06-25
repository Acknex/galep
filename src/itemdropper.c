#include "obstacle_cloud.h"
#include "obstacle_asteroid.h"
#include "item_boost.h"
#include "item_energy.h"
#include "item_speed.h"

#define ITEMDROPPER_DROPDIST 1400
//#define ITEMDROPPER_ACTIVE 1

#define ITEM_SPEED 0
#define ITEM_BOOST 1
#define ITEM_ENERGY 2
#define OBSTACLE_CLOUD 3
#define OBSTACLE_ASTEROID 4
#define NUM_SPAWNABLES 5

void drop_items__new();
void drop_items__file();
void drop_item__spawn(var id, VECTOR* vecPos);


#define NUM_ITEM_WEIGHTS 1
typedef struct
{
	var from;
	var to;
	var weight[NUM_SPAWNABLES];
}WEIGHTING;

WEIGHTING sItemWeigths[NUM_ITEM_WEIGHTS];

void item_weighting_startup()
{
	sItemWeigths[0].from = 0;
	sItemWeigths[0].to = 0;
	sItemWeigths[0].weight[ITEM_SPEED] = 3;
	sItemWeigths[0].weight[ITEM_BOOST] = 10;
	sItemWeigths[0].weight[ITEM_ENERGY] = 1;
	sItemWeigths[0].weight[OBSTACLE_CLOUD] = 5;
	sItemWeigths[0].weight[OBSTACLE_ASTEROID] = 3;	
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
	var vLength = path_length(entWalker);
	//printf("%f %f", (double)vDistance, (double)vLength);
	var vHandle = file_open_write("level.dat");
	while (vDistance < vLength)
	{
		vec_set(&vLastPos, &vSplinePos);
		path_spline(entWalker, vSplinePos, vDistance);
		vDistance += ITEMDROPPER_DROPDIST;
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

