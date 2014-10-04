#include <math.h>
#include "sphere.h"

double Sphere::intersectScalar(Ray r) {
    Vec3 dist = pos - r.getPos();
    double b = r.getDir() * dist;
    double d = b * b - dist * dist + radius * radius;
    if (d < 0.0f) {
        return -1.0;
    }
    double t0 = b - sqrt(d);
    double t1 = b + sqrt(d);

    double t = 999999.9;
    if (t0 > 0.1 && t0 < t) {
        t = t0;
    }
    if (t1 > 0.1 && t1 < t) {
        t = t1;
    }

    if (t != 999999.9) {

        return t;
    } else {
        return -1.0;
    }
}

Vec3 Sphere::normal(Vec3 point) {
    Vec3 normal = Vec3((point.x - pos.x) / radius,
            (point.y - pos.y) / radius,
            (point.z - pos.z) / radius);
    return normal;
}
