#pragma once
#ifndef _OBJECT_H
#define _OBJECT_H

#include "Ray.h"
#include "Vector.h"
#include "Color.h"

class Object {

public:
	Object();

	virtual Color getColor();
	virtual double findIntersection(Ray ray);
	virtual Vector getNormalAt(Vector point);
};

#endif

