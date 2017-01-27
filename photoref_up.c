#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define SPI_CHANNEL 0
#define SS_PORT 8
#define THRESHOLD 1500
#define TERM 3
#define SLEEP 100000

int main(int argc, char **argv){
    int retCode;
    int a2dChannel = 1;  // analog channel
    int a2dVal = 0;

    unsigned char data[3];

    if (wiringPiSPISetup(SPI_CHANNEL, 1000000) < 0)
    {
     	printf("SPISetup failed:\n");
		return 0;
    }
	
	if (wiringPiSetupGpio() == -1) {
		printf("GPIO set up error\n");
		return 0;
	}	

	pinMode(SS_PORT, OUTPUT);
	digitalWrite(SS_PORT, 1);

	int count = 0;
    while(1) {
        data[0] = 0b00000110;  //  first byte transmitted -> start bit -> (SGL/DIF = 1,D2=0)
        data[1] = 0b01000000; // second byte transmitted -> (D1=D0=0)
        data[2] = 0; // third byte transmitted....don't care

		digitalWrite(SS_PORT, 0);
        retCode=wiringPiSPIDataRW (SPI_CHANNEL,data,sizeof(data));
		digitalWrite(SS_PORT, 1);

        a2dVal = (data[1]<< 8) & 0b111100000000; //first 4 bit
        a2dVal |=  (data[2] & 0xff);

        printf("a2dVal=%d\n",a2dVal);
		if (a2dVal > THRESHOLD) {
			count++;
			if (count > TERM) {
				printf("Reach the top.\n");
				break;
			}
		} else {
			count = 0;
		}
        usleep(SLEEP);
    }
}
