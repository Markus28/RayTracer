#ifndef RAYTRACER_BOUNDEDVOLUME_H
#define RAYTRACER_BOUNDEDVOLUME_H


#include "BoundingBox.h"
#include "RenderObject.h"

/**
 * @brief Abstract class implemented by objects that can be contained in a volume
 */
class BoundedVolume: public RenderObject{
public:
    virtual BoundingBox get_bounds() const = 0;
};


#endif //RAYTRACER_BOUNDEDVOLUME_H
