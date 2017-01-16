#include <stdio.h>
#include <wiringPi.h>

int main(){

	if (wiringPiSetupGpio() == -1) {
		fprintf(stderr, "WiringPi Initialize Error\n");
		return 0;
	}

	pinMode(18,PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(375);
	pwmSetRange(1024);

	while(1){
  	int num;
    int duty = 75;
		scanf("%i",&num);
	  printf("%d\n",num);
		pwmWrite(18,num);
	}
  return 0;
}
