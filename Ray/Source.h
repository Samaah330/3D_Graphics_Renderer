#pragma once
#include "Vector.h"
#include "Color.h"
#ifndef _SOURCE_H
#define _SOURCE_H

class Source {
	public:
		Source();
		virtual Vector getLightPosition();
		virtual Color getColor();


	
};
#endif