#include "renderable/Triangle.h"
#include "camera/PinHoleCamera.h"
#include "Scene.h"
#include "renderable/BinaryVolumeHierarchy.h"
#include "OBJFile.h"
#include "light/DistantPointSource.h"
#include "renderable/SDFSphere.h"
#include "renderable/SDFBox.h"
#include "renderable/CSG.h"
#include "renderable/SDFCylinder.h"

extern "C" {
    Vector3D* new_vector(double x, double y, double z){
        return new Vector3D(x,y,z);
    }

    void delete_vector(Vector3D* vec){
        delete vec;
    }
}

extern "C"{
    Material* new_material(Vector3D* specular_refl, Vector3D* diff_refl, Vector3D* ambient_refl,
                           Vector3D* shininess, double transparency, double reflectivity, double eta){
        return new Material(*specular_refl, *diff_refl, *ambient_refl, *shininess, transparency, reflectivity, eta);
    }

    void delete_material(Material* m){
        delete m;
    }
}


extern "C" {
    Triangle* new_triangle(Vector3D* a, Vector3D* b, Vector3D* c, Material* m){
        return new Triangle(*a, *b, *c, *m);
    }

    void set_triangle_normals(Triangle* T, Vector3D* na, Vector3D* nb, Vector3D* nc){
        T->set_normals(*na, *nb, *nc);
    }

    void delete_triangle(Triangle* t){
        delete t;
    }
}

extern "C" {
    std::vector<BoundedVolume*>* new_bv_vector(){
        return new std::vector<BoundedVolume*>;
    }

    void push_back_bv(std::vector<BoundedVolume*>* vec, BoundedVolume* obj){
        vec->push_back(obj);
    }

    void delete_bv_vector(std::vector<BoundedVolume*>* vec){
        delete vec;
    }

    BinaryVolumeHierarchy* new_bvh(std::vector<BoundedVolume*>* objs){
        return new BinaryVolumeHierarchy(objs->begin(), objs->end());
    }

    void delete_bvh(BinaryVolumeHierarchy* b){
        delete b;
    }
}


extern "C" {
    camera::PinHoleCamera* new_pinhole_cam(Vector3D* position, Vector3D* up, Vector3D* right, unsigned int width,
            unsigned int height, double width_angle){
        return new camera::PinHoleCamera(*position, *up, *right, width, height, width_angle);
    }

    void delete_pinhole_cam(camera::PinHoleCamera* c){
        delete c;
    }

    void pinhole_cam_write_file(camera::PinHoleCamera*c, char* s){
        c->write_file(std::string(s));
    }
}


extern "C" {
    std::vector<RenderObject*>* new_ro_vector(){
        return new std::vector<RenderObject*>;
    }

    void push_back_ro(std::vector<RenderObject*>* vec, RenderObject* obj){
        vec->push_back(obj);
    }

    void delete_ro_vector(std::vector<RenderObject*>* vec){
        delete vec;
    }


    std::vector<Light*>* new_lights_vector(){
        return new std::vector<Light*>;
    }

    void push_back_light(std::vector<Light*>* vec, Light* obj){
        vec->push_back(obj);
    }

    void delete_lights_vector(std::vector<Light*>* vec){
        delete vec;
    }


    Scene* new_scene(std::vector<RenderObject*>* objs, std::vector<Light*>* lights, camera::Camera* cam,
                     Vector3D* background, Vector3D* ambient){
        return new Scene(*objs, *lights, cam, *background, *ambient);
    }

    void render_scene(Scene* scene, unsigned int recursion_depth){
        scene->render(recursion_depth);
    }

    void delete_scene(Scene* s){
        delete s;
    }
}

extern "C" {
    DistantPointSource* new_distant_light(Vector3D* dir, Vector3D* specular, Vector3D* diffuse){
        return new DistantPointSource(*dir, *specular, *diffuse);
    }

    void delete_distant_light(DistantPointSource* l){
        delete l;
    }
}


extern "C" {
    CSG* new_csg_object(){
        return new CSG();
    }

    void delete_csg_object(CSG* c){
        delete c;
    }

    SDFSphere* new_sdf_sphere(Vector3D* center, double r, Material* material){
        return new SDFSphere(*center, r, *material);
    }

    void delete_sdf_sphere(SDFSphere* s){
        delete s;
    }

    SDFCylinder* new_sdf_cylinder(Vector3D* center, Vector3D* axis, double length, double radius, Material* mat){
        return new SDFCylinder(*center, *axis, length, radius, *mat);
    }

    void delete_sdf_cylinder(SDFCylinder* c){
        delete c;
    }

    SDFBox* new_sdf_box(Vector3D* center, double depth, double height, double length, Material* mat)
    {
        return new SDFBox(*center, depth, height, length, *mat);
    }

    void delete_sdf_box(SDFBox* b){
        delete b;
    }

    void sdf_intersect(CSG* c, SDFObject* o){
        c->intersect(o);
    }

    void sdf_unionize(CSG* c, SDFObject* o){
        c->unionize(o);
    }

    void sdf_subtract(CSG* c, CSG* o){
        c->subtract(*o);
    }

    void csg_intersect(CSG* c, const CSG* o){
        c->intersect(*o);
    }

    void csg_unionize(CSG* c, const CSG* o){
        c->unionize(*o);
    }

    void csg_subtract(CSG* c, const CSG* o){
        c->subtract(*o);
    }
}