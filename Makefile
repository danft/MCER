CC=g++
CFLAGS=-llapack -g

main: eig.o e3p.cpp
	$(CC) eig.o e3p.cpp -o main $(CFLAGS)

eig.o: eig.cpp eig.h
	$(CC) -c eig.cpp -o eig.o $(CFLAGS)
