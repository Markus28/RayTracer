#include "DownSamplingCam.h"
#include "PinHoleCamera.h"

DownSamplingCam::DownSamplingCam(Vector3D position, Vector3D up, Vector3D right, unsigned int width,
                                 unsigned int height, double width_angle, unsigned int sp): PinHoleCamera(position, up, right, width*sp, height*sp, width_angle) {
    sub_pixel = sp;
}

Image DownSamplingCam::postProcess() const {
    Image result(width/sub_pixel, (std::vector<Color>(height/sub_pixel)));

    for(unsigned int x = 0; x<width; ++x)
    {
        for(unsigned int y = 0; y<height; ++y)
        {
            result[x/sub_pixel][y/sub_pixel] += image[x][y].power(2);
        }
    }

    for(unsigned int x = 0; x<width/sub_pixel; ++x)
    {
        for(unsigned int y = 0; y<height/sub_pixel; ++y)
        {
            result[x][y] = result[x][y].power(0.5);
            result[x][y]/=sub_pixel;
        }
    }

    return result;
}