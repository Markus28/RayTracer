#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <vector>
#include <cassert>
#include "Color.h"
#include "Camera.h"

class RenderObject;
class Light;
class Intersection;
class Ray;


class Scene {
public:
    Scene(const std::vector<RenderObject*>& objects, const std::vector<Light*>& lights, Camera* camera, Color background, Vector3D ambient);
    void render(unsigned int recursion_depth);

private:
    Intersection firstHit(const Ray& ray);
    std::vector<RenderObject*> objs;
    std::vector<Light*> lights;
    Camera* cam;
    Color backgrnd;
    Vector3D ambient;

    Color traceRay(const Ray& ray, unsigned int recursion_depth);
};


#endif //RAYTRACER_SCENE_H