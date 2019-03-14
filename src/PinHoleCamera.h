#ifndef RAYTRACER_PINHOLECAMERA_H
#define RAYTRACER_PINHOLECAMERA_H

#include "Camera.h"

class PinHoleCamera: public Camera {
public:
    PinHoleCamera(Vector3D position, Vector3D up, Vector3D right, unsigned int width, unsigned int height, double width_angle);
    Ray currentRay() const override;

private:
    Vector3D position;
    Vector3D up;
    Vector3D right;
    Vector3D forward;

protected:
    Image postProcess() const override;
};


#endif //RAYTRACER_PINHOLECAMERA_H