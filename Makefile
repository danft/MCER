CC=g++
CXXFLAGS=-llapack -O2 

mcer: mcer.cpp e3p.o e2p.o roots.o instance.o eig.o poly_function.o subset_tree.o utils.o
	$(CC) mcer.cpp subset_tree.o instance.o e2p.o roots.o e3p.o eig.o poly_function.o utils.o -o mcer $(CXXFLAGS)

subset_tree.o: subset_tree.h subset_tree.cpp
	$(CC) -c subset_tree.cpp -o subset_tree.o $(CXXFLAGS)

instance.o: instance.h instance.cpp
	$(CC) -c instance.cpp -o instance.o $(CXXFLAGS)

e2p.o: e2p.h e2p.cpp
	$(CC) -c e2p.cpp -o e2p.o $(CXXFLAGS)

e3p.o: roots.o utils.o poly_function.o eig.o e3p.h e3p.cpp
	$(CC) -c e3p.cpp -o e3p.o $(CXXFLAGS)

roots.o: eig.o roots.h roots.cpp
	$(CC) -c roots.cpp -o roots.o $(CXXFLAGS)

eig.o: eig.cpp eig.h
	$(CC) -c eig.cpp -o eig.o $(CXXFLAGS)

poly_function.o: poly_function.cpp poly_function.h
	$(CC) -c poly_function.cpp -o poly_function.o $(CXXFLAGS)

utils.o: utils.h utils.cpp
	$(CC) -c utils.cpp -o utils.o $(CXXFLAGS)

clean:
	rm *.o mcer

.PHONY: clean
