#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>
#include "ray.h"
#include "scene.h"
#include "color.h"

#ifndef RAYTRACER_H
#define RAYTRACER_H

using namespace cv;


class Raytracer{
public:
    Raytracer(int, int, Scene);
    void raytrace();
    void set_pixel_rgb(int , int , Color);
    void show_result();

private:
    Mat image;
    Scene scene;

    void cast_ray_on(int x, int y);
    void set_pixel_with_color_and_light(int x, int y, Ray view_ray, Scene::iterator scene_obj, double t, Scene::light_iterator l);
    void add_shadow(Color * , Ray, SceneObject *);
};

#endif