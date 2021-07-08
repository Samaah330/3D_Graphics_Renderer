#include "Ray.h"

Ray::Ray() {
	origin = Vector(0, 0, 0);
	direction = Vector(1, 0, 0);

}

Ray::Ray(Vector orig, Vector dir) {
	origin = orig;
	direction = dir;
}

Vector Ray::getOrigin() {
	return origin;
}

Vector Ray::getDirection() {
	return direction;
}