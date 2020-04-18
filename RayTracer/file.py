from .renderable import BVH, Triangle
from .material import Material
import os


def to_int_or_none(s):
    if s == "":
        return None

    return int(s)


class OBJFile:
    def __init__(self, file_name, standard_material=None):
        if standard_material is None:
            standard_material = Material((3,3,3), (1,1,1), (0.5,0.5,0.5), (8,8,8), 0, 0, 1.0)

        else:
            standard_material = standard_material

        self.vertices = []
        self.vertex_normals = []
        self.triangles = []
        self.materials = {}

        current_material = standard_material

        with open(file_name) as f:
            for line in f:
                if line[0] == "#" or line.strip() == "":
                    continue

                line_seperated = list(filter(lambda x: x != "", line.strip().split(" ")))

                if line_seperated[0] == "mtllib":
                    mtllib_path = os.path.join(os.path.dirname(file_name),  line_seperated[1])
                    if os.path.exists(mtllib_path):
                        self.materials = self.read_mtllib(mtllib_path)

                elif line_seperated[0] == "usemtl":
                   if line_seperated[1] in self.materials:
                        current_material = self.materials[line_seperated[1]]

                elif line_seperated[0] == "v":
                    self.vertices.append([float(line_seperated[1]), float(line_seperated[2]), float(line_seperated[3])])

                elif line_seperated[0] == "f":
                    vertex_data = [[to_int_or_none(s2) for s2 in s1.split("/")] for s1 in line_seperated[1:]]
                    for i in range(len(vertex_data)-2):
                        self.triangles.append(Triangle(self.vertices[vertex_data[0][0] - 1],
                                                        self.vertices[vertex_data[i+2][0] - 1],
                                                        self.vertices[vertex_data[i+1][0] - 1],
                                                        current_material))

                        if len(vertex_data[0])==3 and not (vertex_data[0][2] is None or vertex_data[i+1][2] is None or vertex_data[i+2][2] is None):
                            self.triangles[-1].set_normals(self.vertices[vertex_data[0][2]-1],
                                                            self.vertices[vertex_data[i+2][2]-1], self.vertices[vertex_data[i+1][2]-1])


                elif line_seperated[0]=="vn":
                    self.vertex_normals.append([float(line_seperated[1]), float(line_seperated[2]), float(line_seperated[3])])

    def get_bvh(self):
        return BVH(self.triangles)

    @staticmethod
    def read_mtllib(file_name):
        materials = {}

        with open(file_name) as f:
            current_mtl = None
            for line in f:
                if line[0] == "#" or line.strip() == "":
                    continue

                line_seperated = line.strip().split(" ")

                if line_seperated[0] == "newmtl":
                    current_mtl = line_seperated[1]
                    materials[current_mtl] = {"Ns": [0, 0, 0], "Ka": [0, 0, 0], "Kd": [0, 0, 0],
                                              "Ks": [0, 0, 0], "Tf": 0, "d": 1, "Refl": 0}

                else:
                    if current_mtl is None:
                        raise Exception("File corrupted")

                    if line_seperated[0] == "Ns":
                        materials[current_mtl]["Ns"] = [float(line_seperated[1]),]*3

                    elif line_seperated[0] == "Ka":
                        materials[current_mtl]["Ka"] = [float(item) for item in line_seperated[1:]]

                    elif line_seperated[0] == "Kd":
                        materials[current_mtl]["Kd"] = [float(item) for item in line_seperated[1:]]

                    elif line_seperated[0] == "Ks":
                        materials[current_mtl]["Ks"] = [float(item) for item in line_seperated[1:]]

                    elif line_seperated[0] == "Tf":
                        materials[current_mtl]["Tf"] = float(line_seperated[1])

                    elif line_seperated[0] == "d":
                        materials[current_mtl]["d"] = float(line_seperated[1])

        return_materials = {}

        for mat in materials:
            m = materials[mat]
            return_materials[mat] = Material(m["Ks"], m["Kd"], m["Ka"], m["Ns"], m["Tf"], m["Refl"], m["d"])

        return return_materials
