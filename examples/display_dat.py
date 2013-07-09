#!/usr/bin/env python

import IRT
import numpy

class ParserDat(object):
  def handle_start(self, elements):
    if elements[0] == "BEGIN_SCENE":
      self.state.append("SCENE")

  def handle_scene(self, elements):
    if elements[0] == "RESOLUTION":
      self.raytracer_params['RESOLUTION'] = int(elements[1]), int(elements[2])
    if elements[0] == "CAMERA":
      self.state.append("CAMERA")
    if elements[0] == "LIGHT":
      self.parse_light(elements[1:])
    if elements[0] == "SPHERE":
      self.parse_sphere(elements[1:])
      self.state.append("SPHERE")
    if elements[0] == "TRI":
      self.parse_triangle(elements[1:])
      self.state.append("TRI")
    if elements[0] == "TEXDEF":
      self.parse_texture(elements[1:])
      self.state.append("TEXDEF")

  def handle_camera(self, elements):
    if elements[0] == "END_CAMERA":
      self.state = self.state[:-1]
    if elements[0] == "ZOOM":
      self.raytracer_params['ZOOM'] = float(elements[1])
    if elements[0] == "ASPECTRATIO":
      self.raytracer_params['ASPECTRATIO'] = float(elements[1])
    if elements[0] == "ANTIALIASING":
      self.raytracer_params['ANTIALIASING'] = int(elements[1])
    if elements[0] == "RAYDEPTH":
      self.raytracer_params['RAYDEPTH'] = int(elements[1])
    if elements[0] == "CENTER":
      self.raytracer_params['CENTER'] = numpy.array((elements[1], elements[2], elements[3]), dtype=numpy.float32)
    if elements[0] == "VIEWDIR":
      self.raytracer_params['VIEWDIR'] = numpy.array((elements[1], elements[2], elements[3]), dtype=numpy.float32)
    if elements[0] == "UPDIR":
      self.raytracer_params['UPDIR'] = numpy.array((elements[1], elements[2], elements[3]), dtype=numpy.float32)

  def parse_light(self, elements):
    light = {}
    while len(elements) > 0:
      if elements[0] == 'CENTER':
        light['CENTER'] = numpy.array((elements[1], elements[2], elements[3]), dtype=numpy.float32)
        del elements[0:4]
      elif elements[0] == 'COLOR':
        light['COLOR'] = numpy.array((elements[1], elements[2], elements[3]), dtype=numpy.float32)
        del elements[0:4]
      elif elements[0] == 'RAD':
        light['RAD'] = float(elements[1])
        del elements[0:2]
      else:
        break
    self.lights.append(light)

  def parse_for_sphere(self, sphere, elements):
    while len(elements) > 0:
      if elements[0] == 'CENTER':
        sphere['CENTER'] = numpy.array((elements[1], elements[2], elements[3]), dtype=numpy.float32)
        del elements[0:4]
      elif elements[0] == 'RAD':
        sphere['RAD'] = float(elements[1])
        del elements[0:2]
      elif len(elements) == 1 and elements[0] != "END_SCENE":
        sphere['TEXTURE'] = elements[0]
        del elements[0]
      else:
        break

  def parse_sphere(self, elements):
    sphere = {'type' : 'SPHERE'}
    self.objects.append(sphere)
    self.parse_for_sphere(sphere, elements)

  def handle_sphere(self, elements):
    if elements[0] == 'SPHERE':
      self.parse_sphere(elements[1:])
    else:
      self.parse_for_sphere(self.objects[-1], elements)
      if len(elements) > 0:
        self.state = self.state[:-1]
        self.handle_line(elements)

  def parse_for_triangle(self, triangle, elements):
    while len(elements) > 0:
      if elements[0] == 'V0':
        triangle['V0'] = numpy.array((elements[1], elements[2], elements[3]), dtype=numpy.float32)
        del elements[0:4]
      elif elements[0] == 'V1':
        triangle['V1'] = numpy.array((elements[1], elements[2], elements[3]), dtype=numpy.float32)
        del elements[0:4]
      elif elements[0] == 'V2':
        triangle['V2'] = numpy.array((elements[1], elements[2], elements[3]), dtype=numpy.float32)
        del elements[0:4]
      elif len(elements) == 1 and elements[0] != "END_SCENE":
        triangle['TEXTURE'] = elements[0]
        del elements[0]
      else:
        break

  def parse_triangle(self, elements):
    triangle = {'type' : 'TRI'}
    self.objects.append(triangle)
    self.parse_for_triangle(triangle, elements)

  def handle_triangle(self, elements):
    if elements[0] == 'TRI':
      self.parse_triangle(elements[1:])
    else:
      self.parse_for_triangle(self.objects[-1], elements)
      if len(elements) > 0:
        self.state = self.state[:-1]
        self.handle_line(elements)

  def parse_texture(self, elements):
    texture = {}
    self.current_texture = elements[0]
    self.textures[self.current_texture] = texture
    self.parse_for_texture(texture, elements[1:])
  
  def parse_for_texture(self, texture, elements):
    while len(elements) > 0:
      if elements[0] == 'COLOR':
        texture['COLOR'] = numpy.array((elements[1], elements[2], elements[3]), dtype=numpy.float32)
        del elements[0:4]
      elif elements[0] == 'AMBIENT':
        texture['AMBIENT'] = float(elements[1])
        del elements[0:2]
      elif elements[0] == 'DIFFUSE':
        texture['DIFFUSE'] = float(elements[1])
        del elements[0:2]
      elif elements[0] == 'SPECULAR':
        texture['SPECULAR'] = float(elements[1])
        del elements[0:2]
      elif elements[0] == 'OPACITY':
        texture['OPACITY'] = float(elements[1])
        del elements[0:2]
      elif elements[0] == 'TEXFUNC':
        texture['TEXFUNC'] = float(elements[1])
        del elements[0:2]
      elif elements[0] == 'PHONG':
        texture['PHONG'] = elements[1:5]
        del elements[0:5]
      else:
        return

  def handle_texture(self, elements):
    if elements[0] == 'TEXDEF':
      self.parse_texture(elements[1:])
    else:
      self.parse_for_texture(self.textures[self.current_texture], elements)
      if len(elements) > 0:
        self.state = self.state[:-1]
        self.handle_line(elements)

  handle = {
             None : handle_start,
             "SCENE" : handle_scene,
             "CAMERA" : handle_camera,
             "SPHERE" : handle_sphere,
             "TRI" : handle_triangle,
             "TEXDEF" : handle_texture,
           }

  def __init__(self, file):
    self.file = file

    self.raytracer_params = {}
    self.textures = {}
    self.lights = []
    self.objects = []

    self.state = [None]

  def parse(self):
    for line in open(self.file):
      line = line.strip()
      if line != "":
        elements = line.split()
        self.handle_line(elements)

  def handle_line(self, elements):
    if self.state[-1] in ParserDat.handle:
      ParserDat.handle[self.state[-1]](self, elements)

  def populate(self, scene):
    self.populate_lights(scene)
    self.populate_objects(scene)

  def populate_lights(self, scene):
    for object in self.lights:
      light = IRT.Light(object['CENTER'], object['COLOR'])
      scene.addLight(light)

  def populate_objects(self, scene):
    for object in self.objects:
      if object['type'] == 'SPHERE':
        sphere = IRT.Sphere(object['CENTER'], object['RAD'])
        sphere.setColor(self.textures[object['TEXTURE']]['COLOR'])
        sphere.setReflection(self.textures[object['TEXTURE']]['SPECULAR'])
        sphere.setDiffuse(self.textures[object['TEXTURE']]['DIFFUSE'])
        scene.addPrimitive(sphere)
      if object['type'] == 'TRI':
        triangle = IRT.Triangle(object['V0'], object['V1'], object['V2'])
        triangle.setColor(self.textures[object['TEXTURE']]['COLOR'])
        triangle.setReflection(self.textures[object['TEXTURE']]['SPECULAR'])
        triangle.setDiffuse(self.textures[object['TEXTURE']]['DIFFUSE'])
        scene.addPrimitive(triangle)

  def create(self, Raytracer, scene):
    raytracer = Raytracer(*self.raytracer_params['RESOLUTION'])

    raytracer.setSize(self.raytracer_params['ZOOM'], self.raytracer_params['ZOOM'] * self.raytracer_params['ASPECTRATIO'])
    raytracer.setViewer(self.raytracer_params['CENTER'], self.raytracer_params['VIEWDIR'])
    raytracer.setOrientation(self.raytracer_params['UPDIR'])

    if 'ANTIALIASING' in self.raytracer_params and self.raytracer_params['ANTIALIASING'] ==  1:
      self.raytracer.setOversampling(4)

    raytracer.setScene(scene)
    #IRT.BuildKDTree.custom_build(scene, 0, 0, 0)
    IRT.BuildKDTree.automatic_build(scene)
    return raytracer
  
  def create_image(self, raytracer):
    import time
    screen = numpy.zeros((self.raytracer_params['RESOLUTION'][0], self.raytracer_params['RESOLUTION'][1], 3), dtype=numpy.float32)
    current = time.time()
    raytracer.draw(screen)
    print "Elapsed %f" % (time.time() - current)
    return screen
  
  def create_hitlevel(self, raytracer):
    import time
    screen = numpy.zeros((self.raytracer_params['RESOLUTION'][0], self.raytracer_params['RESOLUTION'][1]), dtype=numpy.long)
    current = time.time()
    raytracer.checkDraw(screen, 0)
    print "Elapsed %f" % (time.time() - current)
    return screen

def parse_dat(file):
  scene = IRT.SimpleScene()

  parser = ParserDat(file)
  parser.parse()
  parser.populate(scene)
  raytracer = parser.create(IRT.Raytracer_Jittered, scene)
  #raytracer.setOversampling(1)
  #raytracer.setLevels(0)

  im = parser.create_image(raytracer)
  return im

def hitlevel_dat(file):
  scene = IRT.SimpleScene()
  
  parser = ParserDat(file)
  parser.parse()
  parser.populate(scene)
  raytracer = parser.create(IRT.Raytracer_Jittered, scene)
  #raytracer.setOversampling(1)
  #raytracer.setLevels(0)
  
  im = parser.create_hitlevel(raytracer)
  return im

if __name__ == "__main__":
  import sys
  import matplotlib.pyplot as plt

  im = parse_dat(sys.argv[1])

  plt.imshow(im)
  plt.show()
