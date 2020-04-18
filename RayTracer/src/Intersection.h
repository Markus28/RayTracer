#ifndef RAYTRACER_INTERSECTION_H
#define RAYTRACER_INTERSECTION_H


#include "linalg/Vector3D.h"
#include "Material.h"
#include "IntersectionProperties.h"

class RenderObject;


/**
 * @brief Class for storing information about intersection of a Ray and a RenderObject
 */
class Intersection {
public:
    Intersection(const Intersection& other);

    Intersection(const RenderObject* intersect, const double& d);

    Intersection(const RenderObject* intersect, const double& d, const IntersectionProperties& p);

    Intersection();

    bool does_intersect();

    double get_distance() const;

    void set_properties(const IntersectionProperties& p);

    void set_properties(const Material& mat, const Vector3D& normal);

    bool has_properties() const;

    IntersectionProperties get_properties() const;

    friend bool operator<(const Intersection& first, const Intersection& second);

    const RenderObject* get_object() const;

    Intersection& operator=(const Intersection& other);

    ~Intersection();

private:
    const RenderObject* intersect;
    IntersectionProperties* properties;
    double distance;
};


#endif //RAYTRACER_INTERSECTION_H