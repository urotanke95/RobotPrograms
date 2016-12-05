#include "move_api.h"
#include "stdio.h"

int main()
{
	char c = 0;
	g_init();
  while(1){
		c = getchar();
		if(c=='q'){
    	break;
		}else if(c == 's'){
			g_stop();
		}else if(c == 'f'){
			g_go_straight(1,500);
		}
  }
	g_quit();
}
