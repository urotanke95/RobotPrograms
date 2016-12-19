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
  	int num = 0;
    int duty = 75;
		scanf("%i",&num);
	  printf("%d\n",num);
		
		if(num < -90 || 90 < num){
			fprintf(stderr, "Angle over!\n");
			break;
		}
		num += 90;
		double ratio = num * (97 / 180.0) + 25;
		printf("%f\n", ratio);
		duty =(int)ratio;
		printf("duty:%d\n", duty);
    pwmWrite(18, duty);
	}
  return 0;
}
