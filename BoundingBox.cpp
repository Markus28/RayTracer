#include "BoundingBox.h"
#include <algorithm>

BoundingBox::BoundingBox(Interval x, Interval y, Interval z): x(x), y(y), z(z) {}

BoundingBox::BoundingBox() {
    x  = {};
    y = {};
    z = {};
}

bool BoundingBox::isIntersected(const Ray& ray) const {
    Interval t_range = tRange(x, ray.readBase()[0], ray.readDirection()[0]);
    t_range = t_range*tRange(y, ray.readBase()[1], ray.readDirection()[1]);
    t_range = t_range*tRange(z, ray.readBase()[2], ray.readDirection()[2]);
    return t_range.containsPositive();
}

Interval BoundingBox::tRange(const Interval& i, double base, double direction) const {
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

Vector3D BoundingBox::getCenter() const{
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