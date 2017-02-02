#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <string.h>

int init(){
	printf("Init!\n");
}


int arm_open(){
	printf("Open!\n");
}


int arm_close() {
	printf("Close!\n");
}


int arm_fclose(){
	printf("Fclose!\n");
}
 

int raise(){
	printf("Raise!\n");
}


int lower(){
	printf("Lower!\n");
}


int lower_t(int time){
	printf("Lower_t!\n");
}


int stop() {
	printf("Stop!\n");
}
							
int quit(){
	printf("Quit!\n");
}

