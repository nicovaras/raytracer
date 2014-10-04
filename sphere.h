#include "scene_object.h"
#include "Vec3.hpp"
#include "color.h"
#include "ray.h"

#ifndef SPHERE_H
#define SPHERE_H

class Sphere : public SceneObject {
public:
    Sphere(double r, Vec3 p) : radius(r),
                               pos(p) {
        color = Color(100, 100, 100);
    };

    Sphere(double r, Vec3 p, Color c) : radius(r),
                                        pos(p) {
        color = c;
    };

    double intersectScalar(Ray r);

    Vec3 normal(Vec3);

    double radius;
    Vec3 pos;
};

#endif