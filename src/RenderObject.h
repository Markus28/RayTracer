#ifndef RAYTRACER_RENDEROBJECT_H
#define RAYTRACER_RENDEROBJECT_H


#include <iostream>
#include "IntersectionProperties.h"

class Intersection;
class Ray;

class RenderObject {
public:
    virtual Intersection rayIntersect(const Ray& ray) const = 0;
    virtual IntersectionProperties intersectProperties(const Ray& ray) const = 0;
    virtual std::ostream& print(std::ostream& sink) const = 0;
    virtual ~RenderObject(){};
};


#endif //RAYTRACER_RENDEROBJECT_H