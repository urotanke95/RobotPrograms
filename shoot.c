#include <wiringPi.h>
#include <stdio.h>

void start_moter()
{
  int input;

  if (wiringPiSetupGpio() == -1)
    return;

  pinMode( 04, OUTPUT );
  digitalWrite(04, 1);
}


void stop_moter()
{
	digitalWrite(04, 0);
}
