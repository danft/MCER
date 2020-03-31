import os
from parser import *
import signal
import subprocess
import numpy as np
import matplotlib.pyplot as plt
from math import atan, cos, sin, pi

def eval_ellipse(theta, a, b, xc, yc, x, y):
    X = x - xc
    Y = y - yc

    return (X * cos(theta) + Y * sin(theta)) ** 2 / a ** 2 + (
            X * sin(theta) - Y * cos(theta)) ** 2 / b ** 2

def parse(filename):
	of = open(filename, 'r')
	line = of.readline()
	n, m, k = map(int, line.split())	

	a = []
	b = []

	line = of.readline().split(',')
	for i in range(m):
		a.append(float(line[i]))
	
	line = of.readline().split(',')
	for i in range(m):
		b.append(float(line[i]))

	#wel
	of.readline()

	X = []
	Y = []

	line = of.readline().split(',')
	for i in range(n):
		X.append(float(line[i]))

	line = of.readline().split(',')
	for i in range(n):
		Y.append(float(line[i]))
	
	#wpnt
	of.readline()

	sol = []
	used = []

	line = of.readline().split(',')
	for i in range(m):
		used.append(int(line[i]))

	line = of.readline().split(',')
	for i in range(k):
		sol.append((float(line[3*i]), float(line[3*i+1]), float(line[3*i+2])))
	
	of.close()
	return a, b, X, Y, used, sol

def fx(a, b, X, Y, used, sol, lw=3, s=30):

	colors = plt.rcParams['axes.prop_cycle'].by_key()['color']

	def fig_ax(w=4, h=4):
		fig,ax = plt.subplots(subplot_kw={'aspect': 'equal'}, figsize=(w, h))
		ax.axis('off')

		return fig, ax


	def plt_points(ax, X, Y, a, b, sol, used):
		n=len(X)
		m=len(a)

		ans = 0

		for i in range(n):
			covered = False
			x, y = X[i], Y[i]

			j = 0
			for jj in range(m):
				if not used[jj]:
					continue

				xc, yc, theta = sol[j]

				if eval_ellipse(theta, a[jj], b[jj], xc, yc, x, y) - 1e-9 < 1:
					covered = True
				j+=1

			if covered:
				ax.scatter(x, y, zorder=10, color='black', s = s, marker='o')
			else:
				ax.scatter(x, y, zorder=10, color='gray', s = s, marker='o')

	def ell_curve(a, b, xc, yc, theta):
		t = np.linspace(0, 2*pi, 1000)
		a+=1e-7
		b+=1e-7
		X = a * np.cos(t)
		Y = b * np.sin(t)

		XX = X * np.cos(-theta) + Y * np.sin(-theta)
		YY = Y * np.cos(-theta) - X * np.sin(-theta)
		XX += xc
		YY += yc

		return XX, YY

	def plt_sols(ax, a, b, sol, used):
		m=len(a)
		j = 0

		for i in range(m):

			if not used[i]:
				continue

			xc, yc, theta = sol[j]

			ax.plot(*ell_curve(a[i], b[i], xc, yc, theta), lw=lw, color=colors[i])
			j+=1


	fig, ax = fig_ax()
	plt_points(ax, X, Y, a, b, sol, used)
	plt_sols(ax, a, b, sol, used)
	return fig, ax

def f(filenamebase, rng, cmd):


	for i in rng:
		fbase = filenamebase.format(i)
		fbase = cmd + '-' + fbase 
		filename = 'output/' + fbase + '.txt'

		if not os.path.exists(filename):
			continue

		cx = parse(filename)

		fig, ax = fx(*cx)
		fig.savefig('graphical_output/'+fbase+'.pdf', bbox_inches="tight") 

f('AB{:03}', range(1, 121), 'mce')
f('CM{:01}', range(1, 10), 'mce')
f('AB{:03}', range(1, 121), 'mcerk')
f('CM{:01}', range(1, 10), 'mcerk')
f('TA{:03}', range(1, 48), 'mce')
f('TA{:03}', range(1, 48), 'mcerk')
