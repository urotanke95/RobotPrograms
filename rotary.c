#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int a;
int b;
int p_a;
int p_b;
int num;

void click_a(void) {
	int _a;
	_a = digitalRead(0);
	if (_a != a) {
		if (a == 1) {
			p_a = 1;
		} else {
		p_a = 0;
		}
		a = _a;
		if (a == 0 && b == 0 && p_a == 1 && p_b == 1) {
			printf("right %d\n", ++num);
		}
	}
}

void click_b(void) {
	int _b;
	_b = digitalRead(1);
	if (_b != b) {
		if (b == 1) {
			p_b = 1;
		} else {
		    p_b = 0;
	    }
	    b = _b;
	    if (a == 0 && b == 0 && p_a == 1 && p_b == 1) {
			printf("left  %d\n", --num);
		}
	}
}

int main(void){
	if (wiringPiSetupGPIO() == -1) {
		fprintf(stderr, "Setup Error\n");
		return 1;
	}
	a = 1;
	b = 1;
	p_a = 0;
	p_b = 0;
	num = 0;
    pullUpDnControl(0, PUD_UP);
	pullUpDnControl(1, PUD_UP);
	wiringPiISR(0, INT_EDGE_BOTH, click_a);
	wiringPiISR(1, INT_EDGE_BOTH, click_b);
	while(1){
		sleep(1);
	}
}
