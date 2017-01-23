#include <stdio.h>
#include <wiringPi.h>
#include <string.h>

int main(){

	if (wiringPiSetupGpio() == -1) {
		fprintf(stderr, "WiringPi Initialize Error\n");
		return 0;
	}

	pinMode(12,PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(375);
	pwmSetRange(1024);

	while(1){
  	int num;
    //int duty = 75;
		char com[8];
		scanf("%s",com);
	  //printf("%s\n",num);
		if (strcmp(com, "open") == 0) {
			pwmWrite(12, 125);
		} else if(strcmp(com, "close") == 0) {
			pwmWrite(12, 25);
		} else {
			pwmWrite(12, 75);
		}
	}
  return 0;
}
