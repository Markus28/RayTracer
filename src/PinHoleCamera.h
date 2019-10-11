#ifndef RAYTRACER_PINHOLECAMERA_H
#define RAYTRACER_PINHOLECAMERA_H

#include "Camera.h"

/**
 * @brief Implementation of Camera class
 * @see https://en.wikipedia.org/wiki/Camera_obscura
 */
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