import os
from parser import *
import signal

def handler(signum, frame):
	print("timeout")
	raise Exception("Timeout")

def f(filenamebase, rng, cmd, outfilename):
	n, m = 0, 0

	fw = open(outfilename, "w+")

	for i in rng:
		filename = filenamebase.format(i)

		instance = parse_input(f'input/{filename}.txt')

		signal.signal(signal.SIGALRM, handler)
		signal.alarm(7200)

		sol=[]
		
		try:
			line = os.popen('./' + cmd + '< input/' + filename + '.txt --print-list').read()
			sol = line.split(';')
		except Exception:
			if cmd == 'mce':
				sol = [str(instance.n), str(instance.m), str(instance.k), '-', '-', '-', '-', '-', '-', '-']
			else:
				sol = [str(instance.n), str(instance.m), str(instance.k), '-', '-', '-', '-', '-', '-', '-', '-']

		signal.alarm(0)

		if instance.n != n or instance.m != m:
			if n!=0 and m != 0:
				fw.write('\hline\n')
			sol[0] = '\\multirow{'+str(instance.m)+'}{*}{' + sol[0] + '}'
			sol[1] = '\\multirow{'+str(instance.m)+'}{*}{' + sol[1] + '}'
			if len(sol) == 11:
				sol[6] = '\\multirow{'+str(instance.m)+'}{*}{' + sol[6] + '}'
		else:
			sol[0] = " "  
			sol[1] = " " 
			if len(sol) == 11:
				sol[6] = " "

		fw.write(filename +"&"+ "&".join(sol) + "\\\\")
		
		n = instance.n
		m = instance.m

	fw.close();

#f('AB{:03}', range(1, 61), 'mce', 'table_mcek_ab_1.tex')
#f('AB{:03}', range(61, 121), 'mce', 'table_mcek_ab_2.tex')
#f('CM{:01}', range(1, 10), 'mce', 'table_mcek_cm.tex')
#f('AB{:03}', range(1, 61), 'mcerk', 'table_mcerk_ab_1.tex')
#f('AB{:03}', range(61, 121), 'mcerk', 'table_mcerk_ab_2.tex')
#f('CM{:01}', range(1, 10), 'mcerk', 'table_mcerk_cm.tex')

f('TA{:03}', range(1, 8), 'mcerk', 'table_mcerk_ta_1.tex')
f('TA{:03}', range(1, 8), 'mce', 'table_mcek_ta_1.tex')

#f('TA{:03}', range(8, 17), 'mcerk', 'table_mcerk_ta_2.tex')
#f('TA{:03}', range(8, 17), 'mce', 'table_mcek_ta_2.tex')

f('TA{:03}', range(20, 23), 'mcerk', 'table_mcerk_ta_3.tex')
f('TA{:03}', range(20, 23), 'mce', 'table_mcek_ta_3.tex')

f('TA{:03}', range(23, 38), 'mcerk', 'table_mcerk_ta_4.tex')
f('TA{:03}', range(23, 38), 'mce', 'table_mcek_ta_4.tex')
