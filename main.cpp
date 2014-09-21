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
    s.addToScene(new Sphere(50.0, Vec3(500,800,50)));
    s.addToScene(new Sphere(100.0, Vec3(200,200,100)));
    s.addToScene(new Sphere(150.0, Vec3(600,200,100)));
    return s;
}