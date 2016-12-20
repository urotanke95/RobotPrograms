#include <stdio.h>
#include <wiringPi.h>
#define REV_PWM 125
#define STOP_PWM 75
#define POS_PWM 35

int main()
{
	pinMode(18,PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(375);
	pwmSetRange(1024);

	while(1){
	    int num;
	    scanf("%i",&num);
				
		if (num == -1) {
    		pwmWrite(18, 125);
				printf("Reverse %d\n", REV_PWM);
		} else if (num == 0) {
    		pwmWrite(18, 75);
				printf("Stop\n");
		} else if (num == 1) {
				printf("Positive\n");
    		pwmWrite(18, 30);
		} else {
			printf("end!\n");
			break;
		}
	}
    return 0;
}
