#pragma once

#ifndef _RAY_H
#define _RAY_H

#include "Vector.h"

class Ray {

	Vector origin;
	Vector direction;

public:
	Ray();
	Ray(Vector orig, Vector dest);

	Vector getOrigin();
	Vector getDirection();
};

#endif
