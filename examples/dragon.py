import os
from RayTracer.file import OBJFile
from RayTracer.scene import Scene
from RayTracer.lights import DistantPointSource
from RayTracer.camera import PinHoleCamera


dragon_path = "assets/dragon.obj"

dragon_mesh = OBJFile(dragon_path)
dragon_bvh = dragon_mesh.get_bvh()

light = DistantPointSource((1,1,1), (70,70,70), (50,50,50))

camera = PinHoleCamera((0,5, 20), (0,1,0), (1,0,0), 2000, 1400, 0.8)

dragon_scene = Scene([dragon_bvh], [light], camera, (200,200,200), (0.2,0.2,0.2))

print("Rendering...")
dragon_scene.render(3)
print("Done")

camera.write_file("./dragon.bmp")
