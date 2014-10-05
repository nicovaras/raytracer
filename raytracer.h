#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>
#include "ray.h"
#include "scene.h"
#include "light.h"
#include "color.h"

#ifndef RAYTRACER_H
#define RAYTRACER_H

using namespace cv;


class Raytracer {
public:
    Raytracer(int, int, Scene);

    void raytrace();

    void set_pixel_rgb(int, int, Color);

    void show_result();

private:
    Mat image;
    Scene scene;

    void cast_ray_on(int x, int y);

    void set_pixel_with_color_and_light(int x, int y, Ray view_ray, SceneObject *scene_obj, double t, Scene::light_iterator l);

    void add_shadow(Color *, Ray, SceneObject *);

    void draw_ray(Ray lr, Vec3 limit);

    void draw_lights();

    void set_intersected_pixel(int x, int y, Ray view_ray, SceneObject *scene_obj, double t);

    void set_background_pixel(int x, int y);

    Color reflex_ray_from(Vec3, Vec3 &, SceneObject *, int, Color);

    bool searchIntersection(int x, int y, Ray view_ray);

    Color getLambertLighting(SceneObject *scene_obj, Scene::light_iterator l, Vec3 point);

    double getPhongLighting(Ray view_ray, SceneObject *scene_obj, Scene::light_iterator l, Vec3 point);

    Color getReflectedColor(Ray view_ray, SceneObject *scene_obj, Vec3 point, Color obj_color, int repetitions);

    const static int REFLECT_REPETITIONS = 5;
};

#endif