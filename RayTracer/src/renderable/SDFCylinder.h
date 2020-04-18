#ifndef RAYTRACER_SDFCYLINDER_H
#define RAYTRACER_SDFCYLINDER_H

#include "SDFObject.h"


class SDFCylinder: public SDFObject {
public:
    SDFCylinder(Vector3D center, Vector3D axis, double length, double radius, Material mat);
    BoundingBox get_bounds() const override {return bounds;};

private:
    double distance_bound(const Vector3D& pos) const override;
    IntersectionProperties properties_at(const Vector3D& pos) const override;
    BoundingBox bounds;
    Vector3D center;
    Vector3D axis;
    double length;
    double radius;
    Material mat;
};


#endif //RAYTRACER_SDFCYLINDER_H
