#include "obstacle_cloud.h"
#include "obstacle_asteroid.h"
#include "item_boost.h"
#include "item_energy.h"
#include "item_speed.h"

#define ITEMDROPPER_DROPDIST 400
#define ITEMDROPPER_ACTIVE 1

#define ITEM_SPEED 0
#define ITEM_BOOST 1
#define ITEM_ENERGY 2
#define OBSTACLE_CLOUD 3
#define OBSTACLE_ASTEROID 4
#define NUM_SPAWNABLES 5

void drop_items__new();
void drop_item__spawn(var id, VECTOR* vecPos);


typedef struct
{
	var from;
	var to;
	var weight[NUM_SPAWNABLES];
}WEIGHTING;

WEIGHTING sItemWeigths[1];

void item_weighting_startup()
{
	sItemWeigths[0].from = 0;
	sItemWeigths[0].to = 0;
	sItemWeigths[0].weight[0] = 3;
	sItemWeigths[0].weight[1] = 10;
	sItemWeigths[0].weight[2] = 1;
	sItemWeigths[0].weight[3] = 5;
	sItemWeigths[0].weight[4] = 3;	
}

void drop_items()
{
	#ifdef ITEMDROPPER_ACTIVE
	drop_items__new();
	#else
	//load from file
	#endif
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
	while (vDistance < vLength)
	{
		vec_set(&vLastPos, &vSplinePos);
		path_spline(entWalker, vSplinePos, vDistance);
		vDistance += ITEMDROPPER_DROPDIST;
		wait (1);
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
		var vNum = 0;
		var i;
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
				drop_item__spawn(i, vecTemp);
				break;
			}
		}
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

