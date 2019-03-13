#ifndef RAYTRACER_DISTANTPOINT_H
#define RAYTRACER_DISTANTPOINT_H


#include "Light.h"

class DistantPointSource: public Light {
public:
    DistantPointSource(Vector3D dir,  Vector3D specular, Vector3D diffuse);
    Vector3D diffuseComponent(const Vector3D& point) const override;
    Vector3D specularComponent(const Vector3D& point) const override;
    Vector3D getLightDirection(const Vector3D& pt) const override;
    double getDistance(Vector3D point) const override;

private:
    Vector3D direction;
    Vector3D specular;
    Vector3D diffuse;
};


#endif //RAYTRACER_DISTANTPOINT_H