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
	printf("open, close, end, stop, or auto\n");

	while(1){
		int num;
		//int duty = 75;
		char com[8];
		scanf("%s",com);
		//printf("%s\n",num);
		if (strcmp(com, "open") == 0) {
 			printf("open arm\n");
			pwmWrite(12, 125); //アームが開く
		} else if(strcmp(com, "close") == 0) {
			printf("close arm\n");
			pwmWrite(12, 25); //アームが閉じる
		} else if(strcmp(com, "stop") == 0) {
			printf("stop movement\n");
			pwmWrite(12, 75); //一時停止
		} else if(strcmp(com, "end") == 0) {
			printf("end of program\n");
			return 0; //終了
		} else if(strcmp(com, "auto") == 0) {
			printf("auto\n");
			pwmWrite(12,125);
			sleep(3);
			pwmWrite(12,75);
			sleep(1);
			pwmWrite(12, 25);
			sleep(3);
			pwmWrite(12,75);
			printf("auto finish");
			return 0;
		}
	}
	return 0;
}
