#ifndef RAYTRACER_POINTSOURCE_H
#define RAYTRACER_POINTSOURCE_H

#include "Light.h"

class PointSource: public Light {
public:
    PointSource(Vector3D pt, Vector3D specular, Vector3D diffuse);
    Vector3D diffuseComponent(const Vector3D& point) const override;
    Vector3D specularComponent(const Vector3D& point) const override;
    Vector3D getLightDirection(const Vector3D& pt) const override;
    double getDistance(Vector3D point) const override;

private:
    Vector3D pt;
    Vector3D diffuse;
    Vector3D specular;
};


#endif //RAYTRACER_POINTSOURCE_H
