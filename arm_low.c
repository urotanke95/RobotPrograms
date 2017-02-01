#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define SPI_CHANNEL 0
#define SS_PORT 8
#define MOTOR_OUT1 14
#define MOTOR_OUT2 15

#define SLEEP 100000
#define PR_LOW_CH 1

#define THRESHOLD_PR 1500
#define TERM_PR 10

int main(int argc, char **argv){
    int a2dVal = 0, count = 0;
    unsigned char data[3];
	struct timeval start, end;

    if (wiringPiSPISetup(SPI_CHANNEL, 1000000) < 0) {
     	printf("SPISetup failed:\n");
		return 0;
    }
	
	if (wiringPiSetupGpio() == -1) {
		printf("GPIO set up error\n");
		return 0;
	}	

	pinMode(SS_PORT, OUTPUT);
	pinMode(MOTOR_OUT1, OUTPUT);
	pinMode(MOTOR_OUT2, OUTPUT);
	digitalWrite(SS_PORT, 1);
	digitalWrite(MOTOR_OUT1, 0);
	digitalWrite(MOTOR_OUT2, 0);

	digitalWrite(MOTOR_OUT1, 1);
    gettimeofday(&start, NULL);
	while(1) {
        data[0] = 0b00000110;  
        data[1] = 0b00000000 |(((PR_LOW_CH & 0x03) << 6));
        data[2] = 0;

		digitalWrite(SS_PORT, 0);
        retCode=wiringPiSPIDataRW (SPI_CHANNEL,data,sizeof(data));
		digitalWrite(SS_PORT, 1);

        a2dVal = (data[1]<< 8) & 0b111100000000; //first 4 bit
        a2dVal |=  (data[2] & 0xff);
        a2dVol = (float)a2dVal/4095 * Vref;
		
		if (a2dVal > THRESHOLD_PR) {
			count++;
			if (count > TERM_PR) {
				break;
			}
		} else {
			if (count > 0) {
				count--;
			}
		}
        usleep(SLEEP);
	}
	gettimeofday(&end, NULL);
	digitalWrite(MOTOR_OUT1, 0);
	digitalWrite(MOTOR_OUT2, 0);
	int sec = end.tv_sec - start.tv_sec;
	int time = sec * 1000000 + end.tv_usec;
	time -= start.tv_usec;
	printf("%d usec\n", time);
	return time;
}
