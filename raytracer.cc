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
//    draw_lights();
}

void Raytracer::cast_ray_on(int x, int y) {
    Ray view_ray(Vec3(x, y, -100.0), Vec3(0.0, 0.0, 1.0));
    if (!searchIntersection(x, y, view_ray)) {
        set_background_pixel(x, y);
    }
}

bool Raytracer::searchIntersection(int x, int y, Ray view_ray) {
    bool intersected = false;

    for (Scene::iterator scene_obj = scene.begin(); scene_obj != scene.end(); scene_obj++) {
        double t = (*scene_obj)->intersectScalar(view_ray);
        if (t > 0.0) {
            intersected = true;
            set_intersected_pixel(x, y, view_ray, *scene_obj, t);
        }
    }
    return intersected;
}


void Raytracer::set_intersected_pixel(int x, int y, Ray view_ray, SceneObject *scene_obj, double t) {
    for (Scene::light_iterator l = scene.l_begin(); l != scene.l_end(); l++) {
        set_pixel_with_color_and_light(x, y, view_ray, scene_obj, t, l);
    }
}

void Raytracer::set_pixel_with_color_and_light(int x, int y, Ray view_ray, SceneObject *scene_obj, double t, Scene::light_iterator l) {
    Vec3 point = view_ray.point_on(t);
    Color obj_color = getLambertLighting(scene_obj, l, point);

    double phongTerm = getPhongLighting(view_ray, scene_obj, l, point);

    obj_color = obj_color * phongTerm + obj_color;
    obj_color = getReflectedColor(view_ray, scene_obj, point, obj_color, REFLECT_REPETITIONS);

    Vec3 lr_dir = (*l)->pos - point;
    Ray lr = Ray(point, lr_dir.unit());
    add_shadow(&obj_color, lr, scene_obj);

    set_pixel_rgb(x, y, obj_color);
}

Color Raytracer::getReflectedColor(Ray view_ray, SceneObject *scene_obj, Vec3 point, Color obj_color, int repetitions) {
    Color reflected_color = reflex_ray_from(point, view_ray.getPos(), scene_obj, repetitions, obj_color);
    double rc = scene_obj->reflection_coef;
    obj_color = (1 - rc) * obj_color + rc * reflected_color;
    return obj_color;
}

double Raytracer::getPhongLighting(Ray view_ray, SceneObject *scene_obj, Scene::light_iterator l, Vec3 point) {
    double reflect = 2.0 * ((*l)->dir * scene_obj->normal(point));
    Vec3 phongDir = (*l)->dir - reflect * scene_obj->normal(point);
    double phongTerm = max(phongDir * view_ray.getDir(), 0.0);
    double spec = 3;
    phongTerm = spec * pow(phongTerm, spec);
    return phongTerm;
}

Color Raytracer::getLambertLighting(SceneObject *scene_obj, Scene::light_iterator l, Vec3 point) {
    double cosine_factor = scene_obj->normal(point) * (*l)->vectorFrom(point);
    double ka = scene.ambient_coef;
    double kd = scene_obj->diffusion_coef;
    if (cosine_factor > 0.0f) {
        Color obj_color = ka * scene_obj->color;

        obj_color = obj_color + cosine_factor * kd * scene_obj->color;
        return obj_color;
//        draw_ray(lr, (*l)->pos );
    }
    return Color(0,0,0);
}


void Raytracer::set_background_pixel(int x, int y) {
    Color c = Color(250, 250, 250);
    for (Scene::light_iterator l = scene.l_begin(); l != scene.l_end(); l++) {
        Vec3 lr_dir = (*l)->pos - Vec3(x, y, 500.0);
        Ray lr = Ray(Vec3(x, y, 500.0), lr_dir.unit());
        add_shadow(&c, lr, 0);
    }
    set_pixel_rgb(x, y, c);
}

void Raytracer::draw_ray(Ray lr, Vec3 limit) {
    if (rand() % 1000 < 1) {
        for (int i = 0; i < 1000; i++) {
            int x1 = int(lr.getPos().x + i * (lr.getDir().x));
            int y1 = int(lr.getPos().y + i * (lr.getDir().y));
            if (lr.getDir().x > 0 && x1 > limit.x) continue;
            if (lr.getDir().x < 0 && x1 < limit.x) continue;
            if (lr.getDir().y > 0 && y1 > limit.y) continue;
            if (lr.getDir().y > 0 && y1 > limit.y) continue;

            if (x1 >= 0 && y1 >= 0 && x1 < 1000 && y1 < 1000) {
                set_pixel_rgb(x1, y1, Color(255, 255, 255));
            }
        }
    }
}

void Raytracer::set_pixel_rgb(int i, int j, Color color) {
    image.at<Vec3b>(i, j)[0] = color.b();
    image.at<Vec3b>(i, j)[1] = color.r();
    image.at<Vec3b>(i, j)[2] = color.g();
}

void Raytracer::add_shadow(Color *color, Ray ray, SceneObject *obj) {
    for (Scene::iterator scene_obj = scene.begin(); scene_obj != scene.end(); scene_obj++) {
        if (obj == (*scene_obj)) continue;
        double t = (*scene_obj)->intersectScalar(ray);
        if (t > 0.0) {
            *color = 0.5 * (*color);


        }
    }
}

void Raytracer::draw_lights() {
    for (Scene::light_iterator l = scene.l_begin(); l != scene.l_end(); l++) {
        (*l)->addSprite(image);
    }
}

Color Raytracer::reflex_ray_from(Vec3 point, Vec3 &dir, SceneObject *obj, int repetitions, Color color) {

    if(repetitions <= 0)
        return color;

    double reflect = 2.0 * (dir * obj->normal(point));
    Ray new_ray = Ray(point, dir - reflect * obj->normal(point));

    for (Scene::iterator scene_obj = scene.begin(); scene_obj != scene.end(); scene_obj++) {
        if (obj == (*scene_obj))
            continue;
        double t = (*scene_obj)->intersectScalar(new_ray);
        if (t < 0.0) {
            for (Scene::light_iterator l = scene.l_begin(); l != scene.l_end(); l++) {
                Vec3 new_point = new_ray.point_on(t);
                color =  getLambertLighting(*scene_obj, l, new_point);

                color = getReflectedColor(new_ray, *scene_obj, point, color, repetitions - 1);

                Vec3 lr_dir = (*l)->pos - point;
                Ray lr = Ray(point, lr_dir.unit());
                add_shadow(&color, lr, *scene_obj);
                return color;
            }
        }
    }
    return Color(0, 0, 0);
}