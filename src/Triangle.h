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
    Intersection rayIntersect(const Ray& ray) const override;
    BoundingBox getBounds() const override;
    IntersectionProperties intersectProperties(const Ray& ray) const override;
    std::ostream& print(std::ostream& sink) const override;
    ~Triangle() = default;

private:
    bool inTriangle(Vector3D p) const;
    Vector3D p1;
    Vector3D p2;
    Vector3D p3;
    double d;
    Vector3D normal;
    Material material;
    BoundingBox bounds;
    double area2;
};


#endif //RAYTRACER_TRIANGLE_H
