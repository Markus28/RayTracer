#include "Ray.h"

Ray::Ray(const Vector3D& pt, const Vector3D& dir) : point(pt), direction(dir), inverse_direction(1.0/dir[0], 1.0/dir[1], 1.0/dir[2]){
}

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

const Vector3D& Ray::read_direction() const {
    return direction;
}

const Vector3D& Ray::read_inverse_direction() const {
    return inverse_direction;
}

const Vector3D& Ray::read_base() const {
    return point;
}

std::ostream& Ray::print(std::ostream& sink) const{
    sink<< "Base: "<<point<<", Direction: "<<direction<<' ';
    return sink;
}

std::ostream& operator<<(std::ostream& sink, const Ray& ray){
    return ray.print(sink);
}