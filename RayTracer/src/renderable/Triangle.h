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
    void set_normals(Vector3D n1, Vector3D n2, Vector3D n3);
    void disable_interpolation();
    void enable_interpolation();
    Intersection ray_intersect(const Ray &ray) const override;
    BoundingBox get_bounds() const override;
    IntersectionProperties intersect_properties(const Ray &ray) const override;
    std::ostream& print(std::ostream& sink) const override;
    ~Triangle() = default;

private:
    bool in_triangle(Vector3D p) const;
    Vector3D barycentric_coordinates(const Vector3D& p) const;

    Vector3D p1;
    Vector3D p2;
    Vector3D p3;

    Vector3D n1;
    Vector3D n2;
    Vector3D n3;

    bool interpolate_normal;
    bool normals_set;

    double d;
    Vector3D normal;
    Material material;
    BoundingBox bounds;
    double area2;
};


#endif //RAYTRACER_TRIANGLE_H
