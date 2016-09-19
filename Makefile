CXXFLAGS=-std=c++11

all: runtests

runtests: compiletests
	./rainbowtest

compiletests:
	g++ tests.cpp rainbow.cpp sha1/sha1.cpp $(CXXFLAGS) -o rainbowtest

clean:
	rm rainbowtest

cleantable:
	rm RAINBOW

