#pragma once
#ifndef _LIGHT_H
#define _LIGHT_H

#include "Vector.h"
#include "Color.h"
#include "Source.h"

class Light : public Source {
	Vector position;
	Color color;

	public:
		Light();
		Light(Vector pos, Color col);

		 virtual Vector getLightPosition();
		 virtual Color getColor();
};

#endif
