#include "Intersection.h"


Intersection::Intersection(const RenderObject* intersect, const double& d)
{
    this->intersect = intersect;
    this->distance = d;
}

Intersection::Intersection()
{
    this->intersect = nullptr;
    this->distance = -1;
}

bool operator<(const Intersection& first, const Intersection& second)
{
    return first.distance>0 && (second.distance<0 || first.distance<second.distance);
}

bool Intersection::doesIntersect() {
    return distance>0;
}

double Intersection::getDistance() const {
    return distance;
}

const RenderObject* Intersection::getObject() const {
    return intersect;
}