import os
from ctypes import cdll, c_void_p
from .utilities import create_vector, destroy_vector

lib = cdll.LoadLibrary(os.path.join(os.path.dirname(__file__),'libRayTracer.so'))

lib.new_distant_light.argtypes = [c_void_p, c_void_p, c_void_p]
lib.new_distant_light.restype = c_void_p

lib.delete_distant_light.argtypes = [c_void_p]
lib.delete_distant_light.restype = None

class DistantPointSource:
    def __init__(self, direction, specular, diffuse):
        #Construct Vector3D objects
        dir_ptr = create_vector(direction)
        spec_ptr = create_vector(specular)
        diff_ptr = create_vector(specular)

        self.ptr = c_void_p(lib.new_distant_light(dir_ptr, spec_ptr, diff_ptr))

        #Clean up
        destroy_vector(dir_ptr)
        destroy_vector(spec_ptr)
        destroy_vector(diff_ptr)


    def __del__(self):
        lib.delete_distant_light(self.ptr)
