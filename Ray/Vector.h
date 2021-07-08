#pragma once

#ifndef _VECTOR_H
#define _VECTOR_H

#include "math.h"

class Vector {
	double x; 
	double y;
	double z;

	public:
		Vector();
		Vector(double x_value, double y_value, double z_value);

		double getVectorX();
		double getVectorY();
		double getVectorZ();
		Vector negate();
		Vector crossProduct(Vector v);
		double dotProduct(Vector v);
		double magnitude();
		Vector normalize();
		Vector vectorAdd(Vector v);
		Vector vectorMultiply(double scalar);
};

#endif
