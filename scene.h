#include "Vec3.hpp"
#include "ray.h"
#include <vector>
#include "color.h"
#include "light.h"
#include "scene_object.h"

#ifndef SCENE_H
#define SCENE_H


class Scene {
public:
    Scene() : ambient_coef(0.1) {
    };

    void addToScene(SceneObject *);

    void addToScene(Light *);

    typedef std::vector<SceneObject *>::iterator iterator;
    typedef std::vector<Light *>::iterator light_iterator;

    iterator begin() {
        return sceneObjects.begin();
    }

    iterator end() {
        return sceneObjects.end();
    }

    light_iterator l_begin() {
        return lights.begin();
    }

    light_iterator l_end() {
        return lights.end();
    }

    double ambient_coef;

private:
    std::vector<SceneObject *> sceneObjects;
    std::vector<Light *> lights;

};

#endif