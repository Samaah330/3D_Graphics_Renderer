#pragma once

#ifndef _RAYTRACER_H
#define _RAYTRACER_H

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

#pragma warning (disable : 4996)

#include "Vector.h"
#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"

using namespace std;

struct RGB {
	double r;
	double g;
	double b;
};

class Raytracer {


	public:

		int width;
		int height;
		int dpi;
		RGB* pixels = new RGB[width * height];
		int thisone;
		
		Raytracer(int w, int h, int d);

		int getWidth();

		int getHeight();

		int getDPI();

		//RGB* getPixels();

		/**
		* Finds which object the ray intersects with (Sphere, Plane, or Neither);
		*/
		int winningObjectIndex(vector<double> object_intersections);

		/**
		* Returns the color at the intersection of the ray and Object
		*/
		Color getColorAtIntersection(Vector intersection_position, Vector intersecting_ray_direction,
			vector<Object*> scene_objects, int index_of_winning_object, vector<Source*> light_sources,
			double accuracy, double ambientLight);

		RGB* getImage();

		Color getReflection(Color winning_object_color, Vector winning_object_normal, Vector intersecting_ray_direction, Vector intersection_position,
			vector<Object*> scene_objects, double accuracy, vector<Source*> light_sources, double ambientLight, Color final_color);

		Color getLightAndShadow(vector<Source*> light_sources, Vector intersection_position, Vector winning_object_normal, vector<Object*> scene_objects,
			double accuracy, Color final_color, Color winning_object_color, Vector intersecting_ray_direction);

	private:
		Color getCheckerPattern(Color winning_object_color, Vector intersection_position);


		// to get reflection - 
		/* 
		A ray comes out of the camera, it intersects with an object
		in our scene, it reflects off of that object, and then it 
		intersects with another object in our scene
		if it intersects with another object we have a color of our 
		secondary object and that is going to get added to the color 
		of our first object. 
		So its going to be modifying the winning object color by 
		adding the color of the object that reflected off of our secondary 
		array and that is going to be what we return to our pixel so if the 
		Ray intersects off of our sphere and its reflective and then it
		intersects with our plane which is a white tile then we are going to 
		add the white tile color to the color of our sphere and thats going 
		to give the illusion of a reflection
		*/

};

#endif
