import matplotlib.pyplot as plt
import math
import sys

UP = 0.381
SPIRALS = 20
OUTSIDE_X_RADIUS = 25.4 - 0.381
INSIDE_X_RADIUS = 9.525
OUTSIDE_Y_RADIUS = 28.575 - UP * 2
INSIDE_Y_RADIUS = 9.525
OUTSIDE_POW = 4
INSIDE_POW = 1
CHANGE_POW = OUTSIDE_POW / 2
N = 5000
WIDTH = 0.6096
LAYER = "F.Cu"
CENTER_X = 197.612
CENTER_Y = 106.553 - UP
START = 0.25

def sp(x, p):
    return math.copysign(abs(x) ** (1 / p), x)

def f(t):
    x_r = (1 - t) * INSIDE_X_RADIUS + t * OUTSIDE_X_RADIUS
    y_r = (1 - t) * INSIDE_Y_RADIUS + t * OUTSIDE_Y_RADIUS
    theta = (2 * math.pi * (t * SPIRALS + START))
    t2 = t ** CHANGE_POW
    p = (1 - t2) * INSIDE_POW + t2 * OUTSIDE_POW
    x = x_r * sp(math.cos(theta), p) + CENTER_X
    y = y_r * sp(math.sin(theta), p) + CENTER_Y
    return (x, y)

pts = []
for i in range(0, N + 1):
    pts.append(f(i / N))

#(x, y) = zip(*pts)
#plt.plot(x, y)
#plt.gca().set_aspect('equal')
#plt.show()

length = 0
for ((x1, y1), (x2, y2)) in zip(pts[:-1], pts[1:]):
    print("  (segment (start {} {}) (end {} {}) (width {}) (layer {}))".format(x1, y1, x2, y2, WIDTH, LAYER))
    length += math.hypot(x2 - x1, y2 - y1)
print(length, file=sys.stderr)
