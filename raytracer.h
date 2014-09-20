#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>
#include "ray.h"

#ifndef RAYTRACER_H
#define RAYTRACER_H

using namespace cv;

struct Color{
    Color(int r, int g, int b) : r(r), g(g), b(b) {}
    int r;
    int g;
    int b;
};

class Raytracer{
public:
    Raytracer(int, int);
    void raytrace();
    void set_pixel_rgb(int , int , Color);
    void show_result();

private:
    Mat image;

};

#endif