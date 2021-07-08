#include "Raytracer.h"

Raytracer::Raytracer(int w, int h, int d) {
    width = w;
    height = h;
    dpi = d;
}

int Raytracer::getWidth() {
    return width;
}

int Raytracer::getHeight() {
    return height;
}

int Raytracer::getDPI() {
    return dpi;
}

int Raytracer::winningObjectIndex(vector<double> object_intersections) {
    // returns the index of the winning intersection
    int index_of_min_value;

    //prevent unnecessary calculations
    if (object_intersections.size() == 0) {
        // if there are no intersections
        return -1;
    }
    else if (object_intersections.size() == 1) {
        if (object_intersections.at(0) > 0) {
            // if that intersection is greater than zero then its our minimum value
            return 0;
        }
        else {
            // otherwise the only intersection value is negative
            return -1;
        }
    }
    else {
        // otherwise there is more than one intersection
        // first find the maximum value

        double max = 0;
        for (int i = 0; i < object_intersections.size(); i++) {
            if (max < object_intersections.at(i)) {
                max = object_intersections.at(i);
            }
        }

        // then starting from the max value find the min positive value
        if (max > 0) {
            // we only want positive intersections
            for (int index = 0; index < object_intersections.size(); index++) {

                if (object_intersections.at(index) > 0 && object_intersections.at(index) <= max) {
                    max = object_intersections.at(index);
                    index_of_min_value = index;

                }
            }

            // cout << index_of_min_value;
            return index_of_min_value;
        }
        else {
            // all the intersections were neg
            return -1;
        }
    }
}

Color Raytracer::getColorAtIntersection(Vector intersection_position, Vector intersecting_ray_direction,
	vector<Object*> scene_objects, int index_of_winning_object, vector<Source*> light_sources,
	double accuracy, double ambientLight) {

    Color winning_object_color = scene_objects.at(index_of_winning_object)->getColor();
    Vector winning_object_normal = scene_objects.at(index_of_winning_object)->getNormalAt(intersection_position);
    Color final_color = winning_object_color.colorScalar(ambientLight);

  
   final_color = getReflection(winning_object_color, winning_object_normal, intersecting_ray_direction, 
        intersection_position, scene_objects, accuracy, light_sources, ambientLight, final_color);

   winning_object_color =  getCheckerPattern(winning_object_color, intersection_position);

   final_color = getLightAndShadow(light_sources, intersection_position, winning_object_normal,
       scene_objects, accuracy, final_color, winning_object_color, intersecting_ray_direction);

   return final_color.clip();
 
}

Color Raytracer::getCheckerPattern(Color winning_object_color, Vector intersection_position) {
    if (winning_object_color.getColorSpecial() == 2) {
        int square = (int)floor(intersection_position.getVectorX()) +
            (int)floor(intersection_position.getVectorZ());

        if (square % 2 == 0) {
            //black tile
            winning_object_color.setColorRed(0.0);
            winning_object_color.setColorGreen(0.0);
            winning_object_color.setColorBlue(0.0);
        }
        else {
            // white tile
            winning_object_color.setColorRed(1.0);
            winning_object_color.setColorGreen(1.0);
            winning_object_color.setColorBlue(1.0);
        }
    }

    return winning_object_color;
}

