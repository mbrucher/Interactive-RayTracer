import numpy as np

times = np.loadtxt("examples/times")

from matplotlib import pyplot as plt

plt.plot(times[:, 0], times[0, 1] / times[:, 1], label="Speed up")
plt.plot(times[:, 0], times[:, 0], label="Theoretical speedup")
plt.legend()
plt.show()

