#ifndef RAYTRACER_RENDEROBJECT_H
#define RAYTRACER_RENDEROBJECT_H


#include <iostream>
#include "IntersectionProperties.h"

class Intersection;
class Ray;

/**
 * @brief Abstract class for renderable objects
 *
 * Every object that can be rendered by Scene must implement the virtual methods
 *
 */
class RenderObject {
public:
    /**
     * @brief Method to detect intersection of ray and object
     * @param ray The ray in question
     * @return Intersection object containing distance to intersection and pointer to intersected object
     */
    virtual Intersection ray_intersect(const Ray &ray) const = 0;

    /**
     * @brief If ray intersects this object, this method will provide additional Information
     *
     * Note, that even if rayIntersect detected an intersection, this method might not be called.
     * It is called iff the Intersection-Object returned by rayIntersect contains a pointer to this object and no
     * other object in the rendered scene returned an intersection that was closer to the camera.
     *
     * @param ray the ray in question
     * @return IntersectionProperties object containing the surface normal and material information
     */
    virtual IntersectionProperties intersect_properties(const Ray &ray) const = 0;
    virtual std::ostream& print(std::ostream& sink) const = 0;
    virtual ~RenderObject(){};
};


#endif //RAYTRACER_RENDEROBJECT_H