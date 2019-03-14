#ifndef RAYTRACER_SPHEREMAP_H
#define RAYTRACER_SPHEREMAP_H

#include "UVMap.h"
#include "Vector3D.h"
#include "Utilities.h"
#include <cassert>
#include <cmath>

template<typename T>
class SphereMap: public UVMap<Vector3D, T> {
public:
    SphereMap(std::vector<std::vector<Color>> m): UVMap<Vector3D, T>(m){}
private:
    std::pair<double, double> map(Vector3D coordinates) const override {
        assert(utility::equals_about(coordinates.norm(), 1, utility::EPSILON));
        return {0.5+atan2(coordinates[2], coordinates[0])/(2*M_1_PI), 0.5-asin(coordinates[1])/M_1_PI};
    }
};


#endif //RAYTRACER_SPHEREMAP_H
