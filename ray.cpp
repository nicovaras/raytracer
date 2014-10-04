#include "ray.h"

Vec3 Ray::point_on(float t) {
    return pos + dir * t;
};