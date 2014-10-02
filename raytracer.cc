#include "raytracer.h"
#include <algorithm>    // std::max
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
    draw_lights();
}

void Raytracer::cast_ray_on(int x, int y) {
    Ray view_ray(Vec3(x, y, -100.0), Vec3(0.0, 0.0, 1.0));
    bool intersected = false;
    for (Scene::iterator scene_obj = scene.begin(); scene_obj != scene.end(); scene_obj++) {
        double t = (*scene_obj)->intersectScalar(view_ray);
        if (t > 0.0) {
            intersected = true;
            set_intersected_pixel(x, y, view_ray, scene_obj, t);
        }
    }
    if(!intersected){
        set_background_pixel(x, y);
    }
}

void Raytracer::set_background_pixel(int x, int y) {
    Color c = Color(250,250,250);
    for (Scene::light_iterator l = scene.l_begin(); l != scene.l_end(); l++) {
            Vec3 lr_dir = (*l)->pos - Vec3(x,y,500.0);
            Ray lr = Ray(Vec3(x,y,500.0), lr_dir.unit());
            add_shadow(&c, lr, 0);
        }
    set_pixel_rgb(x, y, c);
}

void Raytracer::set_intersected_pixel(int x, int y, Ray view_ray, Scene::iterator scene_obj, double t) {
    for (Scene::light_iterator l = scene.l_begin(); l != scene.l_end(); l++) {
        set_pixel_with_color_and_light(x, y, view_ray, scene_obj, t, l);
    }
}

void Raytracer::set_pixel_with_color_and_light(int x, int y, Ray view_ray, Scene::iterator scene_obj, double t, Scene::light_iterator l) {
    Vec3 point = view_ray.point_on(t);
    double cosine_factor = (*scene_obj)->normal(point) * (*l)->vectorFrom(point);
    double ka = scene.ambient_coef;
    double kd = (*scene_obj)->diffusion_coef;
    double  R = (*scene_obj)->color.r,
            G = (*scene_obj)->color.g,
            B = (*scene_obj)->color.b;
    Color color = Color(R * ka, G * ka, B * ka);
    if (cosine_factor > 0.0f) {
        color.r += cosine_factor * kd * R;
        color.g += cosine_factor * kd * G;
        color.b += cosine_factor * kd * B;




        Vec3 lr_dir = (*l)->pos - point;
        Ray lr = Ray(point, lr_dir.unit());
//        draw_ray(lr, (*l)->pos );
        add_shadow(&color, lr, (*scene_obj));
    }
    Color reflected_color = reflex_ray_from(point, view_ray.getPos(), (*scene_obj));
    double rc =(*scene_obj)->reflection_coef;
    color.r =(1 - rc) * color.r + rc * reflected_color.r;
    color.g =(1 - rc) * color.g + rc * reflected_color.g;
    color.b =(1 - rc) * color.b + rc * reflected_color.b;

    set_pixel_rgb(x, y, color);

}

void Raytracer::draw_ray(Ray lr, Vec3 limit) {
    if(rand()%1000 < 1) {
        for (int i = 0; i < 1000; i++) {
            int x1 = int(lr.getPos().x + i * (lr.getDir().x));
            int y1 = int(lr.getPos().y + i * (lr.getDir().y));
            if(lr.getDir().x > 0 && x1 > limit.x) continue;
            if(lr.getDir().x < 0 && x1 < limit.x) continue;
            if(lr.getDir().y > 0 && y1 > limit.y) continue;
            if(lr.getDir().y > 0 && y1 > limit.y) continue;

            if (x1 >= 0 && y1 >= 0 && x1 < 1000 && y1 < 1000) {
                set_pixel_rgb(x1, y1, Color(255, 255, 255));
            }
        }
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
//        double dir = obj->normal(ray.point_on(t)) * (*scene_obj)->normal(ray.point_on(t));
//        if (t > 0.0 && dir < 0.0) {
        if (t > 0.0){
            color->r = int(color->r * 0.5);
            color->g = int(color->g * 0.5);
            color->b = int(color->b * 0.5);

        }
    }
}

void Raytracer::draw_lights() {
    for (Scene::light_iterator l = scene.l_begin(); l != scene.l_end(); l++) {
        (*l)->addSprite(image);
    }
}

Color Raytracer::reflex_ray_from(Vec3 point, Vec3 &dir, SceneObject *obj) {

    //TODO CODIGO REPETIDO
    double reflect = 2.0 * (dir * obj->normal(point));
    Ray new_ray = Ray(point, dir - reflect*obj->normal(point));

    for (Scene::iterator scene_obj = scene.begin(); scene_obj != scene.end(); scene_obj++) {
        if(obj == (*scene_obj))
            continue;
        double t = (*scene_obj)->intersectScalar(new_ray);
        if (t < 0.0) {
            for (Scene::light_iterator l = scene.l_begin(); l != scene.l_end(); l++) {
                Vec3 new_point = new_ray.point_on(t);
                double cosine_factor = (*scene_obj)->normal(new_point) * (*l)->vectorFrom(new_point);
                double ka = scene.ambient_coef;
                double kd = (*scene_obj)->diffusion_coef;
                double  R = (*scene_obj)->color.r,
                        G = (*scene_obj)->color.g,
                        B = (*scene_obj)->color.b;
                if (cosine_factor > 0.0f) {
                    Color color = Color(R * ka, G * ka, B * ka);
                    color.r += cosine_factor * kd * R;
                    color.g += cosine_factor * kd * G;
                    color.b += cosine_factor * kd * B;
                    Vec3 lr_dir = (*l)->pos - new_point;
                    Ray lr = Ray(new_point, lr_dir.unit());
                    add_shadow(&color, lr, (*scene_obj));
                    return color;

                }

            }
        }
    }
    return Color(0, 0, 0);
}
