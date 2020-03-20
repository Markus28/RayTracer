#include <cassert>
#include "SDFObject.h"
#include "../Intersection.h"

Intersection SDFObject::ray_intersect(const Ray &ray) const {
    Interval intersection_interval = get_bounds().intersection_interval(ray);

    if(!intersection_interval.containsPositive())
        return {};

    double t = std::max(0.0, intersection_interval.getMin()-epsilon);
    double current_distance = distance_bound(ray.read_base()+ray.read_direction()*t);


    if(current_distance<0)
        return {};

    unsigned int counter = 0;

    while(counter<max_iter && t<intersection_interval.getMax() && (current_distance > epsilon  || counter<5)){
        t += current_distance;
        current_distance = distance_bound(ray.read_base()+ray.read_direction()*t);
        ++counter;
    }

    if(current_distance<=epsilon){
        return {this, t, properties_at(ray.read_base()+ray.read_direction()*t)};
    }

    return {};
}

IntersectionProperties SDFObject::intersect_properties(const Ray& ray) const{
    return ray_intersect(ray).get_properties();
}

std::ostream& SDFObject::print(std::ostream& sink) const{
    return sink<<"A SDF-Sphere"<<std::endl;
}