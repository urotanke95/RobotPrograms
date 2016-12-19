#include <stdio.h>
#include <wiringPi.h>
#define REV_PWM 107
#define STOP_PWM 77
#define POS_PWM 50

int main()
{
	pinMode(18,PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(375);
	pwmSetRange(1024);

	while(1){
	    int num;
	    scanf("%i",&num);
		printf("%d\n",num);
				
		if (num == -1) {
    		pwmWrite(18, REV_PWM);
		} else if (num == 0) {
    		pwmWrite(18, STOP_PWM);
		} else if (num == 1) {
    		pwmWrite(18, POS_PWM);
		} else {
			printf("end!\n");
			break;
		}
	}
    return 0;
}
