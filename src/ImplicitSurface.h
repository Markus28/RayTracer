#ifndef RAYTRACER_IMPLICITSURFACE_H
#define RAYTRACER_IMPLICITSURFACE_H


#include "RenderObject.h"
#include "symcpp/SymbolicGraph.h"
#include "Intersection.h"
#include "BoundingBox.h"
#include "BoundedVolume.h"

class ImplicitSurface: public BoundedVolume {
public:
    ImplicitSurface(SymbolicGraph f, Material m, BoundingBox b);
    Intersection rayIntersect(const Ray& ray) const override;
    IntersectionProperties intersectProperties(const Ray& ray) const override;
    std::ostream& print(std::ostream& sink) const override;
    BoundingBox getBounds() const override;

private:
    SymbolicGraph F;
    SymbolicGraph dxF;
    SymbolicGraph dyF;
    SymbolicGraph dzF;

    Material mat;

    BoundingBox bounds;

    double max_iter, epsilon;
};


#endif //RAYTRACER_IMPLICITSURFACE_H
