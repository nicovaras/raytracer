#include <iostream>
#include "raytracer.h"
#include "ray.h"

Scene get_scene();

using namespace std;

// Clase que haga los objectos renderizables
// Clase RT que tome los objecto a rendeizar

int main() {
    Raytracer *R = new Raytracer(1000,1000, get_scene());
    R->raytrace();
    R->show_result();
    delete R;
    return 0;
}

Scene get_scene() {
    Scene s = Scene();
    s.addToScene(new Sphere(100.0, Vec3(500,800,0), Color(100,200,255)));
    s.addToScene(new Sphere(100.0, Vec3(200,200,0), Color(200,100,255)));
    s.addToScene(new Sphere(100.0, Vec3(400,400,0), Color(200,100,0)));
    s.addToScene(new Sphere(100.0, Vec3(600,200,0), Color(0,30,255)));
    s.addToScene(new Sphere(100.0, Vec3(120,700,0), Color(50,30,55)));
    s.addToScene(new Sphere(100.0, Vec3(800,600,0), Color(255,255,255)));
    s.addToScene(new Light(Vec3(0.0,0.0,0.0),Vec3(1.0,0.0,0.0)));
    return s;
}