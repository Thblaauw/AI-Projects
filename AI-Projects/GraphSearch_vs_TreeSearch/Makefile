CXX = g++
CXXFLAGS = -Wall -g

source: Source.o GraphSearch.o TreeSearch.o Node.o
	$(CXX) $(CXXFLAGS) -o source Source.o GraphSearch.o TreeSearch.o Node.o

Source.o: Source.cpp GraphSearch.h TreeSearch.h Node.h
	$(CXX) $(CXXFLAGS) -c Source.cpp

GraphSearch.o: GraphSearch.cpp
	$(CXX) $(CXXFLAGS) -c GraphSearch.cpp	

TreeSearch.o: TreeSearch.cpp
	$(CXX) $(CXXFLAGS) -c TreeSearch.cpp

Node.o: Node.cpp
	$(CXX) $(CXXFLAGS) -c Node.cpp
