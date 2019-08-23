#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include <vector>
#include <string>
#include "Ray.h"


using Image = std::vector<std::vector<Vector3D>>;

class Camera {
public:

    void resetRay();

    virtual Ray currentRay() const = 0;

    bool endRay() const;

    void setRay(Vector3D c);

    void writeFile(std::string file_name) const;

    void advanceRay();

    virtual ~Camera(){};

protected:
    Image image;
    unsigned int width, height;
    unsigned int x, y;
    virtual Image postProcess() const = 0;
};


#endif //RAYTRACER_CAMERA_H