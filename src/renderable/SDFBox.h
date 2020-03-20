#ifndef RAYTRACER_SDFBOX_H
#define RAYTRACER_SDFBOX_H


#include "SDFObject.h"

class SDFBox: public SDFObject {
public:
    SDFBox(Vector3D center, double depth, double length, double height, Material mat);
    BoundingBox get_bounds() const override {return bounds;};

private:
    IntersectionProperties properties_at(const Vector3D& pos) const override;
    double distance_bound(const Vector3D& pos) const override;
    double depth, length, height;
    Vector3D center;
    BoundingBox bounds;
    Material mat;
};


#endif //RAYTRACER_SDFBOX_H
