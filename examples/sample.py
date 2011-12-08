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
    self.scene.addPrimitive(sphere)
    sphere = IRT.Sphere(numpy.array((2., 1., 15.), dtype=numpy.float32), 1.)
    sphere.setColor(numpy.array((1., 0., 0.), dtype=numpy.float32))
    sphere.setDiffuse(1.)
    sphere.setReflection(.5)
    self.scene.addPrimitive(sphere)
    sphere = IRT.Sphere(numpy.array((-2., -1., 15.), dtype=numpy.float32), 1.)
    sphere.setColor(numpy.array((.0, 1., .0), dtype=numpy.float32))
    sphere.setReflection(.5)
    sphere.setDiffuse(1.)
    self.scene.addPrimitive(sphere)

    Box = IRT.Box(numpy.array((-8., 4., 26.), dtype=numpy.float32), numpy.array((8., 10., 1000.), dtype=numpy.float32))
    Box.setColor(numpy.array((.95, .95, .95), dtype=numpy.float32))
    Box.setReflection(.25)
#    self.scene.addPrimitive(Box)

    light = IRT.Light(numpy.array((-5., 2., 0.), dtype=numpy.float32), numpy.array((.0, .2, .2), dtype=numpy.float32))
    self.scene.addLight(light)
    light = IRT.Light(numpy.array((5., -2., 0.), dtype=numpy.float32), numpy.array((.2, .0, .2), dtype=numpy.float32))
    self.scene.addLight(light)
    light = IRT.Light(numpy.array((0., -5., 2.), dtype=numpy.float32), numpy.array((.4, .4, .4), dtype=numpy.float32))
    self.scene.addLight(light)

    IRT.BuildKDTree.automatic_build(self.scene)

  def __call__(self, screen):
    self.raytracer.draw(screen)

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

    self.raytracer.setOversampling(8)
    #self.raytracer.setLevels(0)

    self.raytracer.setScene(self.scene)
