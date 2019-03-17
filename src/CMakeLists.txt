cmake_minimum_required(VERSION 3.12)
project(RayTracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(RayTracer main.cpp Vector3D.cpp Vector3D.h Ray.cpp Ray.h SimplePlane.cpp SimplePlane.h Utilities.cpp Utilities.h RenderObject.cpp RenderObject.h Intersection.cpp Intersection.h Material.cpp Material.h Scene.cpp Scene.h Light.cpp Light.h SimpleSphere.cpp SimpleSphere.h Camera.cpp Camera.h Color.cpp Color.h IntersectionProperties.cpp IntersectionProperties.h PinHoleCamera.cpp PinHoleCamera.h DistantPointSource.cpp DistantPointSource.h Background.cpp Background.h UVMap.cpp UVMap.h SphereMap.cpp SphereMap.h Triangle.cpp Triangle.h Interval.cpp Interval.h BoundingBox.cpp BoundingBox.h BoundedVolume.cpp BoundedVolume.h BinaryVolumeHierarchy.cpp BinaryVolumeHierarchy.h BoundedVolume.cpp BoundedVolume.h DownSamplingCam.cpp DownSamplingCam.h OBJFile.cpp OBJFile.h PointSource.cpp PointSource.h RandomLight.cpp RandomLight.h)