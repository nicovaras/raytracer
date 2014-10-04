#include "scene.h"

void Scene::addToScene(SceneObject *object) {
    sceneObjects.push_back(object);
}

void Scene::addToScene(Light *light) {
    lights.push_back(light);
}
