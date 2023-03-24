ode:
	g++ -g ode.cpp -std=c++17 -o bin/ode 
image:
	gcc -g image.c -o bin/image -lm

pulse:
	gcc -g pulse/pulse.c -o bin/pulse

coordinates:
	gcc -g coordinates/coordinates.c -o bin/coordinates -ljson-c

.PHONY: coordinates pulse image
