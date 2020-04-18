#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H


#include "../linalg/Vector3D.h"
#include "../Ray.h"
#include "../Material.h"
#include "RenderObject.h"

/**
 * @brief An infinite plane
 */
class SimplePlane: public RenderObject {
public:
    SimplePlane(const Vector3D& pt, const Vector3D& norm, const Material& mat);
    Intersection ray_intersect(const Ray &ray) const override;
    IntersectionProperties intersect_properties(const Ray &ray) const override;
    std::ostream& print(std::ostream& sink) const override;
    virtual bool onPlane(const Vector3D& point, const double& epsilon) const;
    ~SimplePlane() override = default;

private:
    double d;
    Vector3D normal;
    Material material;
};


#endif //RAYTRACER_PLANE_H