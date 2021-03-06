#!/usr/bin/env python

import matplotlib.pyplot as plt

if __name__ == "__main__":
  import sys
  from display_dat import hitdistance_dat

  im = hitdistance_dat(sys.argv[1])

  plt.imshow(im)
  plt.colorbar()
  plt.show()
