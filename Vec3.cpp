#include <math.h>
#include "Vec3.hpp"


Vec3 operator+(Vec3 lhs, Vec3 const &rhs) {
    return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vec3 operator-(Vec3 lhs, Vec3 const &rhs) {
    return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Vec3 operator*(double f, const Vec3 &v) {
    return Vec3(v.x * f, v.y * f, v.z * f);
}

Vec3 operator*(const Vec3 &v, double f) {
    return f * v;
}

bool operator==(const Vec3 &v, const Vec3 &w) {
    return v.x == w.x && v.y == w.y && v.z == w.z;
};

std::ostream &operator<<(std::ostream &os, const Vec3 &v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

double operator*(Vec3 const &lhs, Vec3 const &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

double Vec3::norm() {
    return sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::unit() {
    return operator*((*this), 1.0 / this->norm());
}
