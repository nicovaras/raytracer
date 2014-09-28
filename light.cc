#include <unistd.h>
#include "light.h"
#include <string>
Vec3 Light::vectorFrom(Vec3 point){
    Vec3 l = Vec3(pos.x - point.x, pos.y - point.y, pos.z - point.z);
    l = l * (1/l.norm());
    return l;
}

void Light::addSprite(cv::Mat big_image){
    light_sprite.convertTo(light_sprite, big_image.type());
    cv::Rect roi( cv::Point( pos.x- 24, pos.y - 24), light_sprite.size() );
    light_sprite.copyTo( big_image( roi ) );
}

cv::Mat Light::light_sprite = cv::imread("resources/lightbulb.png",CV_LOAD_IMAGE_COLOR );

