#ifndef RAYTRACER_RANDOMLIGHT_H
#define RAYTRACER_RANDOMLIGHT_H


#include "linalg/Vector3D.h"
#include "Light.h"

class RandomLight: Light {
public:
    RandomLight(Vector3D corner, Vector3D x, Vector3D y, Vector3D specular, Vector3D diffuse);
    Vector3D getLightDirection(const Vector3D& pt) const override;
    Vector3D specularComponent(const Vector3D& pt) const override;
    Vector3D diffuseComponent(const Vector3D& pt) const override;

private:
    Vector3D middle;
    Vector3D x;
    Vector3D y;
    Vector3D corner;
    Vector3D specular;
    Vector3D diffuse;
    Vector3D randomPoint() const;
};


#endif //RAYTRACER_RANDOMLIGHT_H
