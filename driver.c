#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>

#define MOTOROUT1 14
#define MOTOROUT2 15
#define MOTORPWM 18
#define POW 1024

int main(void) {
    int i = 0;

    if ( wiringPiSetupGpio() == -1) {
		printf("setup error");		       
	   	return 1;		
	}
		   
   	pinMode(MOTOROUT1, OUTPUT);	    
	pinMode(MOTOROUT2, OUTPUT);		    
	pinMode(MOTORPWM, PWM_OUTPUT);
							    
	digitalWrite(MOTOROUT1, 0);				    
	digitalWrite(MOTOROUT2, 0);					    
	digitalWrite(MOTORPWM, 0);
													    
	while(1) {						        
		printf("forward\n");		
		digitalWrite(MOTOROUT1, 1);							
		pwmWrite(MOTORPWM, POW);								
		sleep(5);
		
		pwmWrite(MOTORPWM, 0);		
		digitalWrite(MOTOROUT1, 0);							
		usleep(50000);
		
		printf("back\n");
		digitalWrite(MOTOROUT2, 1);
		pwmWrite(MOTORPWM, POW);								
		sleep(5);
																						
		pwmWrite(MOTORPWM, 0);		
		digitalWrite(MOTOROUT2, 0);
		printf("STOP\n");
		sleep(5);
	}
									
	return 0;
}
