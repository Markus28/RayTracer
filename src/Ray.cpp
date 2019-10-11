#include "Ray.h"

Ray::Ray(const Vector3D& pt, const Vector3D& dir) : point(pt), direction(dir){}

/**
 * @brief Offset the base by direction*d
 * @param d The number of directions to walk
 */
void Ray::walk(double d) {
    point += direction*d;
}

/**
 * @brief Offset the base by v
 * @param v The vector to add to the base
 */
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