Color Raytracer::getReflection(Color winning_object_color, Vector winning_object_normal, Vector intersecting_ray_direction, Vector intersection_position,
                              vector<Object*> scene_objects, double accuracy, vector<Source*> light_sources, double ambientLight, Color final_color) {

    if (winning_object_color.getColorSpecial() > 0 && winning_object_color.getColorSpecial() <= 1) {
        // reflection from objects with specular intensity. 
        double dot1 = winning_object_normal.dotProduct(intersecting_ray_direction.negate());
        Vector scalar1 = winning_object_normal.vectorMultiply(dot1);
        Vector add1 = scalar1.vectorAdd(intersecting_ray_direction);
        Vector scalar2 = add1.vectorMultiply(2);
        Vector add2 = intersecting_ray_direction.negate().vectorAdd(scalar2);
        Vector reflection_direction = add2.normalize();

        Ray reflection_ray(intersection_position, reflection_direction);

        // determine what the ray intersets with first
        vector<double> reflection_intersections;

        for (int reflection_index = 0; reflection_index < scene_objects.size(); reflection_index++) {
            reflection_intersections.push_back(scene_objects.at(reflection_index)->findIntersection(reflection_ray));
        }


        int index_of_winning_object_with_reflection = winningObjectIndex(reflection_intersections);

        if (index_of_winning_object_with_reflection != -1) {
            // reflection ray missed everything else

            if (reflection_intersections.at(index_of_winning_object_with_reflection) > accuracy) {
                // determine the position and direction at the point of intersection with the reflection ray
                // the ray only affects the color if it reflected off of something

                Vector reflection_intersection_position = intersection_position.vectorAdd(reflection_direction.vectorMultiply
                (reflection_intersections.at(index_of_winning_object_with_reflection)));

                Vector reflection_intersection_ray_direction = reflection_direction;

                Color reflection_intersection_color = getColorAtIntersection(reflection_intersection_position, reflection_intersection_ray_direction,
                    scene_objects, index_of_winning_object_with_reflection, light_sources, accuracy, ambientLight);

                final_color = final_color.colorAdd(reflection_intersection_color.colorScalar(winning_object_color.getColorSpecial()));

            }

        }
    }

    return final_color;
}

Color Raytracer::getLightAndShadow(vector<Source*> light_sources, Vector intersection_position, Vector winning_object_normal, vector<Object*> scene_objects,
    double accuracy, Color final_color, Color winning_object_color, Vector intersecting_ray_direction) {
    for (int i = 0; i < light_sources.size(); i++) {
        Vector light_direction = light_sources.at(i)->getLightPosition().vectorAdd(intersection_position.negate()).normalize();

        float cosine_angle = winning_object_normal.dotProduct(light_direction);

        if (cosine_angle > 0) {
            // test for shadows
            bool shadowed = false;

            //finding distance to light source from our intersection point
            Vector distance_to_light = light_sources.at(i)->getLightPosition().vectorAdd(intersection_position.negate()).normalize();
            float distance_to_light_magnitude = distance_to_light.magnitude();

            // now we are going to create a new array in the direction from our intersection point to the light source
            // and we are going to look and see if that new array intersects with anything on its way to the light source
            // and if it does that means that our intersection is in shadow
            Ray shadow_ray(intersection_position, light_sources.at(i)->getLightPosition().vectorAdd(intersection_position.negate()).normalize());

            vector<double> secondary_intersections;

            for (int object_index = 0; object_index < scene_objects.size() && shadowed == false; object_index++) {
                secondary_intersections.push_back(scene_objects.at(object_index)->findIntersection(shadow_ray));
            }

            // if we loop through our secondary intersections and we find that there is an intersection value there 
            // and it is less than the distance to the light source then that means the pixel is now shadowed
            for (int c = 0; c < secondary_intersections.size(); c++) {
                if (secondary_intersections.at(c) > accuracy) {
                    if (secondary_intersections.at(c) <= distance_to_light_magnitude) {
                        shadowed = true;
                    }
                }
                // break here?
                break;
            }

            if (shadowed == false) {
                final_color = final_color.colorAdd(winning_object_color.colorMultiply(light_sources.at(i)->getColor()).colorScalar(cosine_angle));

                if (winning_object_color.getColorSpecial() > 0 && winning_object_color.getColorSpecial() <= 1) {
                    // special [0 - 1]
                    double dot1 = winning_object_normal.dotProduct(intersecting_ray_direction.negate());
                    Vector scalar1 = winning_object_normal.vectorMultiply(dot1);
                    Vector add1 = scalar1.vectorAdd(intersecting_ray_direction);
                    Vector scalar2 = add1.vectorMultiply(2);
                    Vector add2 = intersecting_ray_direction.negate().vectorAdd(scalar2);
                    Vector reflection_direction = add2.normalize();

                    double specular = reflection_direction.dotProduct(light_direction);
                    if (specular > 0) {
                        specular = pow(specular, 10);
                        final_color = final_color.colorAdd(light_sources.at(i)->getColor().colorScalar(specular * winning_object_color.getColorSpecial()));
                    }
                }
            }

        }
    }

    return final_color;
}

