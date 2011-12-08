#!/usr/bin/env python

import numpy
import sample
import IRT

s = sample.Sample()
s.setRaytracer(IRT.Raytracer_Uniform)

screen = numpy.zeros((600, 800, 3), dtype=numpy.float32)
s(screen)
