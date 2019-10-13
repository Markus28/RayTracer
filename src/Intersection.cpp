#include <cassert>
#include "Intersection.h"


Intersection::Intersection(const RenderObject* intersect, const double& d)
{
    this->intersect = intersect;
    this->distance = d;
    properties = nullptr;
}

Intersection::Intersection()
{
    intersect = nullptr;
    distance = -1;
    properties = nullptr;
}

Intersection::Intersection(const Intersection &other) {
    if(other.has_properties()){
        properties = new IntersectionProperties(other.get_properties());
    }
    else{
        properties = nullptr;
    }

    intersect = other.intersect;
    distance = other.distance;
}

Intersection::Intersection(const RenderObject *intersect, const double &d, const IntersectionProperties &p) {
    this->intersect = intersect;
    this->distance = d;
    properties = nullptr;
    set_properties(p);
}

/**
 * @brief RenderObject might choose to store information about the intersection here
 * @param p Properties of the intersection
 */
void Intersection::set_properties(const IntersectionProperties &p) {
    assert(does_intersect());
    delete properties;
    properties = new IntersectionProperties(p);
}


/**
 * @brief RenderObject might choose to store information about the intersection here
 * @details Setting the properties using this method will allow Scene to avoid calling intersect_properties of Renderobject.
 * This might be desired if the surface normal/materials are calculated by RenderObjects ray_intersect already.
 * @param mat The material properties at the intersection point
 * @param normal The surface normal at the intersection point
 */
void Intersection::set_properties(const Material &mat, const Vector3D &normal) {
    assert(does_intersect());
    delete properties;
    properties = new IntersectionProperties(normal, mat);
}

/**
 * @return True if information about intersection properties are stored in this object
 */
bool Intersection::has_properties() const {
    return properties!=nullptr;
}

/**
 * @brief Returns IntersectionProperties if they are stored here. Otherwise this method throws an exception
 * @details Before calling this method you might want to call has_properties
 * @return Information about the intersection if these properties were stored here
 */
IntersectionProperties Intersection::get_properties() const {
    if(properties== nullptr){
        throw "Property is not set!";
    }

    return *properties;
}

/**
 * @brief Decides which intersection is closer to the camera
 * @param first The first intersection
 * @param second The second intersection
 * @return True if first is closer to the camera than second
 */
bool operator<(const Intersection& first, const Intersection& second)
{
    return first.distance>0 && (second.distance<0 || first.distance<second.distance);
}


bool Intersection::does_intersect() {
    return distance>0;
}

double Intersection::get_distance() const {
    return distance;
}

const RenderObject* Intersection::get_object() const {
    return intersect;
}

Intersection& Intersection::operator=(const Intersection &other) {
    delete properties;
    if(other.has_properties()){
        properties = new IntersectionProperties(other.get_properties());
    }
    else{
        properties = nullptr;
    }
    intersect = other.intersect;
    distance = other.distance;
    return *this;
}

/**
 * @brief Destructor of Intersection
 * @details Note, that we only have to delete properties. It is not Intersection's responsibility to clean up intersect.
 * In fact, chances are intersect is not even on the heap.
 */
Intersection::~Intersection() {
    delete properties;
}