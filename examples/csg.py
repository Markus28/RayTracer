from RayTracer.renderable import SDFBox, SDFCylinder, SDFSphere, CSGObject
from RayTracer.material import Material
from RayTracer.camera import PinHoleCamera
from RayTracer.lights import DistantPointSource
from RayTracer.scene import Scene

objs = []
lights = []

blue = Material((0.1,0.3, 3), (0.1,0.1,3), (0.1, 0.3, 3), (1,1,1), 0,0,1)
green = Material((0,1,3,0.3), (0.1,3,0.1), (0.1,3,0.3), (1,1,1),0,0,1)
red = Material((3,0.1,0.3), (3,0.1,0.3), (3,0.1,0.3), (1,1,1), 0,0,1)

cylinder_x = SDFCylinder((0,0,0), (1,0,0), 2.0, 0.35, red)
cylinder_y = SDFCylinder((0,0,0), (0,1,0), 2.0, 0.35, red)
cylinder_z = SDFCylinder((0,0,0), (0,0,1), 2.0, 0.35, red)

box = SDFBox((0,0,0), 1,1,1, green)

sphere = SDFSphere((0,0,0), 0.65, blue)

cross = CSGObject()
cross.union(cylinder_x)
cross.union(cylinder_y)
cross.union(cylinder_z)


result = CSGObject()
result.union(box)
result.intersect(sphere)
result.subtract(cross)

objs.append(result)


cam = PinHoleCamera((2.25, 2.25, 2.5), (-1,-1,2), (-1,1,0), 2400, 1800, 0.8)
light = DistantPointSource((1,1,1), (20,20,20), (40,40,40))
lights.append(light)

my_scene = Scene(objs, lights, cam, (200,200,200), (0.2,0.2,0.2))
my_scene.render(3)
cam.write_file("sdf.bmp")