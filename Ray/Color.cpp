#include "Color.h"
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
Color::Color() {
	red = 0.5;
	green = 0.5; 
	blue = 0.5; 
}

Color::Color(double red_value, double green_value, double blue_value, double special_value) {
	red = red_value;
	green = green_value;
	blue = blue_value;
	special = special_value;
}

double Color::getColorRed() {
	return red;
}

double Color::getColorGreen() {
	return green;
}

double Color::getColorBlue() {
	return blue;
}

double Color::getColorSpecial() {
	return special;
}

void Color::setColorRed(double r) {
	red = r;
}

void Color::setColorGreen(double g) {
	green = g;
}

void Color::setColorBlue(double b) {
	blue = b;
}

void Color::setColorSpecial(double s) {
	special = s;
}

double Color::brightness() {
	return (red + green + blue) / 3;
}

Color Color::colorScalar(double scalar) {
	return Color(red * scalar, green * scalar, blue * scalar, special);
}

Color Color::colorAdd(Color color) {
	return Color(red + color.getColorRed(), green + color.getColorGreen(), blue + color.getColorBlue(), special);
}

Color Color::colorMultiply(Color color) {
	return Color(red * color.getColorRed(), green * color.getColorGreen(), blue * color.getColorBlue(), special);
}

Color Color::colorAverage(Color color) {
	return Color((red + color.getColorRed()) / 2, (green + color.getColorGreen()) / 2, (blue + color.getColorBlue()) / 2, special);
}

Color Color::clip() {
	double allLight = red + green + blue;
	double excessLight = allLight - 3;

	if (excessLight > 0) {
		red = red + excessLight * (red / allLight);
		green = green + excessLight * (green / allLight);
		blue = blue + excessLight * (blue / allLight);
	}

	if (red > 1) {
		red = 1;
	}

	if (green > 1) {
		green = 1;
	}

	if (blue > 1) {
		blue = 1;
	}

	if (red < 0) {
		red = 0;
	}

	if (green < 0) {
		green = 0;
	}

	if (blue < 0) {
		blue = 0;
	}

	return Color(red, green, blue, special);
}



