#pragma once
#define _PLANE_H

#include "math.h"
#include "Object.h"
#include "Vector.h"
#include "Color.h"

class Plane : public Object {
	Vector normal_vector;
	double plane_distance;
	Color plane_color;

public:

	Plane();
	Plane(Vector normal, double distance, Color color);
	Vector getNormalVector();
	double getPlaneDistance();
	virtual Color getColor();
	virtual Vector getNormalAt(Vector point);
	virtual double findIntersection(Ray ray);
};


