#include "Scene.h"
#include "Light.h"
#include "Intersection.h"
#include "RenderObject.h"
#include "Utilities.h"
#include <iostream>

Scene::Scene(const std::vector<RenderObject*>& objects, const std::vector<Light*>& lights, Camera* camera, Color background, Vector3D ambient)
{
    assert(!objects.empty());
    this->cam = camera;
    this->objs = objects;
    this->lights = lights;
    this->backgrnd = background;
    this->ambient = ambient;
}

void Scene::render(unsigned int recursion_depth) {
    for(cam->resetRay(); !cam->endRay(); cam->advanceRay())
    {
        cam->setRay(traceRay(cam->currentRay(), recursion_depth));
    }
}


Color Scene::traceRay(const Ray &ray, unsigned int recursion_depth) {
    Intersection hit = firstHit(ray);

    if(hit.doesIntersect())
    {
        assert(hit.getObject()!=nullptr);
        IntersectionProperties properties = hit.getObject()->intersectProperties(ray);
        Vector3D illumination = ambient.elementWiseMultiplication(properties.material.ambientReflectivity());
        Vector3D intersectionPoint = ray.readBase()+ray.readDirection()*hit.getDistance();

        for(Light* light: lights)
        {
            Ray shaddow = light->shaddowRay(intersectionPoint);
            shaddow.offset(properties.normal*utility::EPSILON);
            //shaddow.walk(utility::EPSILON);     //TODO: change epsilon
            Intersection shadowHit = firstHit(shaddow);
            if(!shadowHit.doesIntersect() || shadowHit.getDistance() > light->getDistance(intersectionPoint))      //Check shaddow ray
            {
                double dd = shaddow.readDirection()*properties.normal;
                double ds = (shaddow.readDirection()*-1).reflectAround(properties.normal)*(ray.readDirection()*-1);
                if(dd>0)
                {
                    illumination += properties.material.diffuseReflectivity().elementWiseMultiplication(light->diffuseComponent(shaddow.readBase()))*dd;
                    if(ds>0)
                    {
                        illumination += properties.material.specularReflectivity().elementWiseMultiplication(light->specularComponent(shaddow.readBase())).elementWiseMultiplication(properties.material.shininess().elementWisePower(ds));
                    }
                }
            }
        }

        Vector3D refractionAndReflection;

        if(recursion_depth!=0)
        {
            if(properties.material.isReflective())
            {
                Ray reflection = Ray(intersectionPoint, ray.readDirection().reflectAround(properties.normal));
                reflection.offset(properties.normal*utility::EPSILON);
                refractionAndReflection += traceRay(reflection, recursion_depth-1)*properties.material.getReflectivity();
            }
        }

        return Color(properties.material.getColor().elementWiseMultiplication(illumination) + refractionAndReflection);
    }

    else
    {
        return backgrnd;
    }
}


Intersection Scene::firstHit(const Ray &ray) {
    Intersection firstHit = objs[0]->rayIntersect(ray);
    for(unsigned int i = 1; i<objs.size(); ++i)
    {
        firstHit = std::min(firstHit, objs[i]->rayIntersect(ray));
    }
    return firstHit;
}