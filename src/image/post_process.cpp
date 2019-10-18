#include <cmath>
#include "post_process.h"

namespace image{
    /**
     * @brief Apply gamma correction to original
     * @param original The origina image
     * @param gamma The gamma value
     * @return Gamma corrected image
     */
    Image gamma_correct(const Image& original, double gamma, double A){
        Image corrected(original.size(), std::vector<Vector3D>(original[0].size(), Vector3D()));
        for(int i = 0; i<original.size();++i){
            for(int j = 0; j<original[0].size(); ++j){
                corrected[i][j] = Vector3D(pow(original[i][j][0], gamma), pow(original[i][j][1], gamma), pow(original[i][j][2], gamma))*A;
            }
        }

        return corrected;
    }

    Image gamma_correct(const Image& original, double gamma){
        return gamma_correct(original, gamma, 1.0);
    }

    Image max_tone_mapping(const Image& original, double max){
        double m = 0;

        Image corrected(original.size(), std::vector<Vector3D>(original[0].size(), Vector3D()));

        for(unsigned int i = 0; i<original.size();++i){
            for(unsigned int j = 0; j<original[0].size(); ++j){
                m = std::max(std::max(m, original[i][j][0]), std::max(original[i][j][1], original[i][j][2]));
            }
        }

        for(unsigned int i = 0; i<original.size();++i){
            for(unsigned int j = 0; j<original[0].size(); ++j){
                corrected[i][j] = (original[i][j]/m)*max;
            }
        }

        return corrected;
    }

    Image max_tone_mapping(const Image& original){
        return max_tone_mapping(original, 255);
    }

    Image anti_alias(const Image& original, unsigned int window_size){
        unsigned long x_tiles = original.size()/window_size;
        unsigned long y_tiles = original[0].size()/window_size;
        Image corrected(x_tiles, std::vector<Vector3D>(y_tiles, Vector3D()));

        Vector3D tile_sum;

        for(unsigned int i = 0; i < x_tiles; ++i){
            for(unsigned int j=0; j<y_tiles; ++j){
                tile_sum = Vector3D();
                for(unsigned int kx=i*window_size; kx<(i+1)*window_size; ++kx){
                    for(unsigned int ky=j*window_size; ky<(j+1)*window_size; ++ky){
                        tile_sum += original[kx][ky];
                    }
                }
                corrected[i][j] = tile_sum/pow(window_size,2);
            }
        }

        return corrected;
    }
}