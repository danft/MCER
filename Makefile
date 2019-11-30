CC=g++
CFLAGS=-llapack -g

main: poly_function.o eig.o e3p.cpp
	$(CC) poly_function.o eig.o e3p.cpp -o main $(CFLAGS)

eig.o: eig.cpp eig.h
	$(CC) -c eig.cpp -o eig.o $(CFLAGS)

poly_function.o: poly_function.cpp poly_function.h
	$(CC) -c poly_function.cpp -o poly_function.o $(CFLAGS)
