#!/usr/bin/python

import sys
import numpy as np
import h5py
import matplotlib.pyplot as plt

def plotStar(fileName):
    f = h5py.File(fileName, 'r')
    w = f['/star/w'][:]
    r = f['/star/r'][:]
    z = f['/star/z'][:]
    th = f['/star/th'][:]

    th = np.r_[[[np.pi/2]], th]
    th[-1,:] = 0
    r = np.r_[[r[0,:]], r]
    r = np.c_[r[:,0], r]

    th = th * np.ones(r.shape[1])

    x = r * np.sin(th)
    y = r * np.cos(th)

    print "x: " + str(x.shape)
    print "y: " + str(y.shape)
    print "w: " + str(w.shape)

    plt.pcolor(x, y, w)
    plt.pcolor(-x, y, w)
    plt.pcolor(x, -y, w)
    plt.pcolor(-x, -y, w)
    plt.colorbar()
    plt.show()

for arg in sys.argv[1:]:
    plotStar(arg)
