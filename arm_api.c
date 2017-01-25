#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <string.h>

#define SURVO_OUT 12
#define MOTOR_OUT1 14
#define MOTOR_OUT2 15
#define SS_PORT 8

#define SLEEP 100000

#define THRESHOLD_PR 2000
#define RANGE_PR 50
#define TERM_PR 10

#define CLOSE_TRS 980
#define OPEN_TRS 1200
#define RANGE_PS 50
#define TERM_PS 10

int open(){ //Arm open completely. When error, return -1
    int a2dVal = 0;
    unsigned char data[3];
	if (wiringPiSPISetup(0, 1000000) < 0) {
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
	digitalWrite(SS_PORT, 1);
	
	pwmWrite(SURVO_OUT, 125);
	int count = 0;
	while(1) {
        data[0] = 0b00000110;
        data[1] = 0b00000000;
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

int close(){ //Arm catch or close. When error, return -1
    int a2dVal = 0, buff = 0;
    unsigned char data[3];
	if (wiringPiSPISetup(0, 1000000) < 0) {
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
	digitalWrite(SS_PORT, 1);
	
	pwmWrite(SURVO_OUT, 25);
    int count = 0, over = 0;
	while(1) {
        data[0] = 0b00000110;
        data[1] = 0b00000000;
		data[2] = 0;
		digitalWrite(SS_PORT, 0);
		wiringPiSPIDataRW (SPI_CHANNEL,data,sizeof(data));
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

int raise(){ //Lift rises. When error, return -1
    int a2dVal = 0;
    unsigned char data[3];
	if (wiringPiSPISetup(0, 1000000) < 0) {
     	printf("SPISetup failed\n");
		return -1;
    }
	if (wiringPiSetupGpio() == -1) {
		fprintf(stderr, "WiringPi Initialize Error\n");
		return -1;
	}
	pinMode(MOTOROUT1, OUTPUT);
	pinMode(MOTOROUT2, OUTPUT);
	pinMode(SS_PORT, OUTPUT);
	digitalWrite(SS_PORT, 1);
	digitalWrite(MOTOR_OUT1, 0);
	digitalWrite(MOTOR_OUT2, 0);
    int count = 0;
	digitalWrite(MOTOR_OUT2, 1);
	while(1) {
        data[0] = 0b00000110;
        data[1] = 0b00000000;
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
	digitalWrite(MOTOR_OUT2, 0);
	return 0;
}

int lower(){ //Lift get down. When error, return -1
    int a2dVal = 0;
    unsigned char data[3];
	if (wiringPiSPISetup(0, 1000000) < 0) {
     	printf("SPISetup failed\n");
		return -1;
    }
	if (wiringPiSetupGpio() == -1) {
		fprintf(stderr, "WiringPi Initialize Error\n");
		return -1;
	}
	pinMode(MOTOROUT1, OUTPUT);
	pinMode(MOTOROUT2, OUTPUT);
	pinMode(SS_PORT, OUTPUT);
	digitalWrite(SS_PORT, 1);
	digitalWrite(MOTOR_OUT1, 0);
	digitalWrite(MOTOR_OUT2, 0);
	
	int count = 0;
	digitalWrite(MOTOR_OUT1, 1);
    while(1) {
        data[0] = 0b00000110;
        data[1] = 0b00000000;
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
	return 0;
}

