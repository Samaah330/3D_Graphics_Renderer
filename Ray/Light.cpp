#include "Light.h"

Light::Light() {
	position = Vector(0, 0, 0);
	color = Color(1, 1, 1, 0);
}

Light::Light(Vector pos, Color col) {
	position = pos;
	color = col;
}

 Vector Light::getLightPosition() {
	return position;
}

Color Light::getColor() {
	return color;
}




