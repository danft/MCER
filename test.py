import os

for i in range(1, 121):
	filename = 'AB' + '{:03}'.format(i)
	os.system('./mcer < instances/' + filename + '.txt > solutions/' + filename + '.txt')
