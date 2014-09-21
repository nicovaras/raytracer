#include "Vec3.hpp"
#include "ray.h"
#include <vector>

#ifndef SCENE_H
#define SCENE_H

class SceneObject{
public:
    virtual double intersectScalar(Ray r) {}
};

class Sphere : public SceneObject {
public:
    Sphere(double r, Vec3 p) : radius(r), pos(p) {};
    double intersectScalar(Ray r);

private:
    double radius;
    Vec3 pos;
};

//Borrar y poner un vector y fue...
class Scene{
public:
    void addToScene(SceneObject*);
    typedef std::vector<SceneObject*>::iterator iterator;
    iterator begin() { return sceneObjects.begin(); }
    iterator end() { return sceneObjects.end(); }
private:
    std::vector<SceneObject*> sceneObjects;
};
#endif