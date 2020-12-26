CXX=g++
CXXFLAGS=-Wall -O3 -std=c++11

morse: morse.cpp dict.cpp arbre.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ 

clean:
	rm morse
