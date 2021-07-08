#include "Sphere.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

Sphere::Sphere() {
	sphere_center = Vector(0, 0, 0);
	sphere_radius = 1.0;
	sphere_color = Color(0.5, 0.5, 0.5, 0);
}

Sphere::Sphere(Vector center, double radius, Color color) {
	sphere_center = center;
	sphere_radius = radius;
	sphere_color = color;
}

Vector Sphere::getSphereCenter() {
	return sphere_center;
}

double Sphere::getSphereRadius() {
	return sphere_radius;
}

Color Sphere::getColor() {
	return sphere_color;
}

Vector Sphere::getNormalAt(Vector point) {
	Vector normal_vector = point.vectorAdd(sphere_center.negate()).normalize();
	return normal_vector;
}

double Sphere::findIntersection(Ray ray) {
	Vector ray_origin = ray.getOrigin();
	double ray_origin_x = ray_origin.getVectorX();
	double ray_origin_y = ray_origin.getVectorY();
	double ray_origin_z = ray_origin.getVectorZ();

	Vector ray_direction = ray.getDirection();
	double ray_direction_x = ray_direction.getVectorX();
	double ray_direction_y = ray_direction.getVectorY();
	double ray_direction_z = ray_direction.getVectorZ();

	Vector center = sphere_center;
	double center_x = center.getVectorX();
	double center_y = center.getVectorY();
	double center_z = center.getVectorZ();

	double a = 1; // normalized
	double b = (2 * (ray_origin_x - center_x) * ray_direction_x)
		+ (2 * (ray_origin_y - center_y) * ray_direction_y)
		+ (2 * (ray_origin_z - center_z) * ray_direction_z);
	double c = pow(ray_origin_x - center_x, 2) + pow(ray_origin_y - center_y, 2)
		+ pow(ray_origin_z - center_z, 2) - (sphere_radius * sphere_radius);

	double discriminant = (b * b) - (4 * c);

	//double discriminant = pow(b, 2) - 4 * a * c;

	if (discriminant > 0) {
		// the ray intersects the sphere

		// the first root
		double root_1 = ((-1 * b - sqrt(discriminant)) / 2) - 0.0000001;

		if (root_1 > 0) {
			// the first root is the smallest positive root
			return root_1;
		} else {
			// the second root is the smallest positive root
			double root_2 = ((sqrt(discriminant) - b) / 2) - 0.0000001;
			return root_2;
		}
	} else {
		// the ray missed the sphere
		return -1;
	}
}
