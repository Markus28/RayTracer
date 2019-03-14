#ifndef RAYTRACER_BOUNDEDVOLUME_H
#define RAYTRACER_BOUNDEDVOLUME_H


#include "BoundingBox.h"
#include "RenderObject.h"

class BoundedVolume: public RenderObject{
public:
    virtual BoundingBox getBounds() const = 0;
};


#endif //RAYTRACER_BOUNDEDVOLUME_H
