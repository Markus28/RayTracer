#ifndef RAYTRACER_BACKGROUND_H
#define RAYTRACER_BACKGROUND_H


#include "SphereMap.h"
#include <vector>

using Image = std::vector<std::vector<Vector3D>>;
class Background {
public:
    explicit Background(Vector3D c);
    explicit Background(const SphereMap<Vector3D>& im);
    Vector3D getColor(Vector3D coordinates);

private:
    SphereMap<Vector3D> map;
};


#endif //RAYTRACER_BACKGROUND_H
