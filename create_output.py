import os
from parser import *
import signal
import subprocess

def handler(signum, frame):
	print("timeout")
	raise Exception("Timeout")

def f(filenamebase, rng, cmd):
	n, m = 0, 0

	for i in rng:
		filename = filenamebase.format(i)

		if os.path.exists('output/' + cmd + '-' + filename + '.txt'):
			continue

		#signal.signal(signal.SIGALRM, handler)
		#signal.alarm(10)

		sol=[]
		
		
		try:
			proc = subprocess.Popen('./' + cmd + '< input/' + filename + '.txt --print-info --precision 17 > output/'+ cmd + '-' + filename + '.txt', shell=True, preexec_fn=os.setsid)
			proc.wait(7200)

		except subprocess.TimeoutExpired:
			os.remove('output/' + cmd + '-' + filename + '.txt')
			os.killpg(os.getpgid(proc.pid), signal.SIGTERM)
			print (filename + "TIMED OUT")

		signal.alarm(0)

f('AB{:03}', range(1, 121), 'mce')
f('CM{:01}', range(1, 10), 'mce')
f('AB{:03}', range(1, 121), 'mcerk')
f('CM{:01}', range(1, 10), 'mcerk')
f('TA{:03}', range(1, 48), 'mce')
f('TA{:03}', range(1, 48), 'mcerk')
