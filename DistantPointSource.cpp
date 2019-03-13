#include "DistantPointSource.h"
#include <algorithm>

DistantPointSource::DistantPointSource(Vector3D dir, Vector3D specular, Vector3D diffuse) {
    direction = dir;
    direction /= direction.norm();
    this->diffuse = diffuse;
    this->specular = specular;
}


Vector3D DistantPointSource::getLightDirection(const Vector3D& pt) const{
    return direction;
}

Vector3D DistantPointSource::diffuseComponent(const Vector3D &pt) const {
    return diffuse;
}

Vector3D DistantPointSource::specularComponent(const Vector3D &pt) const {
    return specular;
}

double DistantPointSource::getDistance(Vector3D point) const{
    return std::numeric_limits<double>::infinity();
}