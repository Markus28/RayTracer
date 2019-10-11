#ifndef RAYTRACER_OBJFILE_H
#define RAYTRACER_OBJFILE_H

#include <vector>
#include <tuple>
#include "Triangle.h"
#include "BinaryVolumeHierarchy.h"
#include "MTLLib.h"

/**
 * @brief Class for loading wavefront .obj files
 */
class OBJFile {
public:
    OBJFile(const char* file_name, Material mat);
    std::vector<Triangle> getTriangles() const;
    void dump(std::string file_name) const;
    BinaryVolumeHierarchy getBVH();

private:
    std::vector<Triangle> polygons;
    std::vector<Vector3D> vertices;
    MTLLib materials;

};

struct FaceData{
    FaceData(std::istringstream& iss);
    std::vector<Triangle> getTriangles(const std::vector<Vector3D>& vertices, Material mat);

    std::vector<std::vector<int>> data;
};


#endif //RAYTRACER_OBJFILE_H
