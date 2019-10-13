#include "BoundingBox.h"
#include <algorithm>

BoundingBox::BoundingBox(Interval x, Interval y, Interval z): x(x), y(y), z(z) {}

BoundingBox::BoundingBox() {
    x  = {};
    y = {};
    z = {};
}

bool BoundingBox::is_intersected(const Ray &ray) const {
    Interval t_range = intersection_interval(ray);
    return t_range.containsPositive();
}

/**
 * @brief Returns which part of ray lies inside the box
 *
 * @details If the ray is given as gamma(t)=b+t*v where b is the base vector and v is the direction,
 * this function will return the interval that contains all t such that gamma(t) lies in the cuboid.
 *
 * @param ray The ray intersecting the box
 * @return The interval of arguments t for which ray.readBase()+ray.readDirection()*t is inside the box.
 */
Interval BoundingBox::intersection_interval(const Ray &ray) const
{
    Interval range = t_range(x, ray.read_base()[0], ray.read_direction()[0]);
    range = range* t_range(y, ray.read_base()[1], ray.read_direction()[1]);
    range = range* t_range(z, ray.read_base()[2], ray.read_direction()[2]);
    return range;
}

Interval BoundingBox::t_range(const Interval &i, double base, double direction) const {
    if(i.isEmpty() || (direction==0 && !i.contains(base)))
    {
        return {};
    }

    if(direction==0 && i.contains(base)) {
        return {-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()};
    }

    double a = (i.getMax()-base)/direction;
    double b = (i.getMin()-base)/direction;

    return {std::min(a, b), std::max(a,b)};
}

BoundingBox BoundingBox::operator+(const BoundingBox &other) const {
    return {x+other.x, y+other.y, z+other.z};
}

Vector3D BoundingBox::get_center() const{
    return {x.getCenter(), y.getCenter(), z.getCenter()};
}

const Interval& BoundingBox::operator[](unsigned int index) const{
    switch(index)
    {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw("Index out of bounds...");
    }
}

std::ostream& operator<<(std::ostream& sink, const BoundingBox& b){
    return sink<< "X: "<<b.x<<", Y: "<<b.y<<", Z: "<<b.z;
}