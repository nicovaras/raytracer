#include <iostream>

#ifndef VEC3_H
#define VEC3_H

class Vec3 {
public:
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {
    }

    float x;
    float y;
    float z;

    friend std::ostream &operator<<(std::ostream &, const Vec3 &);

    friend Vec3 operator+(Vec3 lhs, Vec3 const &rhs);

    friend Vec3 operator-(Vec3 lhs, Vec3 const &rhs);

    friend Vec3 operator*(double f, const Vec3 &);

    friend Vec3 operator*(const Vec3 &, double f);

    friend double operator*(const Vec3 &, const Vec3 &);

    friend bool operator==(const Vec3 &, const Vec3 &);

    double norm();

    Vec3 unit();
};


#endif