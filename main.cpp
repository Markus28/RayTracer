#include <iostream>
#include <vector>
#include <chrono>
#include "Utilities.h"
#include "Scene.h"
#include "PinHoleCamera.h"
#include "DistantPointSource.h"
#include "SimplePlane.h"
#include "SimpleSphere.h"
#include "Triangle.h"
#include "DownSamplingCam.h"
#include "BinaryVolumeHierarchy.h"
#include "OBJFile.h"
#include "RandomLight.h"
#include "PointSource.h"

void geo(){
    std::vector<RenderObject*> objs;
    std::vector<BoundedVolume*> bs;
    std::vector<Light*> lights;

    PinHoleCamera cam = PinHoleCamera(Vector3D(0,0,0), Vector3D(0,0,1), Vector3D(0,1,0), 600, 450, 0.8);
    DistantPointSource light = DistantPointSource(Vector3D(1,1,1), Vector3D(0.5,0.5,0.5), Vector3D(1,1,1));
    lights.push_back(&light);

    SimplePlane p = SimplePlane(Vector3D(0,0,-1), Vector3D(0,0,1), Material(Vector3D(1,1,1), Vector3D(1,1,1), Vector3D(1,1,1), Vector3D(6,6,6), Color(50,50,50), 0, 0, 1.0));
    Triangle t = Triangle(Vector3D(-4,1,-0.5), Vector3D(-4,1.5,-0.5), Vector3D(-4,1.25,-0.25), Material(Vector3D(1,1,1), Vector3D(1,1,1), Vector3D(1,1,1), Vector3D(6,6,6), Color(150,0,0), 0, 0, 1.0));

    SimplePlane p2 = SimplePlane(Vector3D(0,-1.6,-1), Vector3D(0,1,0), Material(Vector3D(1,1,1), Vector3D(1,1,1), Vector3D(1,1,1), Vector3D(1,1,1), Color(20,20,20), 0, 0, 1.0));
    SimpleSphere s = SimpleSphere(Vector3D(-10,1.5,0), 1,  Material(Vector3D(0.5,0.5,0.5), Vector3D(1,1,1), Vector3D(1,1,1), Vector3D(4,4,4), Color(0,100,0), 0, 0, 1.0));
    SimpleSphere s2 = SimpleSphere(Vector3D(-5,1.23,-0.9), 0.1,  Material(Vector3D(3,3,3), Vector3D(1,1,1), Vector3D(0.5,0.5,0.5), Vector3D(8,8,8), Color(5,50,100), 0, 0, 1.0));
    SimpleSphere s3 = SimpleSphere(Vector3D(-5,0.1,-0.7), 0.3,  Material(Vector3D(4,4,4), Vector3D(1,1,1), Vector3D(0.5,0.5,0.5), Vector3D(9,9,9), Color(50,50,0), 0, 0, 1.0));
    SimpleSphere s4 = SimpleSphere(Vector3D(-7,0.7,1.2), 0.5,  Material(Vector3D(1,1,1), Vector3D(0.5,0.5,0.5), Vector3D(0.5,0.5,0.5), Vector3D(1,1,1), Color(0,20,50), 0, 0.8, 1.0));
    SimpleSphere s5 = SimpleSphere(Vector3D(-8,-0.5,-0.6), 0.4,  Material(Vector3D(1,1,1), Vector3D(0.5,0.5,0.5), Vector3D(0.5,0.5,0.5), Vector3D(1,1,1), Color(0,20,50), 0, 0.8, 1.0));


    objs.push_back(&s);
    objs.push_back(&t);
    objs.push_back(&s2);
    objs.push_back(&s5);
    objs.push_back(&s4);
    objs.push_back(&s3);
    objs.push_back(&p);
    objs.push_back(&p2);

    Scene my_scene = Scene(objs, lights, &cam, Color(0,0,250), Vector3D(0.2,0.2,0.2));

    auto start = std::chrono::high_resolution_clock::now();

    my_scene.render(3);

    auto stop = std::chrono::high_resolution_clock::now();

    std::cout<<std::endl<<"It took "<<std::chrono::duration_cast<std::chrono::seconds>(stop - start).count()<<" seconds."<<std::endl;
    cam.writeFile("./geo.bmp");
}

