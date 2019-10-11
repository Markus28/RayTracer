#ifndef RAYTRACER_IMPLICITSURFACE_H
#define RAYTRACER_IMPLICITSURFACE_H


#include "RenderObject.h"
#include "symcpp/SymbolicGraph.h"
#include "Intersection.h"
#include "BoundingBox.h"
#include "BoundedVolume.h"

/**
 * @brief RenderObject for the surface implicitly given by F(x,y,z) = 0
 *
 * @details Objects of this type can be used to render meshless surfaces, eg manifolds. This is, however fairly
 * slow. You might consider meshifying the object by applying the marching-cubes algorithm.
 */
class ImplicitSurface: public BoundedVolume {
public:
    ImplicitSurface(symcpp::SymbolicGraph f, Material m, BoundingBox b);
    Intersection rayIntersect(const Ray& ray) const override;
    IntersectionProperties intersectProperties(const Ray& ray) const override;
    std::ostream& print(std::ostream& sink) const override;
    BoundingBox getBounds() const override;

private:
    /// The function defining the surface by F(x, y, z) = 0
    symcpp::SymbolicGraph F;

    /// The partial derivative by x
    symcpp::SymbolicGraph dxF;

    /// The partial derivative by y
    symcpp::SymbolicGraph dyF;

    ///The partial derivative by z
   symcpp:: SymbolicGraph dzF;

    Material mat;

    BoundingBox bounds;

    /// The maximum number of iterations in Newton method
    double max_iter;

    double epsilon;
};


#endif //RAYTRACER_IMPLICITSURFACE_H
