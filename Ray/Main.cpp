// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
#include "Raytracer.h"

using namespace std;


void saveFile(const char* filename, int w, int h, int dpi, RGB* data) {
    FILE* file;

    int k = w * h; 
    int s = 4 * k;
    int file_size = 54 + s;

    double factor = 39.375;
    int m = static_cast<int>(factor);

    int ppm = dpi * m;

    unsigned char bmpfileheader[14] = {
        'B','M', 0,0,0,0 ,0,0,0,0 ,54,0,0,0
    };

    unsigned char bmpinfoheader[40] = {
        40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0
    };

    bmpfileheader[2] = (unsigned char)(file_size);
    bmpfileheader[3] = (unsigned char)(file_size>>8);
    bmpfileheader[4] = (unsigned char)(file_size>>16);
    bmpfileheader[5] = (unsigned char)(file_size>>24);

    bmpinfoheader[4] = (unsigned char)(w);
    bmpinfoheader[5] = (unsigned char)(w>>8);
    bmpinfoheader[6] = (unsigned char)(w>>16);
    bmpinfoheader[7] = (unsigned char)(w>>24);

    bmpinfoheader[8] = (unsigned char)(h);
    bmpinfoheader[9] = (unsigned char)(h>>8);
    bmpinfoheader[10] = (unsigned char)(h>>16);
    bmpinfoheader[11] = (unsigned char)(h>>24);

    bmpinfoheader[21] = (unsigned char)(s);
    bmpinfoheader[22] = (unsigned char)(s>>8);
    bmpinfoheader[23] = (unsigned char)(s>>16);
    bmpinfoheader[24] = (unsigned char)(s>>24);

    bmpinfoheader[25] = (unsigned char)(ppm);
    bmpinfoheader[26] = (unsigned char)(ppm >> 8);
    bmpinfoheader[27] = (unsigned char)(ppm >> 16);
    bmpinfoheader[28] = (unsigned char)(ppm >> 24);

    bmpinfoheader[29] = (unsigned char)(ppm);
    bmpinfoheader[30] = (unsigned char)(ppm >> 8);
    bmpinfoheader[31] = (unsigned char)(ppm >> 16);
    bmpinfoheader[32] = (unsigned char)(ppm >> 24);

    file = fopen(filename, "wb");

    fwrite(bmpfileheader, 1, 14, file);
    fwrite(bmpinfoheader, 1, 40, file);

    for (int i = 0; i < k; i++) {
        RGB rgb = data[i];

        double red = (data[i].r) * 225;
        double green = (data[i].g) * 225; 
        double blue = (data[i].b) * 225;

        unsigned char color[3] = { (int)floor(blue), (int)floor(green), (int)floor(red)};
        fwrite(color, 1, 3, file);
    }

    fclose(file);
       
}

int thisone;
int main() {
    int dpi = 72;
    int height = 640;
    int width = 480;

    /*clock_t t1;
    clock_t t2;

    t1 = clock();*/
    
    Raytracer ray_tracer(width, height, dpi);

    saveFile("scene.bmp", width, height, dpi, ray_tracer.getImage());

    
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
