CC=g++
CXXFLAGS=-llapack -g

mcer: mcer.cpp e3p.o instance.o eig.o poly_function.o
	$(CC) mcer.cpp instance.o e3p.o eig.o poly_function.o -o mcer $(CXXFLAGS)

instance.o: instance.h instance.cpp
	$(CC) -c instance.cpp -o instance.o $(CXXFLAGS)

e3p.o: poly_function.o eig.o e3p.h e3p.cpp
	$(CC) -c e3p.cpp -o e3p.o $(CXXFLAGS)

eig.o: eig.cpp eig.h
	$(CC) -c eig.cpp -o eig.o $(CXXFLAGS)

poly_function.o: poly_function.cpp poly_function.h
	$(CC) -c poly_function.cpp -o poly_function.o $(CXXFLAGS)
