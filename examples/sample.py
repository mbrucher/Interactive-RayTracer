#!/usr/bin/env python

import IRT
import numpy

class Sample(object):
  def __init__(self, width = 800, height = 600):
    self.scene = IRT.SimpleScene()
    self.width = width
    self.height = height

    sphere = IRT.Sphere(numpy.array((0., 0., 20.), dtype=numpy.float32), 2.)
    sphere.setColor(numpy.array((0., 0., 1.), dtype=numpy.float32))
    sphere.setDiffuse(1.)
    sphere.setReflection(.5)
    sphere.addToScene(self.scene)
    sphere = IRT.Sphere(numpy.array((2., 1., 15.), dtype=numpy.float32), 1.)
    sphere.setColor(numpy.array((1., 0., 0.), dtype=numpy.float32))
    sphere.setDiffuse(1.)
    sphere.setReflection(.5)
    sphere.addToScene(self.scene)
    sphere = IRT.Sphere(numpy.array((-2., -1., 15.), dtype=numpy.float32), 1.)
    sphere.setColor(numpy.array((.0, 1., .0), dtype=numpy.float32))
    sphere.setReflection(.5)
    sphere.setDiffuse(1.)
    sphere.addToScene(self.scene)

    box = IRT.Box(numpy.array((-8., 4., 26.), dtype=numpy.float32), numpy.array((8., 10., 1000.), dtype=numpy.float32))
    box.setColor(numpy.array((.95, .95, .95), dtype=numpy.float32))
    box.setReflection(.25)
    #self.scene.addPrimitive(box)
    
    triangle = IRT.Triangle(numpy.array((-6., 0., 30.), dtype=numpy.float32), numpy.array((6., 6., 28.), dtype=numpy.float32), numpy.array((0., -6., 28.), dtype=numpy.float32))
    triangle.setColor(numpy.array((1., 1., 1.), dtype=numpy.float32))
    triangle.setReflection(.1)
    triangle.setDiffuse(.4)
    self.scene.addTriangle(triangle)

    light = IRT.Light(1e6 * numpy.array((-2., 2., 1.), dtype=numpy.float32), 49 * 1e12 * numpy.array((.0, .2, .2), dtype=numpy.float32))
    self.scene.addLight(light)
    light = IRT.Light(1e6 * numpy.array((2., -2., 1.), dtype=numpy.float32), 49 * 1e12 * numpy.array((.2, .0, .2), dtype=numpy.float32))
    self.scene.addLight(light)
    light = IRT.Light(1e6 * numpy.array((0., 0., -9.), dtype=numpy.float32), 49 * 1e12 * numpy.array((.4, .4, .4), dtype=numpy.float32))
    self.scene.addLight(light)

    IRT.BuildKDTree.automatic_build(self.scene)

  def __call__(self, screen):
    self.raytracer.draw(screen)
  
  def hitLevel(self, screen):
    self.raytracer.checkDraw(screen, 0)
  
  def setResolution(self, width, height):
    self.raytracer.setResolution(width, height)

  def setRaytracer(self, Raytracer):
    self.raytracer = Raytracer(self.width, self.height)

    self.raytracer.setSize(16., 12.)
    self.origin = numpy.array((.0, .0, .0), dtype=numpy.float32)
    self.direction = numpy.array((.0, .0, 20.), dtype=numpy.float32)
    self.raytracer.setViewer(self.origin, self.direction)
    self.orientation = numpy.array((.0, .1, .0), dtype=numpy.float32)
    self.raytracer.setOrientation(self.orientation)

    self.raytracer.setOversampling(2)
    self.raytracer.setLevels(3)

    self.raytracer.setScene(self.scene)
