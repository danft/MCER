CC=g++
CXXFLAGS=-llapack -g 
MCER_DEPS=subset_tree.o instance.o cover.o e2p.o e3p.o roots.o utils.o eig.o poly_function.o solver_wrapper.o solution.o cls_mcer.o mcer_base.o context.o

mcer: mcer.cpp $(MCER_DEPS)
	$(CC) mcer.cpp $(MCER_DEPS) -o mcer $(CXXFLAGS)

context.o: context.h context.cpp
	$(CC) -c context.cpp -o context.o $(CXXFLAGS)

cls_mcer.o: cls_mcer.h cls_mcer.cpp
	$(CC) -c cls_mcer.cpp -o cls_mcer.o $(CXXFLAGS)

mcer_base.o: mcer_base.h mcer_base.cpp
	$(CC) -c mcer_base.cpp -o mcer_base.o $(CXXFLAGS)

subset_tree.o: subset_tree.h subset_tree.cpp
	$(CC) -c subset_tree.cpp -o subset_tree.o $(CXXFLAGS)

instance.o: instance.h instance.cpp
	$(CC) -c instance.cpp -o instance.o $(CXXFLAGS)

solver_wrapper.o: solver_wrapper.h solver_wrapper.cpp
	$(CC) -c solver_wrapper.cpp -o solver_wrapper.o $(CXXFLAGS)

solution.o: solution.h solution.cpp
	$(CC) -c solution.cpp -o solution.o $(CXXFLAGS)

cover.o: cover.h cover.cpp
	$(CC) -c cover.cpp -o cover.o $(CXXFLAGS)

e2p.o: e2p.h e2p.cpp
	$(CC) -c e2p.cpp -o e2p.o $(CXXFLAGS)

e3p_test: e3p_test.cpp e3p.o
	$(CC) e3p_test.cpp e3p.o eig.o roots.o poly_function.o utils.o -o e3p_test $(CXXFLAGS)

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
