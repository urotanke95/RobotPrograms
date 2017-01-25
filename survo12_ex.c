#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
#include <unistd.h>

int main(){

	if (wiringPiSetupGpio() == -1) {
		fprintf(stderr, "WiringPi Initialize Error\n");
		return 0;
	}

	pinMode(12,PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(375);
	pwmSetRange(1024);

	while(1){
		int num;
		//int duty = 75;
		char com[8];
		scanf("%s",com);
		//printf("%s\n",num);
		if (strcmp(com, "open") == 0) {
			printf("open arm");
			pwmWrite(12, 125); //アームが開く
		} else if(strcmp(com, "close") == 0) {
			printf("close arm");
			pwmWrite(12, 25); //アームが閉じる
		} else if(stdcmp(com, "pause") == 0) {
			printf("pause movement");
			pwmWrite(12, 75); //一時停止
		} else if(stdcmp(com, "end") == 0) {
			printf("end of program");
			return 0; //終了
		} else if(stdcmp(com, "auto") == 0) {
			printf("auto");
			pwmWrite(12,125);
			sleep(3);
			pwmWrite(12,75);
			sleep(1);
			pwmWrite(12, 25);
			sleep(3);
			printf("auto finish");
			return 0;
		}
	}
	return 0;
}
