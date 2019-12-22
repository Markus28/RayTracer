#include "SDFObject.h"
#include "../Intersection.h"

Intersection SDFObject::ray_intersect(const Ray &ray) const {
    Interval intersection_interval = get_bounds().intersection_interval(ray);
    if(!intersection_interval.containsPositive())
        return {};

    double t = intersection_interval.getMin();
    double last_distance = distance_bound(ray.read_base()+ray.read_direction()*t);
    double current_distance = last_distance;
    unsigned int counter = 0;

    while(counter<max_iter && (!is_monotonic || last_distance<=current_distance) && t<intersection_interval.getMax() &&
    std::abs(current_distance)>epsilon){
        t+=current_distance;
        last_distance = current_distance;
        current_distance = distance_bound(ray.read_base()+ray.read_direction()*t);
    }

    if(std::abs(current_distance)<=epsilon){
        return {};  //TODO
    }

    return {};
}
