#include "Utilities.h"
#include "math.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cassert>

bool utility::equals_about(const double& test, const double& truth, const double& epsilon)
{
        return (test-epsilon<truth && test+epsilon>truth);
}

/**
 * @brief Solves quadratic equation a*x^2+bx+c
 * @param a Quadratic term
 * @param b Linear term
 * @param c Constant term
 * @return Solutions to Equation
 */
utility::QuadraticSolution utility::solveQuadraticEquation(double a, double b, double c) {
        double d = b*b-4*a*c;

        if(d < 0)
        {
                return QuadraticSolution{false, 0, 0};
        }

        d = sqrt(d);

        return QuadraticSolution{true, (-b + d)/(2*a), (-b - d)/(2*a)};
}

void utility::writeImage(std::vector<std::vector<Vector3D>>& im, std::string file_name) { //FROM STACKOVERFLOW: https://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries
    int x, y, r, g, b;
    int w = im.size();
    int h = im[0].size();
    FILE *f;
    unsigned char *img = NULL;
    int filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int

    img = (unsigned char *)malloc(3*w*h);
    memset(img,0,3*w*h);

    for(int i=0; i<w; i++)
    {
        for(int j=0; j<h; j++)
        {
            x=i; y=(h-1)-j;
            im[i][j][0] = std::min(im[i][j][0], 255.0);
            im[i][j][1] = std::min(im[i][j][1], 255.0);
            im[i][j][2] = std::min(im[i][j][2], 255.0);

            r = int(im[i][h-j-1][0]);
            g = int(im[i][h-j-1][1]);
            b = int(im[i][h-j-1][2]);
            img[(x+y*w)*3+2] = (unsigned char)(r);
            img[(x+y*w)*3+1] = (unsigned char)(g);
            img[(x+y*w)*3+0] = (unsigned char)(b);
        }
    }

    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[3] = {0,0,0};

    bmpfileheader[ 2] = (unsigned char)(filesize    );
    bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);

    bmpinfoheader[ 4] = (unsigned char)(       w    );
    bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
    bmpinfoheader[ 6] = (unsigned char)(       w>>16);
    bmpinfoheader[ 7] = (unsigned char)(       w>>24);
    bmpinfoheader[ 8] = (unsigned char)(       h    );
    bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
    bmpinfoheader[10] = (unsigned char)(       h>>16);
    bmpinfoheader[11] = (unsigned char)(       h>>24);

    f = fopen(file_name.c_str(),"wb");
    assert(f!=NULL);
    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);
    for(int i=0; i<h; i++)
    {
        fwrite(img+(w*(h-i-1)*3),3,w,f);
        fwrite(bmppad,1,(4-(w*3)%4)%4,f);
    }

    free(img);
    fclose(f);
}

BoundingBox utility::sumBoundingBoxes(const std::vector<BoundedVolume*>& v)
{
    return sumBoundingBoxes(v.cbegin(), v.cend());
}

BoundingBox utility::sumBoundingBoxes(std::vector<BoundedVolume*>::const_iterator b, std::vector<BoundedVolume*>::const_iterator e)
{
    BoundingBox result;

    for(auto it = b; it!=e; ++it)
    {
        result = result+ (*it)->get_bounds();
    }

    return result;
}

const double& utility::min(const double &x, const double &y, const double &z) {
    return std::min(x, std::min(y, z));
}

const double& utility::max(const double &x, const double &y, const double &z) {
    return std::max(x, std::max(y, z));
}