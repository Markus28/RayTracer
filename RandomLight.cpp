#include "RandomLight.h"
#include <time.h>
#include <stdlib.h>

RandomLight::RandomLight(Vector3D corner, Vector3D x, Vector3D y, Vector3D specular, Vector3D diffuse) {
    this->corner = corner;
    this->x = x;
    this->y = y;
    this->specular = specular;
    this->diffuse = diffuse;
    this->middle = corner+x*0.5 +y*0.5;
    srand((unsigned int)time(nullptr));
}

Vector3D RandomLight::randomPoint() const {
    return corner+x*rand()/((double) RAND_MAX) + y*rand()/((double) RAND_MAX);
}

Vector3D RandomLight::getLightDirection(const Vector3D &pt) const {
    return (randomPoint()-pt)/(randomPoint()-pt).norm();
}

Vector3D RandomLight::specularComponent(const Vector3D& pt) const {
    return specular/(pt-middle).norm();
}

Vector3D RandomLight::diffuseComponent(const Vector3D& pt) const {
    return diffuse/(pt-middle).norm();
}