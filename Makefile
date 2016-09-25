CXXFLAGS=-std=c++11 -g

all: runitest



runitest: compileitest
	./rainbowitest

compileitest:
	g++ itest.cpp rainbow.cpp sha1/sha1.cpp $(CXXFLAGS) -o rainbowitest


runtests: compiletests
	./rainbowtest

compiletests:
	g++ tests.cpp rainbow.cpp sha1/sha1.cpp $(CXXFLAGS) -o rainbowtest



clean:
	rm rainbowtest

cleantable:
	rm RAINBOW

