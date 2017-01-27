#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
#include <unistd.h>

void setup_survo() {
	if (wiringPiSetupGpio() == -1) {
		fprintf(stderr, "WiringPi Initialize Error\n");
		return 0;
	}

	pinMode(12,PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(375);
 	pwmSetRange(1024);
	printf("open, close, end, stop, or auto\n");
}

void openArm() {
	printf("open arm\n");
	pwmWrite(12, 125); //アームが開く
	sleep(5);
	pwmWrite(12,75);
}

void closeArm() {
	printf("close arm\n");
	pwmWrite(12, 25); //アームが閉じる
	sleep(5);
	pwmWrite(12, 75);
}

void stop() {
	printf("stop movement\n");
	pwmWrite(12, 75); //一時停止
}

void end() {
	printf("end of program\n");
}

void auto() {
	printf("auto\n");
	pwmWrite(12,125);
	sleep(3);
	pwmWrite(12,75);
	sleep(1);
	pwmWrite(12, 25);
	sleep(3);
	pwmWrite(12,75);
	printf("auto finish\n");
}


