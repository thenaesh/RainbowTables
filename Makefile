CXXFLAGS=-std=c++11

all: run



run: compile
	./invert < SAMPLE_INPUT.data

compile:
	g++ invert.cpp rainbow.cpp sha1/sha1.cpp $(CXXFLAGS) -o invert
	tar -xzf RAINBOW
	tar -xJf COLLISIONS


rungenerator: compilegenerator
	./generate < SAMPLE_INPUT.data
	tar -cJf COLLISIONS COLLISION1 COLLISION2
	tar -czf RAINBOW RAINBOW1 RAINBOW2 COLLISIONS

compilegenerator:
	g++ invert.cpp rainbow.cpp sha1/sha1.cpp $(CXXFLAGS) -DGENERATE -o generate



clean:
	rm invert
	rm generate
	rm COLLISIONS
	rm COLLISION1
	rm COLLISION2
	rm RAINBOW1
	rm RAINBOW2

