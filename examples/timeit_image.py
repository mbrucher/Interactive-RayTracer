#!/usr/bin/env python

import timeit

setup="""import numpy
import sample
import pylab
import IRT

s = sample.Sample()
s.setRaytracer(IRT.Raytracer_Uniform)

screen = numpy.zeros((600, 800, 3), dtype=numpy.float32)
"""

timer = timeit.Timer('s(screen)', setup=setup)

print timer.timeit(10) / 10
