#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>
#include "Utilities.h"
#include "Scene.h"
#include "camera/PinHoleCamera.h"
#include "DistantPointSource.h"
#include "renderable/SimplePlane.h"
#include "renderable/SimpleSphere.h"
#include "renderable/Triangle.h"
#include "renderable/BinaryVolumeHierarchy.h"
#include "OBJFile.h"
#include "RandomLight.h"
#include "PointSource.h"
#include "MTLLib.h"
#include "symcpp/SymbolicGraph.h"
#include "symcpp/Exponential.h"
#include "symcpp/Logarithm.h"
#include "symcpp/Power.h"
#include "symcpp/Sine.h"
#include "renderable/ImplicitSurface.h"

using namespace symcpp;

void geo(){
    std::vector<RenderObject*> objs;
    std::vector<Light*> lights;

    camera::PinHoleCamera cam = camera::PinHoleCamera(Vector3D(0,0,0), Vector3D(0,0,1), Vector3D(0,1,0), 2400, 1800, 0.8);

    DistantPointSource light = DistantPointSource(Vector3D(1,1,1), Vector3D(20,20,20), Vector3D(40,40,40));
    lights.push_back(&light);

    SimplePlane p = SimplePlane(Vector3D(0,0,-1), Vector3D(0,0,1), Material(Vector3D(1,1,1), Vector3D(1,1,1), Vector3D(1,1,1), Vector3D(6,6,6), 0, 0, 1.0));

    SimplePlane p2 = SimplePlane(Vector3D(0,-1.6,-1), Vector3D(0,3,0), Material(Vector3D(0.1,3,0.3), Vector3D(0.1,3,0.3), Vector3D(0.1,3,0.3), Vector3D(1,1,1), 0, 0, 1.0));

    SimpleSphere s = SimpleSphere(Vector3D(-10,1.5,0), 1,  Material(Vector3D(1,0.2,0.2), Vector3D(4,0.1,0.2), Vector3D(4,0.1,0.2), Vector3D(4,4,4), 0, 0, 1.0));
    SimpleSphere s2 = SimpleSphere(Vector3D(-5,1.23,-0.9), 0.1,  Material(Vector3D(1,1,5), Vector3D(0.1,0.3,4), Vector3D(0.5,0.5,3), Vector3D(8,8,8), 0, 0, 1.0));
    SimpleSphere s3 = SimpleSphere(Vector3D(-3.4,0.1,-0.7), 0.3,  Material(Vector3D(1,1,1), Vector3D(0.1,0.1,0.1), Vector3D(0.1,0.1,0.1), Vector3D(9,9,9), 0.9, 0.1, 0.625));
    SimpleSphere s4 = SimpleSphere(Vector3D(-7,0.7,1.2), 0.5,  Material(Vector3D(1,1,1), Vector3D(0.5,0.5,0.5), Vector3D(0.5,0.5,0.5), Vector3D(1,1,1), 0, 0.8, 1.0));
    SimpleSphere s5 = SimpleSphere(Vector3D(-8,-0.5,-0.6), 0.4,  Material(Vector3D(1,1,1), Vector3D(0.5,0.5,0.5), Vector3D(0.5,0.5,0.5), Vector3D(1,1,1), 0, 0.8, 1.0));


    objs.push_back(&s);
    objs.push_back(&s2);
    objs.push_back(&s5);
    objs.push_back(&s4);
    objs.push_back(&s3);
    objs.push_back(&p);
    objs.push_back(&p2);

    std::cout<< "Rendering" <<std::endl;

    Scene my_scene = Scene(objs, lights, &cam, Vector3D(0,0,250), Vector3D(0.2,0.2,0.2));

    auto start = std::chrono::high_resolution_clock::now();

    my_scene.render(4);

    auto stop = std::chrono::high_resolution_clock::now();

    std::cout<<std::endl<<"It took "<<std::chrono::duration_cast<std::chrono::seconds>(stop - start).count()<<" seconds."<<std::endl;
    cam.write_file("./geo.bmp");
}

void dragon()
{
    std::vector<RenderObject*> objs;
    std::vector<Light*> lights;


    DistantPointSource light = DistantPointSource(Vector3D(1,1,1), Vector3D(70,70,70), Vector3D(50,50,50));


    OBJFile f = OBJFile("dragon.obj", Material(Vector3D(3,3,3), Vector3D(1,1,1), Vector3D(0.5,0.5,0.5), Vector3D(8,8,8), 0, 0, 1.0));

    BinaryVolumeHierarchy bvh = f.getBVH();
    objs.push_back(&bvh);

    camera::PinHoleCamera cam = camera::PinHoleCamera(Vector3D(0,5,20), Vector3D(0,1,0), Vector3D(1,0,0), 2000, 1400, 0.8);

    lights.push_back(&light);
    Scene my_scene = Scene(objs, lights, &cam, Vector3D(200,200,200), Vector3D(0.2,0.2,0.2));

    auto start = std::chrono::high_resolution_clock::now();

    my_scene.render(3);

    auto stop = std::chrono::high_resolution_clock::now();

    std::cout<<std::endl<< "It took " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count()<<" seconds."<<std::endl;
    cam.write_file("./dragon.bmp");
}

