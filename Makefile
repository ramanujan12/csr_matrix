#___________________________________________________________________________________________
#
# project name
#
# author  : archer
# date    :
# to-do   :
# caution :
#
# program : 
#
#___________________________________________________________________________________________
# targets
TARGET = test_csr

all: $(TARGET)

#___________________________________________________________________________________________
# compiler and flags
CXX      := g++
CXXFLAGS := -std=c++17 -O3 # -Wall -fopenmp #-fsanitize=address
LIBS     := # -pthread

#___________________________________________________________________________________________
# directory with the source files
SRC := ./src
OBJ := ./obj
RUN := ./run
TST := ./test

#___________________________________________________________________________________________
# includes
INC := -I $(SRC)

#___________________________________________________________________________________________
# clean 
clean:
	rm -f *~ $(OBJ)/*.o $(SRC)/*~ $(RUN)/*~ $(TST)/*~ $(TARGET)

#___________________________________________________________________________________________
#
# compile commands
#___________________________________________________________________________________________
#___________________________________________________________________________________________
# run files

#___________________________________________________________________________________________
# test files
test_csr: $(TST)/test_csr.cpp $(OBJ)/csr_matrix.o $(OBJ)/dijkstra.o $(OBJ)/bellman_ford.o
	$(CXX) -o $@ $(TST)/test_csr.cpp $(LIBS) $(INC) $(CXXFLAGS)

#___________________________________________________________________________________________
# c++ object files
$(OBJ)/timing.o: $(SRC)/timing.h
	$(CXX) -o $@ -c $(SRC)/timing.h $(CXXFLAGS) $(INC) $(LIBS)

$(OBJ)/csr_matrix.o: $(SRC)/csr_matrix.h
	$(CXX) -o $@ -c $(SRC)/csr_matrix.h $(CXXFLAGS) $(INC) $(LIBS)

$(OBJ)/d_ary_heap.o: $(SRC)/d_ary_heap.h
	$(CXX) -o $@ -c $(SRC)/d_ary_heap.h $(CXXFLAGS) $(INC) $(LIBS)

$(OBJ)/dijkstra.o: $(SRC)/dijkstra.h $(OBJ)/d_ary_heap.o $(OBJ)/csr_matrix.o
	$(CXX) -o $@ -c $(SRC)/dijkstra.h $(CXXFLAGS) $(INC) $(LIBS)

$(OBJ)/bellman_ford.o: $(SRC)/bellman_ford.h
	$(CXX) -o $@ -c $(SRC)/bellman_ford.h $(CXXFLAGS) $(INC) $(LIBS)

#___________________________________________________________________________________________
# non file targets
.PHONY : all clean
