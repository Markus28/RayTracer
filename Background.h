#ifndef RAYTRACER_BACKGROUND_H
#define RAYTRACER_BACKGROUND_H


#include "Color.h"
#include "SphereMap.h"
#include <vector>

using Image = std::vector<std::vector<Color>>;
class Background {
public:
    explicit Background(Color c);
    explicit Background(const SphereMap<Color>& im);
    Color getColor(Vector3D coordinates);

private:
    SphereMap<Color> map;
};


#endif //RAYTRACER_BACKGROUND_H
