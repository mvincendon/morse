CXX=g++
CXXFLAGS=-Wall -O3 -std=c++11

morse: morse.cpp wav.cpp morse.h wav.h Correspondance/corres.cpp Correspondance/arbre.cpp Correspondance/noeud.cpp Correspondance/corres.h Correspondance/arbre.h Correspondance/noeud.h
	$(CXX) $(CXXFLAGS) $^ -o $@ 

clean:
	rm morse
