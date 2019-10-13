#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "Vector3D.h"
#include "Material.h"
#include "BoundedVolume.h"

/**
 * @brief A simple, uniformly textured sphere, implements RenderObject
 */
class SimpleSphere: public BoundedVolume {
public:
    SimpleSphere(Vector3D center, double radius, Material material);
    bool onSphere(Vector3D pt, double epsilon) const;
    IntersectionProperties intersect_properties(const Ray &ray) const override;
    Intersection ray_intersect(const Ray &ray) const override;
    std::ostream& print(std::ostream& sink) const override;
    BoundingBox get_bounds() const override;
    ~SimpleSphere() override = default;

protected:
    Vector3D getNormal(Vector3D pt) const;

private:
    Vector3D center;
    double radius;
    Material material;
    BoundingBox bounds;
};


#endif //RAYTRACER_SPHERE_H