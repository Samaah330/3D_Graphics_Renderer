#pragma once
#ifndef _SPHERE_H
#define _SPHERE_H

#include "Color.h"
#include "Vector.h"
#include "Object.h"
#include "math.h"

class Sphere : public Object {
	Vector sphere_center;
	double sphere_radius;
	Color sphere_color;

public:
	Sphere();
	Sphere(Vector center, double radius, Color color);

	Vector getSphereCenter();
	double getSphereRadius();
	virtual Color getColor();

	/**
	* normal always points away from the center of a sphere
	*/
	virtual Vector getNormalAt(Vector point);

	/**
	* Returns a scalar value which is the distance from the origin of the array
	* to the point of intersection
	*/
	virtual double findIntersection(Ray ray);
};

#endif

