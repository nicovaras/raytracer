#include "raytracer.h"

using namespace cv;

Raytracer::Raytracer(int x, int y, Scene scene) {
    image = Mat(x, y, CV_8UC3);
    this->scene = scene;
}


void Raytracer::show_result() {
    imshow("Display window", image);
    waitKey(0);
}

void Raytracer::raytrace() {
    for (int x = 0; x < image.rows; ++x) {
        for (int y = 0; y < image.cols; ++y) {
            cast_ray_on(x, y);
        }
    }
}

void Raytracer::cast_ray_on(int x, int y) {
    Ray view_ray(Vec3(x, y, -100.0), Vec3(0.0, 0.0, 1.0));
    for (Scene::iterator scene_obj = scene.begin(); scene_obj != scene.end(); scene_obj++) {
        double t = (*scene_obj)->intersectScalar(view_ray);
        if (t > 0.0) {
            for (Scene::light_iterator l = scene.l_begin(); l != scene.l_end(); l++) {
                set_pixel_with_color_and_light(x, y, view_ray, scene_obj, t, l);
            }
        }
    }
}

void Raytracer::set_pixel_with_color_and_light(int x, int y, Ray view_ray, Scene::iterator scene_obj, double t, Scene::light_iterator l) {
    Vec3 point = view_ray.point_on(t);
    double cosine_factor = (*scene_obj)->normal(point) * (*l)->vectorFrom(point);
    if (cosine_factor > 0.0f) {
        double kd = (*scene_obj)->diffusion_coef;
        double ka = scene.ambient_coef;
        double R = (*scene_obj)->color.r,
                G = (*scene_obj)->color.g,
                B = (*scene_obj)->color.b;
        Color color = Color(
                    cosine_factor * R * kd + R * ka,
                    cosine_factor * G * kd + G * ka,
                    cosine_factor * B * kd + B * ka);

        Ray lr = Ray(point, (*l)->dir - point);
        for(int i =0;i<100;i++){
            int x1 = int (point.x + i*(lr.getDir().x));
            int y1 = int (point.y + i*(lr.getDir().y));
            if(x1 > 0 && y1 > 0)
            set_pixel_rgb(x1,
                          y1,
                          Color(255,255,255));
        }
        add_shadow(&color, lr, (*scene_obj));
        set_pixel_rgb(x, y, color);
    }
}

void Raytracer::set_pixel_rgb(int i, int j, Color color) {
    image.at<Vec3b>(i, j)[0] = color.b;
    image.at<Vec3b>(i, j)[1] = color.r;
    image.at<Vec3b>(i, j)[2] = color.g;
}

void Raytracer::add_shadow(Color *color, Ray ray, SceneObject* obj) {
    for (Scene::iterator scene_obj = scene.begin(); scene_obj != scene.end(); scene_obj++) {
        if(obj == (*scene_obj)) continue;
        double t = (*scene_obj)->intersectScalar(ray);
        if (t > 0.0) {
            color->r = int(color->r /2);
            color->g = int(color->g /2);
            color->b = int(color->b /2);
            return;
        }
    }
}
