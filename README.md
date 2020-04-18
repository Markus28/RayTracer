
# C++ Ray Tracer  
A simple CPU Raytracer using OpenMP, built from scratch. 
It supports meshes given as OBJ and MTL files, implicit shapes and CSGs given as signed distance functions.

##Installation
OpenMP is required.

```console
git clone https://github.com/Markus28/RayTracer
cd RayTracer
python setup.py install
```

## Renders  
### OBJ-Files using Binary-Volume-Hierarchies:  
<img src=https://imgur.com/ZGqhSwN.png width="100%">  
<img src=https://i.imgur.com/RzrSGbV.png width="100%">  

### CSG:  
<img src=https://i.imgur.com/747riNa.png width="100%">  

### Implicit shapes (WIP):
<img src=https://i.imgur.com/my1nTcJ.png width="100%">  

  
## Features  
### Implemented  
* Primitives  
  * Spheres  
  * Infinite planes  
  * Triangles  
  * OBJ-Files  
  * MTL-Files  
  * Implicit Surfaces (WIP)
* Lights  
  * Point source in infinite distance  
  * Point source  
* Cameras  
  * Pinhole Camera  
  * Pinhole Camera with supersampling  
* Bounding-Volume-Hierarchies  
* Symbolic Computation System  
* Normal interpolation  
  
### Coming soon  
* UV-Mapped Spheres  
* Spherical background images  
* Fuzzy reflections  
* Bokeh  
* Area lights  
* Orthographic camera
