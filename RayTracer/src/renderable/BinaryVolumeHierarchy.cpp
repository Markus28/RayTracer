#include "BinaryVolumeHierarchy.h"
#include "../Utilities.h"
#include "../Intersection.h"
#include <algorithm>
#include <cassert>
#include <stack>


BoundingBox BinaryVolumeHierarchy::get_bounds() const {
    return nodes->my_box;
}

Intersection BinaryVolumeHierarchy::ray_intersect(const Ray &ray) const {
    FixedSizeStack<std::pair<unsigned int, Interval>, 64> to_visit;

    Interval current_interval = nodes->my_box.intersection_interval(ray);

    if(!current_interval.containsPositive()){
        return {};
    }

    unsigned int current_index = 0;
    Intersection current_best;


    while(true){
        BVHLinearNode current_node = nodes[current_index];

        if(nodes[current_index].contains_leaf){
            Intersection new_intersect = current_node.child.primitive->ray_intersect(ray);
            if(new_intersect<current_best)
                current_best = new_intersect;

            if(to_visit.empty())
                break;

            std::tie(current_index, current_interval) = to_visit.top();
            to_visit.pop();
        }

        else if (current_interval.getMin()<current_best.get_distance() || !current_best.does_intersect()) {
            Interval int_inv_a = nodes[current_index+1].my_box.intersection_interval(ray);
            Interval int_inv_b = nodes[current_index+current_node.child.second_child_offset].my_box.intersection_interval(ray);

            if(int_inv_a.containsPositive() && (int_inv_a.getMin()<int_inv_b.getMin() || !int_inv_b.containsPositive())){
                if(int_inv_b.containsPositive())
                    to_visit.push(std::make_pair(current_index+current_node.child.second_child_offset, int_inv_b));
                ++current_index;
                current_interval = int_inv_a;
            }

            else if(int_inv_b.containsPositive()){
                if(int_inv_a.containsPositive())
                    to_visit.push(std::make_pair(current_index+1, int_inv_a));
                current_index+=current_node.child.second_child_offset;
                current_interval=int_inv_b;
            }

            else{
                assert(!int_inv_a.containsPositive() && !int_inv_b.containsPositive());
                if(to_visit.empty())
                    break;

                std::tie(current_index, current_interval) = to_visit.top();
                to_visit.pop();
            }
        }

        else{
            if(to_visit.empty())
                break;

            std::tie(current_index, current_interval) = to_visit.top();
            to_visit.pop();
        }

    }


    return current_best;
}

BinaryVolumeHierarchy::~BinaryVolumeHierarchy() {
    if(nodes!=nullptr)
        delete[] nodes;
}

std::ostream& BinaryVolumeHierarchy::print(std::ostream &sink) const {
    return sink<<"Not implemented";
}

std::vector<BoundedVolume*>::iterator BinaryVolumeHierarchy::partition(std::vector<BoundedVolume *>::iterator b, std::vector<BoundedVolume *>::iterator e) {
    double min_x, max_x, min_y, max_y, min_z, max_z;
    min_x = (*b)->get_bounds()[0].getMin();
    min_y = (*b)->get_bounds()[1].getMin();
    min_z = (*b)->get_bounds()[2].getMin();
    max_x = (*b)->get_bounds()[0].getMax();
    max_y = (*b)->get_bounds()[1].getMax();
    max_z = (*b)->get_bounds()[2].getMax();

    for(auto i=b; i<e; ++i){
        min_x = std::min(min_x, (*i)->get_bounds()[0].getMin());
        min_y = std::min(min_y, (*i)->get_bounds()[1].getMin());
        min_z = std::min(min_z, (*i)->get_bounds()[2].getMin());

        max_x = std::max(max_x, (*i)->get_bounds()[0].getMax());
        max_y = std::max(max_y, (*i)->get_bounds()[1].getMax());
        max_z = std::max(max_z, (*i)->get_bounds()[2].getMax());
    }

    double dx = max_x -min_x;
    double dy = max_y -min_y;
    double dz = max_z -min_z;

    unsigned int longest_index;

    if(dx>dy && dx>dz)
        longest_index = 0;
    else if(dx>dz)
        longest_index = 1;
    else
        longest_index = 2;

    std::function<bool(BoundedVolume*, BoundedVolume*)> lambda = [longest_index](BoundedVolume* a, BoundedVolume* b)->bool
    {
        return (*a).get_bounds().get_center()[longest_index]< (*b).get_bounds().get_center()[longest_index];
    };

    return utility::split_middle(b, e, lambda);
}

