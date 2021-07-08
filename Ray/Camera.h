#pragma once

#ifndef _CAMERA_H
#define _CAMERA_H

#include "Vector.h"
class Camera {
	
	Vector camera_position;
	Vector camera_direction;
	Vector camera_right;
	Vector camera_down;

	public:
		Camera();
		Camera(Vector position, Vector direction, Vector right, Vector down);

		Vector getCameraPosition();
		Vector getCameraDirection();
		Vector getCameraRight();
		Vector getCameraDown(); 

};

#endif