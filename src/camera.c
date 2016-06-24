#ifndef CAMERA_C_
#define CAMERA_C_

VECTOR camRotateTemp;
ANGLE angTempRotate;

void camera_move() {
	
	if (player == NULL) return;
	vec_set(camRotateTemp, player.x);
	vec_sub(camRotateTemp, camera.x);
	vec_to_angle(angTempRotate, camRotateTemp.x);
	
	vec_lerp(camera.pan, camera.pan, angTempRotate.pan, 0.01);
}

#endif