void duck()
{
    std::vector<RenderObject*> objs;
    std::vector<BoundedVolume*> bs;
    std::vector<Light*> lights;
    std::vector<BoundedVolume*> trs;


    DistantPointSource light = DistantPointSource(Vector3D(2,-1,2), Vector3D(0.5,0.5,0.5), Vector3D(1,1,1));

    OBJFile f = OBJFile("duck.obj", Material(Vector3D(3,3,3), Vector3D(1,1,1), Vector3D(0.5,0.5,0.5), Vector3D(8,8,8), Color(5,50,100), 0, 0, 1.0));
    std::vector<Triangle> ts = f.getTriangles();


    for(Triangle& t: ts)
    {
        trs.push_back(&t);
        //objs.push_back(&t);
    }

    BinaryVolumeHierarchy bvh = BinaryVolumeHierarchy(trs.begin(), trs.end());

    objs.push_back(&bvh);

    PinHoleCamera cam = PinHoleCamera(Vector3D(4,-1,2), Vector3D(0,1,0), Vector3D(1,0,0), 1000, 400, 0.8);

    lights.push_back(&light);
    Scene my_scene = Scene(objs, lights, &cam, Color(0,0,250), Vector3D(0.2,0.2,0.2));

    auto start = std::chrono::high_resolution_clock::now();

    my_scene.render(3);

    auto stop = std::chrono::high_resolution_clock::now();

    std::cout<<std::endl<< "It took " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count()<<" seconds."<<std::endl;
    cam.writeFile("./duck.bmp");
}

void dragon()
{
    std::vector<RenderObject*> objs;
    std::vector<BoundedVolume*> bs;
    std::vector<Light*> lights;
    std::vector<BoundedVolume*> trs;


    DistantPointSource light = DistantPointSource(Vector3D(1,1,1), Vector3D(0.5,0.5,0.5), Vector3D(1,1,1));


    OBJFile f = OBJFile("dragon.obj", Material(Vector3D(3,3,3), Vector3D(1,1,1), Vector3D(0.5,0.5,0.5), Vector3D(8,8,8), Color(5,50,100), 0, 0, 1.0));
    std::vector<Triangle> ts = f.getTriangles();


    for(Triangle& t: ts)
    {
        trs.push_back(&t);
    }

    BinaryVolumeHierarchy bvh = BinaryVolumeHierarchy(trs.begin(), trs.end());

    objs.push_back(&bvh);

    PinHoleCamera cam = PinHoleCamera(Vector3D(0,5,20), Vector3D(0,1,0), Vector3D(1,0,0), 900, 650, 0.8);

    lights.push_back(&light);
    Scene my_scene = Scene(objs, lights, &cam, Color(200,200,200), Vector3D(0.2,0.2,0.2));

    auto start = std::chrono::high_resolution_clock::now();

    my_scene.render(3);

    auto stop = std::chrono::high_resolution_clock::now();

    std::cout<<std::endl<< "It took " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count()<<" seconds."<<std::endl;
    cam.writeFile("./dragon.bmp");
}


void cornell()
{
    std::vector<RenderObject*> objs;
    std::vector<Light*> lights;
    PinHoleCamera cam = PinHoleCamera(Vector3D(6,0,1), Vector3D(0,0,1), Vector3D(0,1,0), 600, 450, 0.8);

    //RandomLight light = RandomLight({2,-0.5,3}, {0,1,0},{-1,0,0}, {1,1,1}, {1,1,1});
    PointSource light = PointSource({-1,0,2}, {0.7,0.7,0.7}, {1,1,1});

    SimplePlane left = SimplePlane({0,-3,0}, {0,1,0}, {{0,0.5,0}, {0,1,0}, {0,1,0}, {0.2,0.2,0.2}, {0, 255,0}, 0,0,0});
    SimplePlane right = SimplePlane({0,3,0}, {0,-1,0}, {{0.5,0,0}, {1,0,0}, {1,0,0}, {0.2,0.2,0.2}, {255, 0,0}, 0,0,0});
    SimplePlane ceiling = SimplePlane({0,0,3}, {0,0,-1}, {{1,1,1}, {1,1,1}, {1,1,1}, {0.2,0.2,0.2}, {255,255,255}, 0,0,0});
    SimplePlane floor = SimplePlane({0,0,-1}, {0,0,1}, {{1,1,1}, {1,1,1}, {1,1,1}, {0.2,0.2,0.2}, {255,255,255}, 0,0,0});
    SimplePlane back = SimplePlane({-5,0,0}, {1,0,0}, {{1,1,1}, {1,1,1}, {1,1,1}, {0.2,0.2,0.2}, {255,255,255}, 0,0,0});

    objs.push_back(&left);
    objs.push_back(&right);
    objs.push_back(&ceiling);
    objs.push_back(&floor);
    objs.push_back(&back);

    Scene my_scene = Scene(objs, lights, &cam, Color(0,0,250), Vector3D(0.2,0.2,0.2));

    auto start = std::chrono::high_resolution_clock::now();

    my_scene.render(3);

    auto stop = std::chrono::high_resolution_clock::now();

    std::cout<<std::endl<<"It took "<<std::chrono::duration_cast<std::chrono::seconds>(stop - start).count()<<" seconds."<<std::endl;
    cam.writeFile("./cornell.bmp");
}

int main() {
    duck();
    dragon();
    geo();
    cornell();
    return 0;

}