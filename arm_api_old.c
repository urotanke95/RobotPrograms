#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <string.h>
#include <unistd.h>

#define SURVO_OUT 12
#define MOTOR_OUT1 14
#define MOTOR_OUT2 15
#define SS_PORT 8
#define PR_U_CHANNEL 0
#define PR_D_CHANNEL 1
#define PS_CHANNEL 2

#define SLEEP 10000

#define THRESHOLD_PR 1500
#define RANGE_PR 50
#define TERM_PR 10

#define CLOSE_TRS 980
#define OPEN_TRS 1200
#define RANGE_PS 50
#define TERM_PS 10

int fd_spi; //SPI descripter

int arm_open(){ //Arm open completely. When error, return -1
    int a2dVal = 0;
    unsigned char data[3];
	
	digitalWrite(SS_PORT, 1);
	
	pwmWrite(SURVO_OUT, 125);
	int count = 0;
	while(1) {
        data[0] = 0b00000110;
        data[1] = 0b00000000 | ((PS_CHANNEL & 0x03) << 6);
		data[2] = 0;
		digitalWrite(SS_PORT, 0);
		wiringPiSPIDataRW (SPI_CHANNEL,data,sizeof(data));
		digitalWrite(SS_PORT, 1);
        a2dVal = (data[1]<< 8) & 0b111100000000;
        a2dVal |=  (data[2] & 0xff);
		if (a2dVal > OPEN_TRS) {
			count++;
			if (count > TERM_PS) {
				break;
			}
		} else {
			if (count > 0) {
				count--;
			}
		}	
		usleep(SLEEP);
	}
	pwmWrite(SURVO_OUT, 75);
	return 0;
}

int arm_close(){ //Arm catch or close. When error, return -1
    int a2dVal = 0, buff = 0;
    unsigned char data[3];
	
	digitalWrite(SS_PORT, 1);
	
	pwmWrite(SURVO_OUT, 25);
    int count = 0, over = 0;
	while(1) {
        data[0] = 0b00000110;
        data[1] = 0b00000000 | ((PS_CHANNEL & 0x03) << 6);
		data[2] = 0;
		digitalWrite(SS_PORT, 0);
		wiringPiSPIDataRW (SPI_CHANNEL, data,sizeof(data));
		digitalWrite(SS_PORT, 1);
        a2dVal = (data[1]<< 8) & 0b111100000000;
        a2dVal |=  (data[2] & 0xff);
		if (a2dVal > CLOSE_TRS) { //Close limit over
			over++;
			if (over > TERM_PS) {
				break;
			}
		} else {
			if (over > 0) {
				over--;
			}
		}
		if ((buff - RANGE_PS) < a2dVal && a2dVal < (buff + RANGE_PS)) {//Stop by catching
			count++;
			if (count > TERM_PS) {
				break;
			}
		} else {
			count = 0;
		}
		buff = a2dVal;
		usleep(SLEEP);
	}
	pwmWrite(SURVO_OUT, 75);
	return 0;
}

int arm_fclose(){ //Arm catch or close. When error, return -1
    int a2dVal = 0;
    unsigned char data[3];
	
	digitalWrite(SS_PORT, 1);
	
	pwmWrite(SURVO_OUT, 25);
    int over = 0;
	while(1) {
        data[0] = 0b00000110;
        data[1] = 0b00000000 | ((PS_CHANNEL & 0x03) << 6);
		data[2] = 0;
		digitalWrite(SS_PORT, 0);
		wiringPiSPIDataRW (SPI_CHANNEL, data,sizeof(data));
		digitalWrite(SS_PORT, 1);
        a2dVal = (data[1]<< 8) & 0b111100000000;
        a2dVal |=  (data[2] & 0xff);
		if (a2dVal > CLOSE_TRS) { //Close limit over
			over++;
			if (over > TERM_PS) {
				break;
			}
		} else {
			if (over > 0) {
				over--;
			}
		}
		usleep(SLEEP);
	}
	pwmWrite(SURVO_OUT, 75);
	return 0;
}

