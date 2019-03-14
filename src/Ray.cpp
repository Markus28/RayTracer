#include "Ray.h"

Ray::Ray(const Vector3D& pt, const Vector3D& dir) : point(pt), direction(dir){}


void Ray::walk(double d) {
    point += direction*d;
}

void Ray::offset(const Vector3D &v) {
    point += v;
}

const Vector3D& Ray::readDirection() const {
    return direction;
}

const Vector3D& Ray::readBase() const {
    return point;
}

std::ostream& Ray::print(std::ostream& sink) const{
    sink<< "Base: "<<point<<", Direction: "<<direction<<' ';
}

std::ostream& operator<<(std::ostream& sink, const Ray& ray){
    return ray.print(sink);
}