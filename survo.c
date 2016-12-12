#include <stdio.h>
#include <wiringPi.h>
int main()
{
pinMode(18,PWM_OUTPUT);
pwmSetMode(PWM_MODE_MS);
pwmSetClock(400);
pwmSetRange(1024);

while(1){
    int num;
    scanf("%i",&num);
	    printf("%d\n",num);
		
		    if(num == -1){
			      break;
			  }
    pwmWrite(18,num);
	  }
    return 0;
}
