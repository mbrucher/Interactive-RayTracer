#!/usr/bin/env python

import IRT
import numpy as np

class ParserTest:
  def handle_none(self, elements):
    pass

  def handle_size(self, elements):
    self.raytracer_params["RESOLUTION"] = (int(elements[0]), int(elements[1]))

  def handle_output(self, elements):
    self.raytracer_params["OUTPUT"] = elements[0]

  def handle_camera(self, elements):
    self.raytracer_params['EYE'] = np.array([float(el) for el in elements[0:3]])
    self.raytracer_params['CENTER'] = np.array([float(el) for el in elements[3:6]])
    self.raytracer_params['UPDIR'] = np.array([float(el) for el in elements[6:9]])
    self.raytracer_params['FOVY'] = float(elements[9])

  def handle_point(self, elements):
    light = {}
    light["CENTER"] = np.array([float(el) for el in elements[0:3]])
    light["COLOR"] = np.array([float(el) for el in elements[3:]])

    self.lights.append(light)

  def handle_ambient(self, elements):
    self.textures["AMBIENT"] = np.array([float(el) for el in elements])

  def handle_emission(self, elements):
    self.textures["EMISSION"] = np.array([float(el) for el in elements])

  def handle_diffuse(self, elements):
    self.textures["DIFFUSE"] = np.array([float(el) for el in elements])

  def handle_specular(self, elements):
    self.textures["SPECULAR"] = np.array([float(el) for el in elements])

  def handle_shininess(self, elements):
    self.textures["SHININESS"] = float(elements[0])

  def handle_vertex(self, elements):
    elements.append(1)
    self.vertex.append(np.array([float(el) for el in elements]))

  def handle_push(self, elements):
    self.transforms.append(np.array(self.transforms[-1]))

  def handle_pop(self, elements):
    self.transforms.pop()

  def handle_scale(self, elements):
    scale = np.diag((float(elements[0]), float(elements[1]), float(elements[2]), 1))
    self.transforms[-1] = np.dot(self.transforms[-1], scale)

  def handle_translate(self, elements):
    translate = np.eye(4)
    translate[0:3, 3] = np.array([float(el) for el in elements])
    self.transforms[-1] = np.dot(self.transforms[-1], translate)

  def handle_rotate(self, elements):
    axis = np.array([float(el) for el in elements[:3]])
    theta = float(elements[3]) * np.pi / 180
  
    rotation = np.eye(4)
    rotation[0:3, 0:3] = np.eye(3) * np.cos(theta) + np.outer(axis, axis) * (1 - np.cos(theta)) + np.array(((0, -axis[0], axis[1]), (axis[2], 0, -axis[2]), (-axis[1], axis[0], 0))).T * np.sin(theta)
    self.transforms[-1] = np.dot(self.transforms[-1], rotation)

  def handle_triangle(self, elements):
    current_transform = self.transforms[-1]
    corner1 = np.dot(current_transform, self.vertex[int(elements[0])])
    corner2 = np.dot(current_transform, self.vertex[int(elements[0])])
    corner3 = np.dot(current_transform, self.vertex[int(elements[0])])
    triangle = {'type' : 'TRI'}
    triangle['V0'] = corner1[0:3]/corner1[3]
    triangle['V1'] = corner3[0:3]/corner2[3]
    triangle['V2'] = corner3[0:3]/corner3[3]
    triangle['TEXTURE'] = self.textures.copy()
    self.objects.append(triangle)

  def handle_sphere(self, elements):
    current_transform = self.transforms[-1]
    center = [float(el) for el in elements[:3]]
    center.append(1)
    center = np.dot(current_transform, center)
    sphere = {'type' : 'SPHERE'}
    sphere['CENTER'] = center[0:3]/center[3]
    sphere['RAD'] = float(elements[3])
    sphere['TEXTURE'] = self.textures.copy()
    self.objects.append(sphere)

  handle = {
             'size' : handle_size,
             'output' : handle_output,
             'camera' : handle_camera,
             'point' : handle_point,
             'ambient' : handle_ambient,
             'emission' : handle_emission,
             'diffuse' : handle_diffuse,
             'specular' : handle_specular,
             'shininess' : handle_shininess,
             'maxverts': handle_none,
             'vertex': handle_vertex,
             'pushTransform': handle_push,
             'popTransform': handle_pop,
             'scale': handle_scale,
             'translate': handle_translate,
             'rotate': handle_rotate,
             'tri': handle_triangle,
             'sphere': handle_sphere,
           }

  def __init__(self, file):
    self.file = file

    self.raytracer_params = {}
    self.textures = {}
    self.lights = []
    self.objects = []
    self.vertex = []

    self.state = [None]
    self.transforms = [np.eye(4)]

  def parse(self):
    for line in open(self.file):
      line = line.strip()
      if line != "" and line[0] != '#':
        elements = line.split()
        ParserTest.handle[elements[0]](self, elements[1:])

  def populate(self, scene):
    self.populate_lights(scene)
    self.populate_objects(scene)

  def populate_lights(self, scene):
    for object in self.lights:
      light = IRT.Light(object['CENTER'], 20 * object['COLOR'])
      scene.addLight(light)

  def populate_objects(self, scene):
    for object in self.objects:
      if object['type'] == 'SPHERE':
        sphere = IRT.Sphere(object['CENTER'], object['RAD'])
        sphere.diffuse_color = (object['TEXTURE']['DIFFUSE'])
        sphere.specular_color = (object['TEXTURE']['SPECULAR'])
        sphere.emission_color = (object['TEXTURE']['EMISSION'])
        sphere.shininess = (object['TEXTURE']['SHININESS'])
        sphere.reflection = 1
        scene.addPrimitive(sphere)
      if object['type'] == 'TRI':
        triangle = IRT.Triangle(object['V0'], object['V1'], object['V2'])
        triangle.diffuse_color = (object['TEXTURE']['DIFFUSE'])
        triangle.specular_color = (object['TEXTURE']['SPECULAR'])
        triangle.emission_color = (object['TEXTURE']['EMISSION'])
        triangle.shininess = (object['TEXTURE']['SHININESS'])
        triangle.reflection = 1
        scene.addPrimitive(triangle)

  def create(self, Raytracer, scene):
    raytracer = Raytracer(*self.raytracer_params['RESOLUTION'])

    up_size = np.tan(self.raytracer_params['FOVY'] / 2 * np.pi / 180)
    raytracer.size = (up_size * self.raytracer_params['RESOLUTION'][0] / self.raytracer_params['RESOLUTION'][1], up_size)
    raytracer.viewer = (self.raytracer_params['CENTER'], self.raytracer_params['CENTER'] - self.raytracer_params['EYE'])
    raytracer.orientation = (self.raytracer_params['UPDIR'])

    if 'ANTIALIASING' in self.raytracer_params and self.raytracer_params['ANTIALIASING'] ==  1:
      self.raytracer.oversampling = (4)

    scene.ambient_color = self.textures["AMBIENT"]
    
    raytracer.scene = (scene)
    #IRT.BuildKDTree.custom_build(scene, 0, 0, 0)
    IRT.BuildKDTree.automatic_build(scene)
    return raytracer

  def create_image(self, raytracer):
    import time
    screen = np.zeros((self.raytracer_params['RESOLUTION'][1], self.raytracer_params['RESOLUTION'][0], 3), dtype=np.float32)
    current = time.time()
    raytracer.draw(screen)
    print("Elapsed %f" % (time.time() - current))
    return screen
    
def parse_test(file):
  scene = IRT.SimpleScene()

  parser = ParserTest(file)
  parser.parse()
  parser.populate(scene)
  raytracer = parser.create(IRT.Raytracer_Uniform, scene)

  im = parser.create_image(raytracer)
  return im
if __name__ == "__main__":
  import sys
  import matplotlib.pyplot as plt
  from PIL import Image
  
  im = parse_test(sys.argv[1])

  image = Image.frombuffer('RGB', (im.shape[:2]), im, "raw", "RGB", 0, 1)
  
  plt.imshow(im)
  plt.show()
