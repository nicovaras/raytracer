#include "Vec3.hpp"
#include "ray.h"
#include <vector>
#include "color.h"

#ifndef SCENE_H
#define SCENE_H

class SceneObject{
public:
    SceneObject() : color(Color(0,0,0)) {};
    virtual double intersectScalar(Ray r) {}
    virtual Vec3 normal(Vec3) {}
    Color color;
    double diffusion_coef;
};

class Sphere : public SceneObject {
public:
    Sphere(double r, Vec3 p) : radius(r),
                               pos(p){
        color = Color(100,100,100);
        diffusion_coef = 0.9;
    };
    Sphere(double r, Vec3 p, Color c) : radius(r),
                                        pos(p){
        color = c;
        diffusion_coef = 0.9;
    };

    double intersectScalar(Ray r);
    Vec3 normal(Vec3);

    double radius;
    Vec3 pos;
};

class Light{
public:
    Light(Vec3 pos, Vec3 dir) : pos(pos),
                                dir(dir),
                                ambient_coef(0.1){};
    Vec3 vectorFrom(Vec3 point){
        Vec3 l = Vec3(pos.x - point.x, pos.y - point.y, pos.z - point.z);
        l = l * (1/l.norm());
        return l;
    }
    Vec3 pos;
    Vec3 dir;
    double ambient_coef;
};

//Borrar y poner un vector y fue...
class Scene{
public:
    void addToScene(SceneObject*);
    void addToScene(Light*);
    typedef std::vector<SceneObject*>::iterator iterator;
    typedef std::vector<Light*>::iterator light_iterator;
    iterator begin() { return sceneObjects.begin(); }
    iterator end() { return sceneObjects.end(); }
    light_iterator l_begin() { return lights.begin(); }
    light_iterator l_end() { return lights.end(); }


private:
    std::vector<SceneObject*> sceneObjects;
    std::vector<Light*> lights;

};
#endif