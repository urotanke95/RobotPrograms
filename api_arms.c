#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define SPI_CHANNEL 0
#define SS_PORT 8
#define MOTOR1_OUT 14 
#define MOTOR2_OUT 15
#define SURVO_OUT 12

#define SLEEP 10000

#define THRESHOLD_PR 1500
#define RANGE_PR 50
#define TERM_PR 10

#define CLOSE_TRS 980
#define OPEN_TRS 1200
#define RANGE_PS 50
#define TERM_PS 10

#define PS_CHANEL 0
#define PR_U_CHANEL 1
#define PR_D_CHANEL 2

int init() {
	if (wiringPiSPISetup(SPI_CHANNEL, 1000000) < 0) {
     	printf("SPISetup failed:\n");
		return -1;
    }
	
	if (wiringPiSetupGpio() == -1) {
		printf("GPIO set up error\n");
		return -1;
	}
	pinMode(SS_PORT, OUTPUT);
	pinMode(MOTOR1_OUT, OUTPUT);
	pinMode(MOTOR2_OUT, OUTPUT);
	pinMode(SURVO_OUT, OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(375);
	pwmSetRange(1024);	
	return 0;
}

int arm_open(){ //Arm open completely. When error, return -1
    int a2dVal = 0;
    unsigned char data[3];
    
    digitalWrite(SS_PORT, 1);
    
    pwmWrite(SURVO_OUT, 125);
    int count = 0;
    while(1) {
        data[0] = 0b00000110;
        data[1] = 0b00000000 |(((PS_CHANEL & 0x03) << 6));
        data[2] = 0;
        digitalWrite(SS_PORT, 0);
        wiringPiSPIDataRW (0,data,sizeof(data));
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
    usleep(SLEEP);
    return 0;
}

int arm_fclose() {
    int a2dVal = 0;
    unsigned char data[3];
    
    digitalWrite(SS_PORT, 1);
    pwmWrite(SURVO_OUT, 25);
    int over = 0;
    while(1) {
        data[0] = 0b00000110;
        data[1] = 0b00000000 |(((PS_CHANEL & 0x03) << 6));
        data[2] = 0;
        digitalWrite(SS_PORT, 0);
        wiringPiSPIDataRW (0, data,sizeof(data));
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
    pwmWrite(SURVO_OUT, 25);
    usleep(SLEEP);
    return 0;
}

int arm_close() {
    int a2dVal = 0, buff = 0;
    unsigned char data[3];
    
    digitalWrite(SS_PORT, 1);
    pwmWrite(SURVO_OUT, 25);
    int count = 0, over = 0;
    while(1) {
        data[0] = 0b00000110;
        data[1] = 0b00000000 |(((PS_CHANEL & 0x03) << 6));
        data[2] = 0;
        digitalWrite(SS_PORT, 0);
        wiringPiSPIDataRW (0, data,sizeof(data));
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
    usleep(SLEEP);
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
        data[1] = 0b00000000 |(((PR_U_CHANEL & 0x03) << 6));
        data[2] = 0;
        digitalWrite(SS_PORT, 0);
        wiringPiSPIDataRW (0,data,sizeof(data));
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
    usleep(SLEEP);
    return 0;
}

int lower(){ //Lift get down. When error, return -1
    int a2dVal = 0;
    unsigned char data[3];
    
    digitalWrite(SS_PORT, 1);
    digitalWrite(MOTOR_OUT1, 0);
    digitalWrite(MOTOR_OUT2, 0);
    
    int count = 0;
    digitalWrite(MOTOR_OUT1, 1);
    while(1) {
        data[0] = 0b00000110;
        data[1] = 0b00000000 |(((PR_D_CHANEL & 0x03) << 6));
        data[2] = 0;
        digitalWrite(SS_PORT, 0);
        wiringPiSPIDataRW (0,data,sizeof(data));
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
    usleep(SLEEP);
    return 0;
}

int stop(){
    pwmWrite(SURVO_OUT, 75);
    digitalWrite(MOTOR_OUT1, 0);
    digitalWrite(MOTOR_OUT2, 0);
}

int quit(){
	if (raise() != 0) {
		return -1;
	}
	if (arm_open() != 0) {
		return -1;
	}
	if (stop() != 0) {
		return -1;
	}
	return 0;
}

int main(){
	char str[256] = {};
	if (init() != 0) {
		return -1;
	}
	while (1) {
		memset(str, 0, sizeof(str));
		if (strcmp(str, "o") == 0) { //Open
			open();
		} else if (strcmp(str, "fc") == 0) { //Full Close
			arm_fclose();
		} else if (strcmp(str, "c") == 0) { //Close
			arm_close();
		} else if (strcmp(str, "l") == 0) { //Lower
			lower();
		} else if (strcmp(str, "r") == 0) { //Raise
			raise();
		} else {
			stop();
		}
	}
}
