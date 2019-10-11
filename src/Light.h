#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H


#include "Vector3D.h"
#include "Ray.h"

/**
 * @brief Abstract class for lights used in Scene
 */
class Light {
public:
    /**
     * @brief This method is called to construct shaddow rays for this light-source
     * @param pt A point in 3D-Space at which the shaddow-ray originates
     * @return A ray originating in pt, pointing at this light
     */
    virtual Ray shaddowRay(const Vector3D& pt) const;
    virtual Vector3D specularComponent(const Vector3D& pt) const = 0;
    virtual Vector3D diffuseComponent(const Vector3D& pt) const = 0;
    virtual Vector3D getLightDirection(const Vector3D& pt) const = 0;
    virtual double getDistance(Vector3D point) const = 0;
    virtual ~Light(){};
private:
    Vector3D color;
};


#endif //RAYTRACER_LIGHT_H