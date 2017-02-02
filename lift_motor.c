#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <unistd.h>

#define MOTOROUT1 14
#define MOTOROUT2 15

void setup_lift() {
	if ( wiringPiSetupGpio() == -1) {
		printf("setup error");
		return;		
	}

	pinMode(MOTOROUT1, OUTPUT);
	pinMode(MOTOROUT2, OUTPUT);
	digitalWrite(MOTOROUT1, 0);
    digitalWrite(MOTOROUT2, 0);
}

void up() {
	digitalWrite(MOTOROUT1, 1);
	sleep(3);
	digitalWrite(MOTOROUT1, 0);
}

void down() {
	digitalWrite(MOTOROUT2, 1);
	sleep(3);
	digitalWrite(MOTOROUT2, 0);
}

void stop() {
	digitalWrite(MOTOROUT1, 0);
    digitalWrite(MOTOROUT2, 0);
}
