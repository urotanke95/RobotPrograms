#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <unistd.h>

#define MOTOROUT1 14
#define MOTOROUT2 15

void up() {
		digitalWrite(MOTOROUT1, 1);
}

void down() {
		digitalWrite(MOTOROUT2, 1);
}

void stop() {
		digitalWrite(MOTOROUT1, 0);
    digitalWrite(MOTOROUT2, 0);
}

int main(void) {
		if ( wiringPiSetupGpio() == -1) {
			printf("setup error");
			return 1;		
		}

		pinMode(MOTOROUT1, OUTPUT);
		pinMode(MOTOROUT2, OUTPUT);

		digitalWrite(MOTOROUT1, 0);
    digitalWrite(MOTOROUT2, 0);

		char str[512] = {};	
    while(1) {
			memset(str, 0, sizeof(str));
			scanf("%s", str);
			if (strcmp("up", str) == 0) {
				up();
			} else if (strcmp("down", str) == 0) {
				down();
			} else {
				stop();
			}
		}
		return 0;

}
