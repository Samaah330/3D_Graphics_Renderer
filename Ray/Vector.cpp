#include "Vector.h"


Vector::Vector() {
	x = 0;
	y = 0;
	z = 0;
}

Vector::Vector(double x_value, double y_value, double z_value) {
	x = x_value;
	y = y_value;
	z = z_value;
}

double Vector::getVectorX() {
	return x;
}

double Vector::getVectorY() {
	return y;
}

double Vector::getVectorZ() {
	return z;
}

double Vector::magnitude() {
	return sqrt((x * x ) + (y * y) + (z * z));
}

Vector Vector::Vector::normalize() {

	return Vector(x / magnitude(), y / magnitude(), z / magnitude());
}

Vector Vector::negate() {
	return Vector(-x, -y, -z);
}

double Vector::dotProduct(Vector v) {
	return (x * v.getVectorX() + y * v.getVectorY() + z * v.getVectorZ());
}

Vector Vector::crossProduct(Vector v) {
	return Vector (y * v.getVectorZ() - z * v.getVectorY(),
				   z * v.getVectorX() - x * v.getVectorZ(),
				   x * v.getVectorY() - y * v.getVectorX());
}

Vector Vector::vectorAdd(Vector v) {
	return Vector(x + v.getVectorX(), y + v.getVectorY(), z + v.getVectorZ());
}

Vector Vector::vectorMultiply(double scalar) {
	return Vector(x * scalar, y * scalar, z * scalar);
}



