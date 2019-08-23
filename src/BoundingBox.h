#ifndef RAYTRACER_BOUNDINGBOX_H
#define RAYTRACER_BOUNDINGBOX_H

#include "Interval.h"
#include "Ray.h"

class BoundingBox {
public:
    BoundingBox(Interval x, Interval y, Interval z);
    BoundingBox();
    bool isIntersected(const Ray& ray) const;
    Interval intersectionInterval(const Ray& ray) const;
    Vector3D getCenter() const;
    BoundingBox operator+(const BoundingBox& other) const;
    const Interval& operator[](unsigned int index) const;
    friend std::ostream& operator<<(std::ostream& sink, const BoundingBox& b);

private:
    Interval x;
    Interval y;
    Interval z;

    Interval tRange(const Interval& i, double base, double direction) const;
};


#endif //RAYTRACER_BOUNDINGBOX_H
