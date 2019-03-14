#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H


#include "Vector3D.h"
#include "Ray.h"
#include "Color.h"

class Light {
public:
    virtual Ray shaddowRay(const Vector3D& pt) const;
    virtual Vector3D specularComponent(const Vector3D& pt) const = 0;
    virtual Vector3D diffuseComponent(const Vector3D& pt) const = 0;
    virtual Vector3D getLightDirection(const Vector3D& pt) const = 0;
    virtual double getDistance(Vector3D point) const = 0;
    virtual ~Light(){};
private:
    Color color;
};


#endif //RAYTRACER_LIGHT_H