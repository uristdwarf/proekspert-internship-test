pulse:
	gcc -g pulse/pulse.c -o bin/pulse

coordinates:
	gcc -g coordinates/coordinates.c -o bin/coordinates -ljson-c
.PHONY: coordinates pulse
