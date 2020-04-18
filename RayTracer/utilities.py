import os
from ctypes import cdll, c_void_p, c_double

lib = cdll.LoadLibrary(os.path.join(os.path.dirname(__file__), 'lib/libRayTracer.so'))

lib.new_vector.argtypes = [c_double, c_double, c_double]
lib.new_vector.restype = c_void_p

lib.delete_vector.argtypes = [c_void_p]
lib.delete_vector.restype = None


def create_vector(lst):
    return c_void_p(lib.new_vector(lst[0], lst[1], lst[2]))


def destroy_vector(v):
    lib.delete_vector(v)
