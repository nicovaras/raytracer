#include <cv.h>
#include <highgui.h>
#include "Vec3.hpp"

#ifndef LIGHT_H
#define LIGHT_H

class Light{


public:
    Light(Vec3 pos, Vec3 dir) : pos(pos),
                                dir(dir) { };
    Vec3 vectorFrom(Vec3 point);
    void addSprite(cv::Mat big_image);
    Vec3 pos;
    Vec3 dir;
    static cv::Mat light_sprite ;

};

#endif