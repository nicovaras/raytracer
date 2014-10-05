#ifndef COLOR_H
#define COLOR_H

#include "Vec3.hpp"
class Color : public Vec3 {
public:
    Color(int r, int g, int b): Vec3(r,g,b){
        r = std::min(x, 255.);
        g = std::min(y, 255.);
        b = std::min(z, 255.);
    }

    int r(){ return std::min(x, 255.);}
    int g(){ return std::min(y, 255.);}
    int b(){ return std::min(z, 255.);}



    friend Color operator+(Color lhs, Color const &rhs){
        Vec3 v = (Vec3)lhs +  (Vec3)rhs;
        return Color(v.x,v.y,v.z);
    };

    friend Color operator-(Color lhs, Color const &rhs){
        Vec3 v = (Vec3)lhs - (Vec3)rhs;
        return Color(v.x,v.y,v.z);
    };

    friend Color operator*(double f, const Color &col){
        Vec3 v = f * (Vec3)col;
        return Color(v.x,v.y,v.z);
    };

    friend Color operator*(const Color &col, double f){
        Vec3 v = (Vec3)col * f;
        return Color(v.x,v.y,v.z);
    };

};

#endif