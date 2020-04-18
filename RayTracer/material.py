import os
from ctypes import cdll, c_void_p, c_double
from .utilities import create_vector, destroy_vector

lib = cdll.LoadLibrary(os.path.join(os.path.dirname(__file__),'libRayTracer.

lib.new_material.argtypes = [c_void_p, c_void_p, c_void_p, c_void_p, c_double, c_double, c_double]
lib.new_material.restype = c_void_p

lib.delete_material.argtypes = [c_void_p]
lib.delete_material.restype = None


class Material:
    def __init__(self, specular_refl, diff_refl, ambient_refl, shininess, transparency, reflectivity, eta):
        spec_ptr = create_vector(specular_refl)
        diff_ptr = create_vector(diff_refl)
        ambient_ptr = create_vector(ambient_refl)
        shininess_ptr = create_vector(shininess)

        self.ptr = c_void_p(lib.new_material(spec_ptr, diff_ptr, ambient_ptr, shininess_ptr, transparency,
                                             reflectivity, eta))

        destroy_vector(spec_ptr)
        destroy_vector(diff_ptr)
        destroy_vector(ambient_ptr)
        destroy_vector(shininess_ptr)

    def __del__(self):
        print("Destroying Material")
        lib.delete_material(self.ptr)