void car()
{
    std::vector<RenderObject*> objs;
    std::vector<Light*> lights;

    //DistantPointSource light = DistantPointSource(Vector3D(-3,1,1), Vector3D(300,300,300), Vector3D(500,500,500));
    PointSource light1 = PointSource(Vector3D(-6, 10, 4), Vector3D(4000, 4000, 4000), Vector3D(1000, 1000, 1000));
    PointSource light2 = PointSource(Vector3D(0, 0.9, 0.5), Vector3D(350, 350, 350), Vector3D(350, 350, 350));

    std::cout<<"Loading obj file..."<<std::endl;
    OBJFile f = OBJFile("sportsCar.obj", Material(Vector3D(3,3,3), Vector3D(1,1,1), Vector3D(0.5,0.5,0.5), Vector3D(8,8,8), 0, 0, 1.0));
    std::cout<<"Done..."<<std::endl<<std::endl;

    std::cout<<"Creating BVH..."<<std::endl;
    BinaryVolumeHierarchy bvh = f.getBVH();
    std::cout<<bvh.get_deepest_branch()<<std::endl;
    std::cout<<"Done..."<<std::endl<<std::endl;
    SimplePlane floor = SimplePlane(Vector3D(0,0,0), Vector3D(0,1,0), Material(Vector3D(0.5,0.5,0.5), Vector3D(0.4,0.4,0.4), Vector3D(0.1,0.1,0.1), Vector3D(1,1,1), 0, 0, 1.0));

    objs.push_back(&floor);
    objs.push_back(&bvh);

    camera::PinHoleCamera cam = camera::PinHoleCamera(Vector3D(-6,2.5,0), Vector3D(0.377,0.925,0), Vector3D(0,0,1), 1200, 650, 0.8);
    lights.push_back(&light1);
    lights.push_back(&light2);
    Scene my_scene = Scene(objs, lights, &cam, Vector3D(200,200,200), Vector3D(300,300,300));

    auto start = std::chrono::high_resolution_clock::now();

    std::cout<< "Rendering..."<<std::endl;
    my_scene.render(3);
    std::cout<<"Done..."<<std::endl;

    auto stop = std::chrono::high_resolution_clock::now();

    std::cout<<std::endl<< "It took " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count()<<" seconds."<<std::endl;
    cam.write_file("./car.bmp");
}

void implicit(){
    //SymbolicGraph my_graph = (Variable("x")^4) + (Variable("y")^4) + (Variable("z")^4) - Constant(1);
    Variable x = Variable("x");
    Variable y = Variable("y");
    Variable z = Variable("z");

    SymbolicGraph my_graph = Power((Power(x, 2)+9*Power(y, 2)/4 + Power(z, 2) - 1), 3) - Power(x, 2)*Power(z, 3) - 9*Power(y,2)*Power(z,3)/80;
    ImplicitSurface surface(my_graph, Material(Vector3D(1,0.2,0.2), Vector3D(4,0.1,0.2), Vector3D(4,0.1,0.2), Vector3D(4,4,4), 0, 0, 1.0), BoundingBox({-1.2, 1.2}, {-1.5,1.5}, {-1.2,1.2}));
    camera::PinHoleCamera cam = camera::PinHoleCamera(Vector3D(0,-10,0), Vector3D(0,0,1), Vector3D(1,0,0), 1200, 900, 0.8);
    std::vector<RenderObject*> objs;
    std::vector<Light*> lights;
    objs.push_back(&surface);
    DistantPointSource light = DistantPointSource(Vector3D(0.5,-1,1), Vector3D(20,20,20), Vector3D(40,40,40));
    lights.push_back(&light);

    Scene my_scene = Scene(objs, lights, &cam, Vector3D(0,0,250), Vector3D(0.2,0.2,0.2));

    auto start = std::chrono::high_resolution_clock::now();

    my_scene.render(4);

    auto stop = std::chrono::high_resolution_clock::now();

    std::cout<<std::endl<<"It took "<<std::chrono::duration_cast<std::chrono::seconds>(stop - start).count()<<" seconds."<<std::endl;
    cam.write_file("./sym.bmp");
}


int main() {
    car();
    //implicit();
    //dragon();
    //geo();
    //cornell();
    return 0;

}