#include <wiringPi.h>
#include <stdio.h>

int main()
{
  int input;

  if (wiringPiSetupGpio() == -1)
    return 1;
	
  while (1) {

    printf("Please input 1 to shoot the ball\n");
    scanf("%d", &input);

    if (input == 1) {
      pinMode( 04, OUTPUT );

      digitalWrite(04, 1);
      break;
    }else
      continue;
  }

  while (1) {
    printf("Please input 0 to stop the motors\n");
    scanf("%d", &input);
    if (input == 0) {
      digitalWrite(04, 0);
      break;
    }else
      continue;
  }

  return 0;
}