BinaryVolumeHierarchy::BinaryVolumeHierarchy(std::vector<BoundedVolume*>::iterator b, std::vector<BoundedVolume*>::iterator e)
{
    BVHConstructionNode* root = build_tree(b, e);
    nodes = new BVHLinearNode[root->total_children+1];
    unsigned int used_nodes = flatten_tree(root, nodes);
    assert(used_nodes==root->total_children+1);
    delete root;
}


unsigned int BinaryVolumeHierarchy::flatten_tree(BVHConstructionNode* root, BVHLinearNode* target){
    *target = {{}, root->my_box, root->total_children==0};

    if(root->total_children==0) {
        target->child.primitive = root->children.leaf;
        return 1;
    }

    unsigned int first_child_size = flatten_tree(root->children.children_nodes.first, target + 1);
    target->child.second_child_offset = first_child_size+1;
    return flatten_tree(root->children.children_nodes.second, target+first_child_size+1)+first_child_size+1;
}

BVHConstructionNode* BinaryVolumeHierarchy::build_tree(std::vector<BoundedVolume*>::iterator b, std::vector<BoundedVolume*>::iterator e)
{
    BVHConstructionNode* root;

    switch(std::distance(b,e))
    {
        case 0: {
            return nullptr;
        }


        case 1: {
            root = new BVHConstructionNode{{}, 0, (*b)->get_bounds()};
            root->children.leaf = *b;
            break;
        }

        case 2: {
            BVHConstructionNode *first = new BVHConstructionNode{{}, 0, (*b)->get_bounds()};
            BVHConstructionNode *second = new BVHConstructionNode{{}, 0, (*(b + 1))->get_bounds()};
            first->children.leaf = *b;
            second->children.leaf = *(b + 1);
            root = new BVHConstructionNode{{}, 2, first->my_box + second->my_box};
            root->children.children_nodes = std::make_pair(second, first);
            break;
        }

        default: {
            auto division = partition(b, e);
            assert(std::distance(b, division) >= 0 && std::distance(division, e) >= 0);
            BVHConstructionNode *sub_tree_a = build_tree(b, division);
            BVHConstructionNode *sub_tree_b = build_tree(division, e);

            if (sub_tree_a == nullptr)
                return sub_tree_b;

            if (sub_tree_b == nullptr)
                return sub_tree_a;

            root = new BVHConstructionNode{{}, sub_tree_a->total_children + sub_tree_b->total_children+2,
                                           sub_tree_a->my_box + sub_tree_b->my_box};
            root->children.children_nodes = std::make_pair(sub_tree_a, sub_tree_b);
        }
    }

    return root;
}

IntersectionProperties BinaryVolumeHierarchy::intersect_properties(const Ray &ray) const
{
    assert(false);                                      //DO NOT CALL THIS METHOD! NOT EFFICIENT!
    Intersection intersection = ray_intersect(ray);
    return intersection.get_object()->intersect_properties(ray);
}

unsigned int BinaryVolumeHierarchy::get_deepest_branch() const {
    return get_deepest_branch(0);
}

unsigned int BinaryVolumeHierarchy::get_deepest_branch(unsigned int offset) const {
    if(nodes[offset].contains_leaf)
        return 0;
    return 1+std::max(get_deepest_branch(offset+1), get_deepest_branch(offset+nodes[offset].child.second_child_offset));
}