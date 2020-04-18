#ifndef RAYTRACER_DISTANCEESTIMATEDOBEJECT_H
#define RAYTRACER_DISTANCEESTIMATEDOBEJECT_H


#include "BoundedVolume.h"

/**
 * @brief Interface for an object that can be Sphere-Marched
 *
 * Objects which implement this interface must provide the distance_bound function, which returns a lower bound on
 * the distance from the object. Using this information the sphere-marching algorithm is used to compute an
 * intersection with the object.
 */
class SDFObject: public BoundedVolume {
public:
    explicit SDFObject(): max_iter(250), epsilon(1e-9){};
    SDFObject(unsigned int max_iter, double epsilon): max_iter(max_iter), epsilon(epsilon) {};
    Intersection ray_intersect(const Ray &ray) const override;
    IntersectionProperties intersect_properties(const Ray& ray) const override;
    std::ostream& print(std::ostream& sink) const override;
    virtual ~SDFObject() = default;

private:
    virtual double distance_bound(const Vector3D& pos) const = 0;
    virtual IntersectionProperties properties_at(const Vector3D& pos) const = 0;

    friend class CSGLeaf;

    unsigned int max_iter;
    double epsilon;
};


#endif //RAYTRACER_DISTANCEESTIMATEDOBEJECT_H
