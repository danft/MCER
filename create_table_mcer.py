import os

for i in range(1, 61):
	filename = 'AB' + '{:03}'.format(i)
	line = os.popen('./mcerk < input/' + filename + '.txt --print-table').read()

	print(f"{filename} & {line}");
