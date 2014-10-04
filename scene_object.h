#ifndef SCENE_OBJ_H
#define SCENE_OBJ_H

#include "color.h"
#include "ray.h"
#include "Vec3.hpp"

class SceneObject {
public:
    SceneObject() : color(Color(0, 0, 0)), reflection_coef(0.2), diffusion_coef(0.4) {
    };

    virtual double intersectScalar(Ray r) {
    }

    virtual Vec3 normal(Vec3) {
    }

    Color color;
    double diffusion_coef;
    double reflection_coef;
};

#endif