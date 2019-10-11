#ifndef RAYTRACER_INTERSECTIONPROPERTIES_H
#define RAYTRACER_INTERSECTIONPROPERTIES_H


class Vector3D;
#include "Material.h"

/**
 * @brief Class for storing information about the local properties of a RenderObject at a specific point in space
 */
class IntersectionProperties {
public:
    IntersectionProperties(const Vector3D& n, const Material& mat);
    Vector3D normal;
    Material material;
};


#endif //RAYTRACER_INTERSECTIONPROPERTIES_H