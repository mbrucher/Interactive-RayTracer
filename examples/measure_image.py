#!/usr/bin/env python

# Matthieu Brucher
# Last Change : 2009-05-30 16:54

import numpy
import sample
  
s = sample.Sample()
s.setRaytracer(IRT.Raytracer_Uniform)

screen = numpy.zeros((600, 800, 3), dtype=numpy.float32)
s(screen)
