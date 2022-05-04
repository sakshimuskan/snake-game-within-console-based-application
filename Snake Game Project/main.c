#include <time.h>
#include <stdio.h>
#include<unistd.h>
#include "snake_s.h"
#include<windows.h>




int main()
{
	system("color 40");
	
	clock_t before;
	int msec = 0, trigger = 20000, i = 0, timer; /* 20ms */
	before = clock();
	start_up();
	snake_init();
	do
	{
		clock_t difference = clock() - before;
		msec = difference * 1000 / CLOCKS_PER_SEC;
		timer = msec / 1000;
		printf("timer = %ld\n", timer);
		
			
		print_s();
		screen_reset_position();
		random_f();
		movement();
		tail_remove();
		Sleep(speed);
		i++;
	} while (msec < trigger);
	game_o();
}

