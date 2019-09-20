#ifndef RAYTRACER_SPOTLIGHT_H
#define RAYTRACER_SPOTLIGHT_H


#include "Light.h"

class SpotLight: public Light {
public:
    SpotLight(Vector3D pt, Vector3D direction, double focus, Vector3D spec, Vector3D diff);
    Vector3D specularComponent(const Vector3D& pt) const override;
    Vector3D diffuseComponent(const Vector3D& pt) const override;
    Vector3D getLightDirection(const Vector3D& pt) const override;
    double getDistance(Vector3D point) const override;

private:
    double weight(double vector_cos) const;
    Vector3D position, direction, specular, diffuse;
    double focus;
};


#endif //RAYTRACER_SPOTLIGHT_H
