#ifndef RAYTRACER_INTERSECTIONPROPERTIES_H
#define RAYTRACER_INTERSECTIONPROPERTIES_H


class Vector3D;
#include "Material.h"

class IntersectionProperties {
public:
    IntersectionProperties(const Vector3D& n, const Material& mat);
    Vector3D normal;
    Material material;
};


#endif //RAYTRACER_INTERSECTIONPROPERTIES_H