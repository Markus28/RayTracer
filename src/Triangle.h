//
// Created by markus on 2/5/19.
//

#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H

#include "SimplePlane.h"
#include "BoundedVolume.h"

/**
 * @brief A Triangle implementing BoundedVolume, RenderObject
 */
class Triangle: public BoundedVolume {
public:
    Triangle(Vector3D p1, Vector3D p2, Vector3D p3, Material mat);
    Intersection ray_intersect(const Ray &ray) const override;
    BoundingBox get_bounds() const override;
    IntersectionProperties intersect_properties(const Ray &ray) const override;
    std::ostream& print(std::ostream& sink) const override;
    void enable_interpolation();
    void disable_interpolation();
    ~Triangle() = default;

private:
    bool inTriangle(Vector3D p) const;
    Vector3D p1;
    Vector3D p2;
    Vector3D p3;
    Vector3D n1;
    Vector3D n2;
    Vector3D n3;
    double d;
    bool interpolate_normal;
    Vector3D normal;
    Material material;
    BoundingBox bounds;
    double area2;
};


#endif //RAYTRACER_TRIANGLE_H
