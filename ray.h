#include "Vec3.hpp"
#ifndef RAY_H
#define RAY_H

class Ray{
public:
    Ray(Vec3 pos, Vec3 dir) : pos(pos), dir(dir) {};
    Vec3 point_on(float);
    std::ostream& operator<<(std::ostream& os);
    Vec3 const &getPos() const { return pos; }
    Vec3 const &getDir() const { return dir; }

private:
    Vec3 pos;
    Vec3 dir;

};

#endif