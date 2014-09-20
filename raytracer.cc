
#include "raytracer.h"
using namespace cv;

Raytracer::Raytracer(int x, int y) {
    image = Mat(x, y, CV_8UC3);
}


void Raytracer::show_result() {
    imshow("Display window",image);
    waitKey(0);
}


void Raytracer::raytrace() {
    for (int x = 0; x < image.rows; ++x) {
        for (int y = 0; y < image.cols; ++y) {
            Ray view_ray(Vec3(x, y, -1000.0), Vec3(0.0, 0.0, 1.0));
            set_pixel_rgb(x, y, Color(x, y, x + y));
        }
    }
}

//for each pixel of the screen
//{
//Final color = 0;
//Ray = { starting point, direction };
//Repeat
//{
//
//for each object in the scene
//{
//determine closest ray object/intersection;
//}
//if intersection exists
//        {
//                for each light in the scene
//                {
//                    if the light is not in shadow of another object
//                            {
//                                    add this light contribution to computed color;
//                            }
//                }
//        }
//Final color = Final color + computed color * previous reflection factor;
//reflection factor = reflection factor * surface reflection property;
//increment depth;
//} until reflection factor is 0 or maximum depth is reached;
//}
void Raytracer::set_pixel_rgb(int i, int j, Color color) {
    image.at<Vec3b>(i, j)[0] = color.b;
    image.at<Vec3b>(i, j)[1] = color.r;
    image.at<Vec3b>(i, j)[2] = color.g;
}