// break this method up
RGB* Raytracer::getImage() {
    int size = width * height;
    double aspectratio = (double)width / (double)height;
    double ambientLight = 0.2;
    double accuracy = 0.0000001;

    RGB* pixels = new RGB[size];

    Vector origin(0, 0, 0);
    Vector camera_position(3.0, 1.5, -4.0);
    Vector x(1, 0, 0);
    Vector y(0, 1, 0);
    Vector z(0, 0, 1);

    //defines direction of camera (where the camera is looking at)
    Vector look_at(0, 0, 0);
    Vector difference(camera_position.getVectorX() - look_at.getVectorX(),
        camera_position.getVectorY() - look_at.getVectorY(),
        camera_position.getVectorZ() - look_at.getVectorZ());

    Vector camera_direction = difference.negate().normalize();
    Vector camera_right = y.crossProduct(camera_direction).normalize();
    Vector camera_down = camera_right.crossProduct(camera_direction);

    Camera scene_camera(camera_position, camera_direction, camera_right, camera_down);

    Color white_light(1.0, 1.0, 1.0, 0);
    Color green(0.5, 1.0, 0.5, 0.3);
    Color gray(0.5, 0.5, 0.5, 0);
    Color black(0.0, 0.0, 0.0, 0);
    Color maroon(0.5, 0.25, 0.25, 0);
    Color tile_floor(1, 1, 1, 2);

    Vector light_position(-7, 10, -10);
    Light scene_light(light_position, white_light);
    vector<Source*> light_sources;
    light_sources.push_back(dynamic_cast<Source*>(&scene_light));


    // scene objects
    Sphere scene_sphere(origin, 1, green);
    Plane scene_plane(y, -1, tile_floor);

    vector<Object*> scene_objects;
    scene_objects.push_back(dynamic_cast<Object*>(&scene_sphere));
    scene_objects.push_back(dynamic_cast<Object*>(&scene_plane));

    double xamnt;
    double yamnt;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            thisone = y * width + x;

            if (width > height) {
                // the image is wider than it is tall
                xamnt = ((x + 0.5) / width) * aspectratio - (((width - height) / (double)height) / 2);
                yamnt = ((height - y) + 0.5) / height;
            }
            else if (height > width) {
                // the image is taller than it is wide
                xamnt = (x + 0.5) / width;
                yamnt = (((height - y) + 0.5) / height) / aspectratio - (((height - width) / (double)width) / 2);
            }
            else {
                // the image is square
                xamnt = (x + 0.5) / width;
                yamnt = ((height - y) + 0.5) / height;
            }

            Vector camera_ray_origin = scene_camera.getCameraPosition();
            Vector camera_ray_direction = camera_direction.vectorAdd
            (camera_right.vectorMultiply(xamnt - 0.5).vectorAdd(camera_down.vectorMultiply(yamnt - 0.5))).normalize();

            Ray camera_ray(camera_ray_origin, camera_ray_direction);

            vector<double> intersections;

            // loop through each of the objects in our scene and determine if the ray that we 
            // created intersects with any of those objects in our scene
            for (int index = 0; index < scene_objects.size(); index++) {
                intersections.push_back(scene_objects.at(index)->findIntersection(camera_ray));
            }

            int index_of_winning_object = winningObjectIndex(intersections);


            if (index_of_winning_object == -1) {
                // set background black
                pixels[thisone].r = 0;
                pixels[thisone].g = 0;
                pixels[thisone].b = 0;
            }
            else {
                // index corrresponds to an object in our scene

                // if the intersection at that point is greater than our accuracy
                if (intersections.at(index_of_winning_object) > accuracy) {
                    // determine the position and direction vectors at the point of intersection 

                    Vector intersection_position = camera_ray_origin.vectorAdd(camera_ray_direction.vectorMultiply(intersections.at(index_of_winning_object)));
                    Vector intersecting_ray_direction = camera_ray_direction;

                    Color intersection_color = getColorAtIntersection(intersection_position, intersecting_ray_direction, scene_objects, index_of_winning_object, light_sources, accuracy, ambientLight);

                    pixels[thisone].r = intersection_color.getColorRed();
                    pixels[thisone].g = intersection_color.getColorGreen();
                    pixels[thisone].b = intersection_color.getColorBlue();
                }
            }
        }
    }

    return pixels;
}