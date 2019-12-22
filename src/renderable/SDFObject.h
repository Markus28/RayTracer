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
    explicit SDFObject(): max_iter(75), is_monotonic(false), epsilon(10e-4){};
    explicit SDFObject(bool is_monotonic): max_iter(75), is_monotonic(is_monotonic), epsilon(10e-4) {};
    SDFObject(bool is_monotonic, unsigned int max_iter, double epsilon): max_iter(max_iter),
    is_monotonic(is_monotonic), epsilon(epsilon) {};

    Intersection ray_intersect(const Ray &ray) const override;

    virtual ~SDFObject() = default;

private:
    virtual double distance_bound(const Vector3D& pos) const = 0;

    friend class CSGLeaf;

    unsigned int max_iter;
    bool is_monotonic;
    double epsilon;
};


#endif //RAYTRACER_DISTANCEESTIMATEDOBEJECT_H
