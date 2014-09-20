#include <iostream>
#include "raytracer.h"
#include "ray.h"
using namespace std;

// Clase que haga los objectos renderizables
// Clase RT que tome los objecto a rendeizar

int main() {
    Ray view_ray(Vec3(2, 3, -1000.0), Vec3(0.0, 0.0, 1.0));
    cout << view_ray.point_on(20) << endl;
    Raytracer *R = new Raytracer(500,500);
    R->raytrace();
    R->show_result();
    delete R;
    return 0;
}