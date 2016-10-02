CXXFLAGS=-std=c++11

all: runitest



runitest: compileitest
	./rainbowitest
	tar -cJf COLLISIONS COLLISION1 COLLISION2
	tar -czf RAINBOW RAINBOW1 RAINBOW2 COLLISIONS

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

