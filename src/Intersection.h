#ifndef RAYTRACER_INTERSECTION_H
#define RAYTRACER_INTERSECTION_H


class RenderObject;


class Intersection {
public:
    Intersection(const RenderObject* intersect, const double& d);

    Intersection();

    bool doesIntersect();

    double getDistance() const;

    friend bool operator<(const Intersection& first, const Intersection& second);

    const RenderObject* getObject() const;

private:
    const RenderObject* intersect;
    double distance;
};


#endif //RAYTRACER_INTERSECTION_H