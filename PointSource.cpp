#include "PointSource.h"


PointSource::PointSource(Vector3D pt, Vector3D specular, Vector3D diffuse) {
    this->specular = specular;
    this->diffuse = diffuse;
    this->pt = pt;
}

Vector3D PointSource::diffuseComponent(const Vector3D& point) const {
    return diffuse/(point-pt).norm();
}

Vector3D PointSource::specularComponent(const Vector3D& point) const {
    return specular/(point-pt).norm();
}

Vector3D PointSource::getLightDirection(const Vector3D& point) const
{
    return (pt-point)/(pt-point).norm();
}

double PointSource::getDistance(Vector3D point) const{
    return (pt-point).norm();
}