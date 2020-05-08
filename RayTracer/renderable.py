import os
from ctypes import cdll, c_void_p, c_double
from .utilities import create_vector, destroy_vector

lib = cdll.LoadLibrary(os.path.join(os.path.dirname(__file__),'libRayTracer.so'))


lib.new_triangle.argtypes = [c_void_p, c_void_p, c_void_p, c_void_p]
lib.new_triangle.restype = c_void_p

lib.set_triangle_normals.argtypes = [c_void_p, c_void_p, c_void_p, c_void_p]
lib.set_triangle_normals.restype = None

lib.delete_triangle.argtypes = [c_void_p]
lib.delete_triangle.restype = None


lib.new_bvh.argtypes = [c_void_p]
lib.new_bvh.restype = c_void_p

lib.delete_bvh.argtypes = [c_void_p]
lib.delete_bvh.restype = None


lib.new_ro_vector.argtypes = []
lib.new_ro_vector.restype = c_void_p

lib.push_back_ro.artypes = [c_void_p]
lib.push_back_ro.restype = None

lib.delete_ro_vector.artypes = [c_void_p]
lib.delete_ro_vector.restype = None


lib.new_csg_object.artypes = []
lib.new_csg_object.restype = c_void_p

lib.delete_csg_object.artypes = [c_void_p]
lib.delete_csg_object.restype = None


lib.new_sdf_sphere.artypes = [c_void_p, c_double, c_void_p]
lib.new_sdf_sphere.restype = c_void_p

lib.delete_sdf_sphere.artypes = [c_void_p]
lib.delete_sdf_sphere.restype = None


lib.new_sdf_cylinder.artypes = [c_void_p, c_void_p, c_double, c_double, c_void_p]
lib.new_sdf_cylinder.restype = c_void_p

lib.delete_sdf_cylinder.artypes = [c_void_p]
lib.delete_sdf_cylinder.restype = None


lib.new_sdf_box.artypes = [c_void_p, c_double, c_double, c_double, c_void_p]
lib.new_sdf_box.restype = c_void_p

lib.delete_sdf_box.artypes = [c_void_p]
lib.delete_sdf_box.restype = None


lib.sdf_intersect.artypes = [c_void_p, c_void_p]
lib.sdf_intersect.restype = None

lib.sdf_unionize.artypes = [c_void_p, c_void_p]
lib.sdf_unionize.restype = None

lib.sdf_subtract.artypes = [c_void_p, c_void_p]
lib.sdf_subtract.restype = None


lib.csg_intersect.artypes = [c_void_p, c_void_p]
lib.csg_intersect.restype = None

lib.csg_unionize.artypes = [c_void_p, c_void_p]
lib.csg_unionize.restype = None

lib.csg_subtract.artypes = [c_void_p, c_void_p]
lib.csg_subtract.restype = None


class Triangle:
    def __init__(self, a, b, c, mat, normals = None):
        # We need to keep a tab on mat in order to protect them from being destroyed
        self.material = mat

        # First we need to construct pointers to Vector3D objects
        a_ptr = create_vector(a)
        b_ptr = create_vector(b)
        c_ptr = create_vector(c)

        # Now we need to construct a Triangle object

        self.ptr = c_void_p(lib.new_triangle(a_ptr, b_ptr, c_ptr, mat.ptr))

        # Now we need to clean up the memory
        destroy_vector(a_ptr)
        destroy_vector(b_ptr)
        destroy_vector(c_ptr)

        if normals is not None:
            self.set_normals(normals[0], normals[1], normals[2])

    def set_normals(self, an, bn, cn):
        an_ptr = create_vector(an)
        bn_ptr = create_vector(bn)
        cn_ptr = create_vector(cn)

        lib.set_triangle_normals(self.ptr, an_ptr, bn_ptr, cn_ptr)

        destroy_vector(an_ptr)
        destroy_vector(bn_ptr)
        destroy_vector(cn_ptr)


    def __del__(self):
        print("Destroying Triangle")
        lib.delete_triangle(self.ptr)


class BVH:
    def __init__(self, objs):
        # We need to keep a tab on the objs to protect them from being destroyed
        self.objects = objs

        # First we need to construct a C++ vector of pointers to the objects
        self.obj_vector = c_void_p(lib.new_ro_vector())

        for o in objs:
            lib.push_back_ro(self.obj_vector, o.ptr)

        self.ptr = c_void_p(lib.new_bvh(self.obj_vector))

        lib.delete_ro_vector(self.obj_vector)

    def __del__(self):
        lib.delete_bvh(self.ptr)



"""
The following classes wrap the SDF and CSG functionalities:

"""

class CSGObject:
    def __init__(self):
        self.components = []
        self.ptr = c_void_p(lib.new_csg_object())

    def intersect(self, other):
        self.components.append(other)

        if(type(other)!=CSGObject):
            lib.sdf_intersect(self.ptr, other.ptr)
        else:
            lib.csg_intersect(self.ptr, other.ptr)

    def union(self, other):
        self.components.append(other)

        if(type(other)!=CSGObject):
            lib.sdf_unionize(self.ptr, other.ptr)
        else:
            lib.csg_unionize(self.ptr, other.ptr)

    def subtract(self, other):
        self.components.append(other)

        if(type(other)!=CSGObject):
            lib.sdf_subtract(self.ptr, other.ptr)
        else:
            lib.csg_subtract(self.ptr, other.ptr)

    def __del__(self):
        lib.delete_csg_object(self.ptr)


class SDFSphere:
    def __init__(self, center, r, mat):
        center_ptr = create_vector(center)
        self.mat = mat

        self.ptr = c_void_p(lib.new_sdf_sphere(center_ptr, c_double(r), mat.ptr))

        destroy_vector(center_ptr)

    def __del__(self):
        lib.delete_sdf_sphere(self.ptr)


class SDFCylinder:
    def __init__(self, center, axis, length, radius, mat):
        self.mat = mat
        axis_ptr = create_vector(axis)
        center_ptr = create_vector(center)

        self.ptr = c_void_p(lib.new_sdf_cylinder(center_ptr, axis_ptr, c_double(length), c_double(radius), mat.ptr))

        destroy_vector(axis_ptr)
        destroy_vector(center_ptr)

    def __del__(self):
        lib.delete_sdf_cylinder(self.ptr)

class SDFBox:
    def __init__(self, center, depth, height, length, mat):
        self.mat = mat
        center_ptr = create_vector(center)

        self.ptr = c_void_p(lib.new_sdf_box(center_ptr, c_double(depth), c_double(height), c_double(length), mat.ptr))

        destroy_vector(center_ptr)

    def __del__(self):
        lib.delete_sdf_box(self.ptr)
