import os
from ctypes import cdll, c_void_p, c_int, c_char_p, c_double
from .utilities import create_vector, destroy_vector

lib = cdll.LoadLibrary(os.path.join(os.path.dirname(__file__),'libRayTracer.so'))

lib.new_pinhole_cam.argtypes = [c_void_p, c_void_p, c_void_p, c_int, c_int, c_double]
lib.new_pinhole_cam.restype = c_void_p

lib.pinhole_cam_write_file.argtypes = [c_void_p, c_char_p]
lib.pinhole_cam_write_file.restype = None

lib.delete_pinhole_cam.argtypes = [c_void_p]
lib.delete_pinhole_cam.restype = None


class PinHoleCamera:
    def __init__(self, position, up, right, width, height, width_angle):
        pos_ptr = create_vector(position)
        up_ptr = create_vector(up)
        right_ptr = create_vector(right)

        self.ptr = c_void_p(lib.new_pinhole_cam(pos_ptr, up_ptr, right_ptr, width, height, width_angle))

        destroy_vector(pos_ptr)
        destroy_vector(up_ptr)
        destroy_vector(right_ptr)


    def write_file(self, file_name):
        file_name_ptr = c_char_p(file_name.encode('utf-8'))
        lib.pinhole_cam_write_file(self.ptr, file_name_ptr)


    def __del__(self):
        lib.delete_pinhole_cam(self.ptr)
