#!/usr/bin/env python

import numpy
import sample
import pylab

import IRT

s = sample.Sample()
s.setRaytracer(IRT.Raytracer_Uniform)

screen = numpy.zeros((600, 800, 3), dtype=numpy.float32)
s(screen)

pylab.imshow(screen)
#pylab.imshow(screen[30:130, 460:500])
pylab.show()
