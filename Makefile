main.out: main.cpp Enigma.h Plugboard.h Reflector.h Rotor.h
	g++ main.cpp -std=c++11 -O2 -o main.out