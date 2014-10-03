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
    s.addToScene(new Sphere(100.0, Vec3(500,800,250), Color(100,200,255)));
    s.addToScene(new Sphere(100.0, Vec3(200,200,200), Color(200,100,255)));
    s.addToScene(new Sphere(150.0, Vec3(300,400,150), Color(200,100,0)));  //verde
    s.addToScene(new Sphere(200.0, Vec3(700,100,500), Color(0,30,255)));  //azul
    s.addToScene(new Sphere(100.0, Vec3(600,300,300), Color(50,30,55))); //negra
    s.addToScene(new Sphere(40.0, Vec3(500,700,0), Color(255,255,255)));  //blanca
    s.addToScene(new Sphere(40.0, Vec3(600,700,0), Color(255,0,255)));  //blanca
    s.addToScene(new Light(Vec3(500.0,500.0,-300.0),Vec3(1.0,0.0,0.0)));
    return s;
}