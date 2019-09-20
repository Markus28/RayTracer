#include <cmath>
#include "SpotLight.h"

SpotLight::SpotLight(Vector3D pt, Vector3D dir, double focus, Vector3D spec, Vector3D diff): position(pt), focus(focus),
                                                                                                    specular(spec), diffuse(diff){
    dir/=dir.norm();
    direction = dir;
}

double SpotLight::getDistance(Vector3D point) const {
    return (point-position).norm();
}

Vector3D SpotLight::getLightDirection(const Vector3D &pt) const {
    Vector3D dir = pt-position;
    dir /= dir.norm();
    return dir;
}

Vector3D SpotLight::diffuseComponent(const Vector3D &pt) const {
    return diffuse*weight(direction*getLightDirection(pt));
}

Vector3D SpotLight::specularComponent(const Vector3D &pt) const {
    return specular*weight(direction*getLightDirection(pt));
}

double SpotLight::weight(double vector_cos) const{
    if(vector_cos<=0){
        return 0;
    }
    vector_cos*=focus;
    return exp(-vector_cos*vector_cos);
}