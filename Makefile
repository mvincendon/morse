CXX=g++
CXXFLAGS=-Wall -O3 -std=c++11

morse: morse.cpp arbre.cpp morse.h arbre.h
	$(CXX) $(CXXFLAGS) $^ -o $@ 

clean:
	rm morse
