#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define DEBUG 0
#define SPI_CHANNEL 0
#define SS_PORT 8

int main(int argc, char **argv){
    int retCode;
    int i;
    int a2dChannel = atoi(argv[1]);  // analog channel
    int a2dVal = 0;
    float a2dVol = 0;
    float Vref = 5;
		
		printf("Channel:%d\n", a2dChannel);
    unsigned char data[3];

// SPI channel 0 ?? 1MHz ?ŊJ?n?B
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

    while(1) {
        data[0] = 0b00000110 |( ((a2dChannel & 0x04) >> 2));  //  first byte transmitted -> start bit -> (SGL/DIF = 1,D2=0)
        data[1] = 0b00000000 |( ((a2dChannel & 0x03) << 6)); // second byte transmitted -> (D1=D0=0)
        data[2] = 0; // third byte transmitted....don't care

		digitalWrite(SS_PORT, 0);
        retCode=wiringPiSPIDataRW (SPI_CHANNEL,data,sizeof(data));
		digitalWrite(SS_PORT, 1);

        a2dVal = (data[1]<< 8) & 0b111100000000; //first 4 bit
        a2dVal |=  (data[2] & 0xff);
        a2dVol = (float)a2dVal/4095 * Vref;

        printf("a2dVal=%d\n",a2dVal);
        printf("a2dVol=%f[V]\n",a2dVol);
        sleep(1);
    }
}
