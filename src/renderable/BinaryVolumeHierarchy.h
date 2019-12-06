#ifndef RAYTRACER_BINARYVOLUMEHIERARCHY_H
#define RAYTRACER_BINARYVOLUMEHIERARCHY_H


#include "BoundedVolume.h"
#include <vector>
#include <cassert>

struct BVHConstructionNode{
    union ConstructionChildren{
        std::pair<BVHConstructionNode*, BVHConstructionNode*> children_nodes;
        BoundedVolume* leaf;
    };
    ConstructionChildren children;
    unsigned int total_children;
    BoundingBox my_box;
    ~BVHConstructionNode(){
        if(total_children!=0){
            delete children.children_nodes.first;
            delete children.children_nodes.second;
        }
    }
};

struct BVHLinearNode{
    union LinearSecondChild{
        BoundedVolume* primitive;
        unsigned int second_child_offset;
    };

    LinearSecondChild child;
    BoundingBox my_box;
    bool contains_leaf;

    ~BVHLinearNode()=default;
};


/**
 * @brief A stack that can contain at most N elements. If more are pushed to the stack, it will crash. No error handling
 * is done. If top is called on an empty stack, it will crash.
 * @tparam V Type of elements in the stack
 * @tparam N Maximum number of elements in stack.
 */
template <class V, unsigned int N>
class FixedSizeStack{
public:
    FixedSizeStack(): stack_pointer(-1){};

    void pop(){
        assert(stack_pointer>=0);
        stack_pointer-=1;
    }

    V top(){
        assert(stack_pointer>=0);
        return data[stack_pointer];
    }

    bool empty() const{
        return stack_pointer<0;
    }

    void push(const V& to_push){
        assert(stack_pointer<N-1 || stack_pointer<0);
        data[stack_pointer+1] = to_push;
        stack_pointer+=1;
    }

    void flush(){
        stack_pointer = -1;
    }

private:
    int stack_pointer;
    V data[N];
};

/**
 * @brief Acceleration structure for ensemble of bounded volumes
 */
class BinaryVolumeHierarchy: public BoundedVolume {
public:
    BinaryVolumeHierarchy(std::vector<BoundedVolume*>::iterator b, std::vector<BoundedVolume*>::iterator e);
    Intersection ray_intersect(const Ray &ray) const override;
    BoundingBox get_bounds() const override;
    std::ostream& print(std::ostream& sink) const override;
    IntersectionProperties intersect_properties(const Ray &ray) const override;
    unsigned int get_deepest_branch() const;
    ~BinaryVolumeHierarchy() override;

private:
    unsigned int get_deepest_branch(unsigned int offset) const;
    BVHLinearNode* nodes = nullptr;
    BVHConstructionNode* build_tree(std::vector<BoundedVolume*>::iterator b, std::vector<BoundedVolume*>::iterator e);
    unsigned int flatten_tree(BVHConstructionNode* root, BVHLinearNode* nodes);
    std::vector<BoundedVolume*>::iterator partition(std::vector<BoundedVolume*>::iterator b, std::vector<BoundedVolume*>::iterator e);
};

#endif //RAYTRACER_BINARYVOLUMEHIERARCHY_H