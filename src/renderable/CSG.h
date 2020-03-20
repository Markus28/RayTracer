#ifndef RAYTRACER_CSG_H
#define RAYTRACER_CSG_H

#include "SDFObject.h"


/**
 * @brief Interface for nodes in CSG-Tree according to composition-pattern.
 *
 * Note, that CSGComponent is not renderable and is not affiliated with SDFObject. Although its methods have the same
 * names, they have (formally) nothing to do with SDFObject or BoundingBox methods.
 */
class CSGComponent{
public:
    virtual double distance_bound(const Vector3D& pos) const = 0;
    virtual IntersectionProperties properties_at(const Vector3D& pos) const = 0;
    virtual BoundingBox get_bounds() const = 0;
    virtual CSGComponent* deep_copy() const = 0;
    virtual ~CSGComponent() = default;
};

/**
 * @brief A union node in the CSG-Tree
 */
class CSGUnion: public CSGComponent{
public:
    /**
     * @brief Create a Union-Node for a CSG-Tree.
     * @param a The first node
     * @param b The second
     */
    CSGUnion(CSGComponent* a, CSGComponent *b): first(a), second(b) {bounds = a->get_bounds()+b->get_bounds();};

    double distance_bound(const Vector3D& pos) const override;
    IntersectionProperties properties_at(const Vector3D& pos) const override;
    BoundingBox get_bounds() const override;
    CSGComponent* deep_copy() const override;

    ~CSGUnion() override {delete first; delete second;};

private:
    CSGComponent* first;
    CSGComponent* second;
    BoundingBox bounds;  ///A bounding box for the union. It is simply the smallest bounding box that contains both boxes
};

/**
 * @brief An intersection node in the CSG-Tree
 */
class CSGIntersection: public CSGComponent{
public:
    /**
     * @brief C
     */
    CSGIntersection(CSGComponent* a, CSGComponent *b): first(a), second(b) {bounds = (a->get_bounds()).intersection_box(b->get_bounds());};


    double distance_bound(const Vector3D& pos) const override;
    IntersectionProperties properties_at(const Vector3D& pos) const override;
    BoundingBox get_bounds() const override;
    CSGComponent* deep_copy() const override;

    ~CSGIntersection() override {delete first; delete second;};

private:
    CSGComponent* first;
    CSGComponent* second;
    BoundingBox bounds;     /// BoundingBox for the Intersection. It is the intersection of the two BoundingBoxes
};

/**
 * @brief A difference node in the CSG-Tree
 */
class CSGDifference: public CSGComponent{
public:
    CSGDifference(CSGComponent* a, CSGComponent *b): first(a), second(b) {};

    double distance_bound(const Vector3D& pos) const override;
    IntersectionProperties properties_at(const Vector3D& pos) const override;
    /**
     * @brief Returns a BoundingBox for the Difference
     * It will simply return the BoundingBox of a, this is usually a good fit.
     * @return BoundingBox of left node
     */
    BoundingBox get_bounds() const override;
    CSGComponent* deep_copy() const override;

    ~CSGDifference() override {delete first; delete second;};

private:
    CSGComponent* first;
    CSGComponent* second;
};

/**
 * @brief Essentially a wrapper for DistanceEstimatedObject. They are leafs in the CSG-Tree.
 */
class CSGLeaf: public CSGComponent{
public:
    explicit CSGLeaf(SDFObject* a): obj(a) {};

    double distance_bound(const Vector3D& pos) const override {return obj->distance_bound(pos);};
    IntersectionProperties properties_at(const Vector3D& pos) const override {return obj->properties_at(pos);};
    BoundingBox get_bounds() const override;
    CSGComponent* deep_copy() const override;

    ~CSGLeaf() override = default;          //We do not delete obj, because we do not have ownership

private:
    SDFObject* obj;
};

/**
 * @brief This renderable object represents a constructive solid geometry
 *
 * A CSG consists of a set of primitives, SDFObjects, which are composed into one object by taking their union,
 * intersection or difference. The sequence of operations is stored as a tree, CSG contains a pointer to the root of this
 * tree. Nodes in this tree implement the abstract class CSGComponent.
 */
class CSG: public SDFObject {
public:
    CSG();
    CSG(const CSG& other);
    CSG& operator=(const CSG& other);
    explicit CSG(SDFObject* object);

    void unionize(SDFObject* a);
    void intersect(SDFObject* a);
    void subtract(SDFObject* a);

    void unionize(const CSG& a);
    void intersect(const CSG& a);
    void subtract(const CSG& a);

    BoundingBox get_bounds() const override;

    ~CSG() override;

private:
    double distance_bound(const Vector3D& pos) const override;
    IntersectionProperties properties_at(const Vector3D& pos) const override {return root->properties_at(pos);};

    CSGComponent* root;     ///Root of the CSG-Tree
};


#endif //RAYTRACER_CSG_H
