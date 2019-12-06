import wget

for i in range(1, 121):

	filename = 'AB' + '{:03}'.format(i)
	wget.download('https://www.ime.usp.br/~egbirgin/sources/ab-ellipses/instances/AB/' + filename + '.dat', filename + '.txt')
