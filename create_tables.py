import os
from parser import *


def f(filenamebase, rng, cmd, outfilename):
	n, m = 0, 0

	fw = open(outfilename, "w+")

	for i in rng:
		filename = filenamebase.format(i)

		instance = parse_input(f'input/{filename}.txt')

		line = os.popen('./' + cmd + '< input/' + filename + '.txt --print-list').read()
		sol = line.split(';')

		if instance.n != n or instance.m != m:
			if n!=0 and m != 0:
				fw.write('\hline\n')
			sol[0] = '\\multirow{'+str(instance.m)+'}{*}{' + sol[0] + '}'
			sol[1] = '\\multirow{'+str(instance.m)+'}{*}{' + sol[1] + '}'
			#sol[5] = '\\multirow{'+str(m)+'}{*}{' + sol[5] + '}'
		else:
			sol[0] = " "  
			sol[1] = " " 
			#sol[5] = " "

		fw.write(filename +"&"+ "&".join(sol) + "\\\\")
		
		n = instance.n
		m = instance.m

	fw.close();

f('AB{:03}', range(1, 61), 'mce', 'table_mcek_ab_1.tex')
f('AB{:03}', range(61, 121), 'mce', 'table_mcek_ab_2.tex')
f('CM{:01}', range(1, 10), 'mce', 'table_mcek_cm.tex')
f('AB{:03}', range(1, 61), 'mcerk', 'table_mcerk_ab_1.tex')
f('AB{:03}', range(61, 121), 'mcerk', 'table_mcerk_ab_2.tex')
f('CM{:01}', range(1, 10), 'mcerk', 'table_mcerk_cm.tex')

f('TA{:03}', range(1, 9), 'mcerk', 'table_mcerk_ta_1.tex')
f('TA{:03}', range(1, 9), 'mce', 'table_mcek_ta_1.tex')


