CXXFLAGS=-llapack -g 
obj=subset_tree.o instance.o cover.o utils.o  solver_wrapper.o solution.o cls_mcer.o mcer_base.o context.o mcerk.o mcer.o
src=$(obj:.o=.cpp)

e3p_obj=e3p.o roots.o eig.o poly_function.o
e3p_obj_=$(foreach sname, $(e3p_obj), $(e3p_DIR)/$(sname))
e3p_DIR=e3p

e2p_obj=e2p.o
e2p_obj_=$(foreach sname, $(e2p_obj), $(e2p_DIR)/$(sname))
e2p_DIR=e2p


all_obj=$(obj) $(e2p_obj_) $(e3p_obj_)

$(info ${all_obj})

%.o : %.cpp %.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

mcer: main_mcer.cpp $(all_obj)
	$(CXX) main_mcer.cpp $(all_obj) -o mcer $(CXXFLAGS)
	
mcerk: main_mcerk.cpp $(all_obj)
	$(CXX) main_mcerk.cpp $(all_obj) -o mcerk $(CXXFLAGS)

all: mcer mcerk

e3p_test: e3p/e3p_test.cpp e3p/$(e3p_obj)
	$(CC) e3p/e3p_test.cpp e3p/$(e3p_obj) -o e3p/e3p_test $(CXXFLAGS)

.PHONY: clean
clean:
	rm *.o mcer $(e3p_DIR)/*.o $(e2p_DIR)/*.o 
