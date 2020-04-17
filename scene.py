from ctypes import cdll, c_void_p, c_int
from .utilities import create_vector, destroy_vector

lib = cdll.LoadLibrary('RayTracer/lib/libRayTracer.so')


lib.new_ro_vector.argtypes = []
lib.new_ro_vector.restype = c_void_p

lib.push_back_ro.argtypes = [c_void_p, c_void_p]
lib.push_back_ro.restype = None

lib.new_lights_vector.argtypes = []
lib.new_lights_vector.restype = c_void_p

lib.push_back_light.argtypes = [c_void_p, c_void_p]
lib.push_back_light.restype = None

lib.delete_lights_vector.argtypes = [c_void_p]
lib.delete_lights_vector.restype = None

lib.new_scene.argtypes = [c_void_p, c_void_p, c_void_p, c_void_p, c_void_p]
lib.new_scene.restype = c_void_p

lib.render_scene.argtypes = [c_void_p, c_int]
lib.render_scene.restype = None

lib.delete_scene.argtypes = [c_void_p]
lib.delete_scene.restype = None


class Scene:
    def __init__(self, objects, lights, camera, background, ambient):
        #Keep all the necessary objects alive
        self.objects = objects
        self.lights = lights
        self.camera = camera

        background_ptr = create_vector(background)
        ambient_ptr = create_vector(ambient)

        object_vec_ptr = c_void_p(lib.new_ro_vector())

        for obj in objects:
            lib.push_back_ro(object_vec_ptr, obj.ptr)

        light_vec_ptr = c_void_p(lib.new_lights_vector())

        for light in lights:
            lib.push_back_light(light_vec_ptr, light.ptr)

        self.ptr = c_void_p(lib.new_scene(object_vec_ptr, light_vec_ptr, camera.ptr, background_ptr, ambient_ptr))

        destroy_vector(background_ptr)
        destroy_vector(ambient_ptr)

        lib.delete_ro_vector(object_vec_ptr)
        lib.delete_lights_vector(light_vec_ptr)


    def render(self, recursion_depth = 2):
        lib.render_scene(self.ptr, recursion_depth)

    def __del__(self):
        lib.delete_scene(self.ptr)