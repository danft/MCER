import os
from parser import *
import signal

def handler(signum, frame):
	print("timeout")
	raise Exception("Timeout")

def f(filenamebase, rng, cmd):
	n, m = 0, 0

	for i in rng:
		filename = filenamebase.format(i)

		signal.signal(signal.SIGALRM, handler)
		signal.alarm(7200)

		sol=[]
		
		try:
			os.popen('./' + cmd + '< input/' + filename + '.txt --print-info --precision 17 > output/'+ cmd + '-' + filename + '.txt')

		except Exception:
			print (filename + "TIMED OUT")

		signal.alarm(0)

f('AB{:03}', range(1, 121), 'mce')
f('CM{:01}', range(1, 10), 'mce')
f('AB{:03}', range(1, 121), 'mcerk')
f('CM{:01}', range(1, 10), 'mcerk')
f('TA{:03}', range(1, 48), 'mce')
f('TA{:03}', range(1, 48), 'mcerk')
