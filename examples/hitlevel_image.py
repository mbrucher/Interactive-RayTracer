#!/usr/bin/env python

import numpy
import sample
import matplotlib.pyplot as plt

import IRT

s = sample.Sample()
s.setRaytracer(IRT.Raytracer_Jittered)

screen = numpy.zeros((600, 800), dtype=numpy.long)
s.hitLevel(screen)

plt.imshow(screen)
plt.colorbar()
plt.show()
