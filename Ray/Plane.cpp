#include "Plane.h"

Plane::Plane() {
	normal_vector = Vector(1, 0, 0);
	plane_distance = 0;
	plane_color = Color(0.5, 0.5, 0.5, 0);
}

Plane::Plane(Vector normal, double distance, Color color) {
	normal_vector = normal;
	plane_distance = distance;
	plane_color = color;
}

Vector Plane::getNormalVector() {
	return normal_vector;
}

double Plane::getPlaneDistance() {
	return plane_distance;
}

Color Plane::getColor() {
	return plane_color;
}

Vector Plane::getNormalAt(Vector point) {
	return normal_vector;
}

double Plane::findIntersection(Ray ray) {
	Vector ray_direction = ray.getDirection();

	double a = ray_direction.dotProduct(normal_vector);

	if (a == 0) {
		// ray is parallel to the plane
		return -1;
	} else {
		double b = normal_vector.dotProduct(ray.getOrigin().vectorAdd
		(normal_vector.vectorMultiply(plane_distance).negate()));

		return -1 * b / a;
	}
}
