#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <vector>
#include <cassert>
#include "Camera.h"

class RenderObject;
class Light;
class Intersection;
class Ray;


/**
 * @brief The Scene-Object is used to compose RenderObjects, Lights, the Background and render them
 */
class Scene {
public:
    Scene(const std::vector<RenderObject*>& objects, const std::vector<Light*>& lights, Camera* camera, Vector3D background, Vector3D ambient);
    void render(unsigned int recursion_depth);

private:
    Intersection first_hit(const Ray &ray, bool ignore_transparent);
    Intersection first_hit(const Ray &ray);
    std::vector<RenderObject*> objs;
    std::vector<Light*> lights;
    Camera* cam;
    Vector3D backgrnd;
    Vector3D ambient;

    Vector3D traceRay(const Ray& ray, unsigned int recursion_depth);
};


#endif //RAYTRACER_SCENE_H