int raise(){ //Lift rises. When error, return -1
    int a2dVal = 0;
    unsigned char data[3];
	
	digitalWrite(SS_PORT, 1);
	digitalWrite(MOTOR_OUT1, 0);
	digitalWrite(MOTOR_OUT2, 0);
    
	int count = 0;
	digitalWrite(MOTOR_OUT2, 1);
	while(1) {
        data[0] = 0b00000110;
        data[1] = 0b00000000 | ((PR_U_CHANNEL & 0x03) << 6);
		data[2] = 0;
		digitalWrite(SS_PORT, 0);
		wiringPiSPIDataRW (SPI_CHANNEL,data,sizeof(data));
		digitalWrite(SS_PORT, 1);
        a2dVal = (data[1]<< 8) & 0b111100000000;
        a2dVal |=  (data[2] & 0xff);
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
	digitalWrite(MOTOR_OUT1, 0);
	digitalWrite(MOTOR_OUT2, 0);
	return 0;
}

int lower(){ //Lift get down. When error, return -1
  	int a2dVal = 0;
  	unsigned char data[3];
	struct timeval start, end;

	digitalWrite(SS_PORT, 1);
	digitalWrite(MOTOR_OUT1, 0);
	digitalWrite(MOTOR_OUT2, 0);
	
	int count = 0;
	digitalWrite(MOTOR_OUT1, 1);
	gettimeofday(&start, NULL);
    while(1) {
        data[0] = 0b00000110;
        data[1] = 0b00000000 | ((PR_D_CHANNEL & 0x03) << 6);
		data[2] = 0;
		digitalWrite(SS_PORT, 0);
		wiringPiSPIDataRW (SPI_CHANNEL,data,sizeof(data));
		digitalWrite(SS_PORT, 1);
        a2dVal = (data[1]<< 8) & 0b111100000000;
        a2dVal |=  (data[2] & 0xff);
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
	if (count > TERM_PR) {
		return 0;
	}
	int sec = end.tv_sec - start.tv_sec;
	int time = sec * 1000000 + end.tv_usec;
	time -= start.tv_usec;
	return time;
}

int lower_t(int clock){ //Lift get down. When error, return -1
  	int a2dVal = 0;
  	unsigned char data[3];
	struct timeval start, end;

	digitalWrite(SS_PORT, 1);
	digitalWrite(MOTOR_OUT1, 0);
	digitalWrite(MOTOR_OUT2, 0);
	
	int count = 0;
	digitalWrite(MOTOR_OUT1, 1);
	gettimeofday(&start, NULL);
    while(1) {
		gettimeofday(&end, NULL);
		int sec = end.tv_sec - start.tv_sec;
		int time = sec * 1000000 + end.tv_usec;
	   	time -= start.tv_usec;
		if (time > clock) {
			break;
		} 
        data[0] = 0b00000110;
        data[1] = 0b00000000 | ((PR_D_CHANNEL & 0x03) << 6);
		data[2] = 0;
		digitalWrite(SS_PORT, 0);
		wiringPiSPIDataRW (SPI_CHANNEL,data,sizeof(data));
		digitalWrite(SS_PORT, 1);
        a2dVal = (data[1]<< 8) & 0b111100000000;
        a2dVal |=  (data[2] & 0xff);
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
	digitalWrite(MOTOR_OUT1, 0);
	digitalWrite(MOTOR_OUT2, 0);
	return 0;
}

void stop(){ //Lift get down. When error, return -1
	pwmWrite(SURVO_OUT, 75);
	pinMode(MOTOR_OUT1, OUTPUT);
	pinMode(MOTOR_OUT2, OUTPUT);
	digitalWrite(MOTOR_OUT1, 0);
	digitalWrite(MOTOR_OUT2, 0);
}

int init() {
	if ((fd_spi = wiringPiSPISetup(SPI_CHANNEL, 1000000)) < 0) {
		printf("SPISetup failed\n");
		return -1;
	}
	if (wiringPiSetupGpio() == -1) {
		fprintf(stderr, "WiringPi Initialize Error\n");
		return -1;
	}
	
	pinMode(SURVO_OUT,PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(375);
	pwmSetRange(1024);
	
	pinMode(SS_PORT, OUTPUT);
	pinMode(MOTOR_OUT1, OUTPUT);
	pinMode(MOTOR_OUT2, OUTPUT);
	
	
	return 0;
}

void quit() {
	close(fd_spi);
}
	
int main(){
	char str[512];
	if (init < 0) {
		return -1;
	}
	while(1) {
		memset(str, 0, sizeof(str));
		scanf("%s",str);
		if (strcmp("o", str) == 0) {
			arm_open();	
		} else if (strcmp("c", str) == 0) {
			arm_close();
		} else if (strcmp("fc", str) == 0) {
			arm_fclose();
		} else if (strcmp("r", str) == 0) {
			raise();
		} else if (strcmp("l", str) == 0) {
			lower();
		} else {
			stop();
		}
	}
}
