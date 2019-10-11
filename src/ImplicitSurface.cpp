#include "ImplicitSurface.h"
#include <cmath>
#include <cassert>


ImplicitSurface::ImplicitSurface(symcpp::SymbolicGraph f, Material m, BoundingBox b):F(f), mat(m), bounds(b) {
    dxF = F.diff("x");
    dyF = F.diff("y");
    dzF = F.diff("z");

    std::cout<< f << std::endl << dxF <<std::endl <<dyF<<std::endl<<dzF<<std::endl;

    max_iter = 70;
    epsilon = 0.00000000000001;
}

BoundingBox ImplicitSurface::getBounds() const {
    return bounds;
}

/**
 * @brief Uses the symbolic derivative and the Newton method to detect the earliest intersection
 * @see https://en.wikipedia.org/wiki/Newton%27s_method
 * @param ray The ray intersecting the surface
 * @return Intersection object containing distance of intersection and pointer to this
 */
Intersection ImplicitSurface::rayIntersect(const Ray &ray) const {
    Interval range = bounds.intersectionInterval(ray);

    if(range.isEmpty() || range.getMax()<0){
        return {};
    }


    double guess_l = std::max(range.getMin(), 0.);
    Vector3D guess_v = ray.readDirection()+ray.readDirection()*guess_l;
    std::unordered_map<std::string, double> env;
    env["x"] = guess_v[0];
    env["y"] = guess_v[1];
    env["z"] = guess_v[2];

    unsigned int i = 0;
    double F_value = F.subs(env);
    double deriv;

    while(i<max_iter && std::abs(F_value)>epsilon){
        deriv = dxF.subs(env)*ray.readDirection()[0] + dyF.subs(env)*ray.readDirection()[1] + dzF.subs(env)*ray.readDirection()[2];
        guess_l -= F_value/deriv;
        guess_v = ray.readBase()+ray.readDirection()*guess_l;
        env["x"] = guess_v[0];
        env["y"] = guess_v[1];
        env["z"] = guess_v[2];
        F_value = F.subs(env);
        ++i;
    }

    if(std::abs(F_value)<epsilon && guess_l>0){
        return {this, guess_l};
    }

    return {};
}

IntersectionProperties ImplicitSurface::intersectProperties(const Ray &ray) const {
    Intersection is = this->rayIntersect(ray);            //TODO: add intersection information to call!!! This is inefficient!
    assert(is.doesIntersect());
    Vector3D posn = ray.readBase()+ray.readDirection()*is.getDistance();
    std::unordered_map<std::string, double> env;
    env["x"] = posn[0];
    env["y"] = posn[1];
    env["z"] = posn[2];

    Vector3D grad(dxF.subs(env), dyF.subs(env), dzF.subs(env));
    grad /= grad.norm();
    return {grad ,mat};
}

std::ostream& ImplicitSurface::print(std::ostream &sink) const {
    sink<<"Implicit Surface for Function F(x,y,z)="<<F;
}