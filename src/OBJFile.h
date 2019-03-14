#ifndef RAYTRACER_OBJFILE_H
#define RAYTRACER_OBJFILE_H

#include <vector>
#include "Triangle.h"

class OBJFile {
public:
    OBJFile(const char* file_name, Material mat);
    std::vector<Triangle> getTriangles() const;
    void dump(std::string file_name) const;

private:
    std::vector<Triangle> polygons;
    std::vector<Vector3D> vertices;
};


#endif //RAYTRACER_OBJFILE_H
