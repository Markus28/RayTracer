#ifndef RAYTRACER_DOWNSAMPLINGCAM_H
#define RAYTRACER_DOWNSAMPLINGCAM_H

#include "PinHoleCamera.h"

class DownSamplingCam: public PinHoleCamera {
public:
    DownSamplingCam(Vector3D position, Vector3D up, Vector3D right, unsigned int width, unsigned int height, double width_angle,
                    unsigned int sp);

protected:
    Image postProcess() const override;

private:
    unsigned int sub_pixel;
};


#endif //RAYTRACER_DOWNSAMPLINGCAM_H
