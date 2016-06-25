#ifndef CAMERA_C_
#define CAMERA_C_

VECTOR camRotateTemp;
ANGLE angTempRotate;

void camera_move() {
	
	if (player == NULL) return;
	
	// Camera follow player
	//vec_set(camera.x, vector(player.x - 1000, player.y, player.z));
	
	// Camera rotates towards player
	camera.x = player.x - 1000 * cos(player.pan);
	camera.y = player.y - 1000 * sin(player.pan);
		
		
	vec_set(camRotateTemp, player.x);
	vec_sub(camRotateTemp, camera.x);

	VECTOR temp;
	vec_to_angle(temp, camRotateTemp.x);
	camera.pan = temp.x;
	camera.tilt = temp.y;
	
	//vec_to_angle(angTempRotate, camRotateTemp.x);
	
	//vec_lerp(camera.pan, camera.pan, angTempRotate.pan, 0.01);
}

#endif