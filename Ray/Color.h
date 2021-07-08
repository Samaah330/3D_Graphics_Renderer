#pragma once
#pragma once

#ifndef _COLOR_H
#define _COLOR_H

#include "math.h"

class Color {
	double red;
	double green;
	double blue;
	double special; // reflectivity and shininess

public:
	Color();
	Color(double red_value, double green_value, double blue_value, double special_value);

	double getColorRed();
	double getColorGreen();
	double getColorBlue();
	double getColorSpecial();

	void setColorRed(double r);
	void setColorGreen(double g);
	void setColorBlue(double b);
	void setColorSpecial(double s);

	double brightness();
	Color colorScalar(double scalar);
	Color colorAdd(Color color);
	Color colorMultiply(Color color);
	Color colorAverage(Color color);

	/**
	* checks to see if our light exceeds one and normalizes it past 
	* that value and if it is less than zero it normalizes in that direction
	* as well
	*/
	Color clip();
	
};

#endif
