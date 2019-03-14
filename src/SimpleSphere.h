#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "Vector3D.h"
#include "Material.h"
#include "BoundedVolume.h"

class SimpleSphere: public BoundedVolume {
public:
    SimpleSphere(Vector3D center, double radius, Material material);
    bool onSphere(Vector3D pt, double epsilon) const;
    IntersectionProperties intersectProperties(const Ray& ray) const override;
    Intersection rayIntersect(const Ray& ray) const override;
    std::ostream& print(std::ostream& sink) const override;
    BoundingBox getBounds() const override;
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