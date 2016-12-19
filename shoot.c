#include <wiringPi.h>
#include <stdio.h>

int main()
{
	int input;

	if (wiringPiSetupGpio() == -1)
		return 1;
	printf("Please input 1 to shoot the ball\n");
	scanf("%d", &input);

	if (input == 1) {
		pinMode( 04, OUTPUT );
		pinMode( 17, OUTPUT );
		pinMode(27, OUTPUT);
		pinMode(22, OUTPUT);

		digitalWrite(04, 1);
		digitalWrite( 17, 1 );
		digitalWrite(27, 1);
		digitalWrite(22, 1);
	}

	printf("Please input 0 to stop the motors\n");
	scanf("%d", &input);
	if (input == 0) {
	  digitalWrite(04, 0);
	  digitalWrite(17, 0);
	  digitalWrite(27, 0);
	  digitalWrite(22, 0);
	}

	return 0;
}