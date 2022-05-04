#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "snake_s.h"


#define SNAKE_START_UP
#define SNAKE_PRINT_S
#define SNAKE_SNAKE_INIT
#define SNAKE_SCREEN_RESET_POSITION
#define SNAKE_RANDOM_F
#define SNAKE_MOVEMENT
#define SNAKE_GETCH_NOBLOCK
#define SNAKE_TAIL_REMOVE
#define SNAKE_GAME_O

/*
Special characters used for creating the tables will be: 201/187/205/186/200/188/
*/

#define N_ROW 20 // border row
#define N_COL 40 // border column

// variable declarations
// game=used in reset position, frog,a,b= used in creating frog random
// field[][]- used for the position for the character
// var=used to store the return from the function getch
// dir-used for conitonus movement direction
// speed-used to increase the  speed of snake
int i, j, field[N_ROW][N_COL], x, y, Gy_temp, head, tail, Game, frog, a, b, var, dir, speed;
char plname[20];
unsigned int score, high_score; // delcared as unsigned int to store long values

FILE *f;

#ifdef SNAKE_START_UP
void start_up()
{
	int t;
	for (t = 0; t < 5; t++)
	{
		printf("\n");
	}
	printf("\t\t\t\t\t***Welcome to the ***\n\n");
	printf("\n\t *********************************************************************************************");
	printf("\n\t  @@@@@@   @@    @@    @@@    @@    @@ @@@@@@@@     @@@@@@      @@@    @@     @@ @@@@@@@@ ");
	printf("\n\t @@    @@  @@@   @@   @@ @@   @@   @@  @@          @@    @@    @@ @@   @@@   @@@ @@       ");
	printf("\n\t @@        @@@@  @@  @@   @@  @@  @@   @@          @@         @@   @@  @@@@ @@@@ @@       ");
	printf("\n\t  @@@@@@   @@ @@ @@ @@     @@ @@@@@    @@@@@@      @@   @@@@ @@     @@ @@ @@@ @@ @@@@@@   ");
	printf("\n\t       @@  @@  @@@@ @@@@@@@@@ @@  @@   @@          @@    @@  @@@@@@@@@ @@     @@ @@       ");
	printf("\n\t @@    @@  @@   @@@ @@     @@ @@   @@  @@          @@    @@  @@     @@ @@     @@ @@       ");
	printf("\n\t  @@@@@@   @@    @@ @@     @@ @@    @@ @@@@@@@@     @@@@@@   @@     @@ @@     @@ @@@@@@@@");
	printf("\n\n\t **********************************************************************************************");
	for (t = 0; t < 3; t++)
	{
		printf("\n");
	}

	printf("\n\t\t\t\t Enter Your Name: ");
	scanf("%[^\n]", plname);
	getch();
	system("cls");

	//	clrscr();
	printf("\n\n\n\t\t\t\t### Rules of this Game is given below read carefully ###");
	printf("\n\n\n\t\t **************************************************************************************************************\n");
	printf("\n\t\t  @@     @@  @@@@@@@  @@      @@    @@@@@@@@  @@@@@@@     @@@@@@@@  @@          @@@    @@    @@ ");
	printf("\n\t\t  @@     @@ @@     @@ @@  @@  @@       @@    @@     @@    @@     @@ @@         @@ @@    @@  @@  ");
	printf("\n\t\t  @@     @@ @@     @@ @@  @@  @@       @@    @@     @@    @@     @@ @@        @@   @@    @@@@   ");
	printf("\n\t\t  @@@@@@@@@ @@     @@ @@  @@  @@       @@    @@     @@    @@@@@@@@  @@       @@     @@    @@    ");
	printf("\n\t\t  @@     @@ @@     @@ @@  @@  @@       @@    @@     @@    @@        @@       @@@@@@@@@    @@    ");
	printf("\n\t\t  @@     @@ @@     @@ @@  @@  @@       @@    @@     @@    @@        @@       @@     @@    @@    ");
	printf("\n\t\t  @@     @@  @@@@@@@   @@@  @@@        @@     @@@@@@@     @@        @@@@@@@@ @@     @@    @@    ");
	printf("\n\n\t\t ****************************************************************************************************************");

	printf("\n\n\t\t***  To Move Right -> Press 'D/d' ");
	printf("\n\t\t***  To Move Left  -> Press 'A/a'  ");
	printf("\n\t\t***  To Move Down -> Press 'S/s'  ");
	printf("\n\t\t***  To Move Up  -> Press 'W/w'  ");
	printf("\n\t\t*** The food will spawn at different coordinates on the screen");
	printf("\n\t\t*** Everytime the snake eats the food, its length will increase by one and the score will increase by 5");
	printf("\n\t\t*** Press P to pause the Game and press any button to resume the game");
	printf("\n\t\t*** The game will end when:");
	printf("\n\t\t*** - The snake will hit the border");
	printf("\n\t\t*** - The snake will hit itself");
	printf("\n\t\t*** - When the time limit of 4 mins cross");
	printf("\n");
	printf("\t\t***Press enter to start the Game***");
	printf("\n");
	printf("\n\t\t***Good Luck***");
	while (1)
	{
		var = getch_noblock(); // getting the data from keyboard
		if (var == 13)		   // if its enter(ascii value =13) to start the game
		{
			Game = 0;
			snake_init();
			break;
		}
	}
	system("Cls");
}
#endif

#ifdef SNAKE_PRINT_S
void print_s()
{
	// set_1
	for (i = 0; i <= N_COL + 1; i++)
	{
		if (i == 0)
		{
			printf("%c", 201);
		}
		else if (i == N_COL + 1)
		{
			printf("%c", 187);
		}
		else
		{
			printf("%c", 205);
		}
	}
	printf("\tCurrent Score: %d\tHigh Score: %d", score, high_score);
	printf("\n");
	// set_2
	for (i = 0; i <= N_ROW-1; i++)
	{
		printf("%c", 186);
		for (j = 0; j < N_COL; j++)
		{
			if (field[i][j] == 0)
			{
				printf(" ");
			}
			if (field[i][j] > 0 && field[i][j] != head)
			{
				printf("%c", 176);
			}

			if (field[i][j] == head) // head printing-178 ascii value
			{
				printf("%c", 178);
			}

			if (field[i][j] == -1)
			{
				printf("%c", 15);
			}
			if (j == N_COL - 1)
			{
				printf("%c\n", 186);
			}
		}
		// printf("\n");
	}
	// set_3
	for (i = 0; i <= N_COL + 1; i++)
	{
		if (i == 0)
		{
			printf("%c", 200);
		}
		else if (i == N_COL + 1)
		{
			printf("%c", 188);
		}
		else
		{
			printf("%c", 205);
		}
	}
	printf("\n\n*****************************************");
	printf("\n\n You have 20 secs to beat the high score");
	printf("\n\n*****************************************");
}
#endif

#ifdef SNAKE_SNAKE_INIT
void snake_init()
{
	f = fopen("Highscore.txt", "r");
	fscanf(f, "%d", &high_score);
	fclose(f);

	for (i = 0; i < N_ROW; i++)
	{
		for (j = 0; j < N_COL; j++)
		{
			field[i][j] = 0;
		}
	}

	// intilizing the starting value
	x = N_ROW / 2;
	y = N_COL / 2;
	Gy_temp = y;
	head = 5;
	tail = 1;
	Game = 0;
	frog = 0;
	dir = 'd';
	score = 0;
	speed = 99;

	for (i = 0; i < head; i++)
	{
		Gy_temp++;
		field[x][Gy_temp - head] = i + 1;
	}
}
#endif

#ifdef SNAKE_SCREEN_RESET_POSITION
void screen_reset_position()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}
#endif

#ifdef SNAKE_RANDOM_F
int random_f() // creating the random frogs
{
	srand(time(0));		 // creating the random generation with the starting position(here it time) so it is the starting time and it generates the random frog based on the time
	a = 1 + rand() % 18; // rand=creating the random numbers on the screen why 18 means it will come withing border
	b = 1 + rand() % 38;

	if (frog == 0 && field[a][b] == 0)
	{
		field[a][b] = -1;
		frog = 1;
		if (speed > 10 && score != 0)
		{
			speed -= 5;
		}
	}
	return 0;
}
#endif

#ifdef SNAKE_GETCH_NOBLOCK
int getch_noblock()
{
	if (_kbhit()) // keyboard is pressed or not is in header file conio.h
	{
		return getch();
	}
	else
	{
		return -1;
	}
}
#endif

#ifdef SNAKE_MOVEMENT
void movement()
{
	var = getch_noblock(); // getting the char from keyboard
	var = tolower(var);	   // making the char to lowercase

	if (((var == 'd' || var == 'a') || (var == 'w' || var == 's')) && (abs(dir - var) > 5)) // used for continous move
	{
		dir = var;
	}
	if (dir == 'd')
	{
		y++;
		if (field[x][y] != 0 && field[x][y] != -1) // it is used to indicate when the game is over here we are checking the snake can move aorund the border and can eat a frog(here for frog -1 is used) whenever the  it hits arount the body the game_o func wil becalled
		{
			game_o();
		}
		if (y == N_COL - 1) // moving into border parts
		{
			game_o();
		}
		if (field[x][y] == -1) // generating the frog randmoly after the first frog
		{
			frog = 0;
			tail -= 1; // snake size increase with the decrease in the tail to modify the size of snake
			score += 5;
		}
		head++;
		field[x][y] = head;
	}
	if (dir == 'a')
	{
		y--;
		if (field[x][y] != 0 && field[x][y] != -1) // it is used to indicate when the game is over here we are checking the snake can move aorund the border and can eat a frog(here for frog -1 is used) whenever the  it hits arount the body the game_o func wil becalled
		{
			game_o();
		}
		if (y == 0)
		{
			game_o();
		}
		if (field[x][y] == -1)
		{
			frog = 0;
			tail -= 1;
			score += 5;
		}
		head++;
		field[x][y] = head;
	}

	if (dir == 'w')
	{
		x--;
		if (field[x][y] != 0 && field[x][y] != -1) // it is used to indicate when the game is over here we are checking the snake can move aorund the border and can eat a frog(here for frog -1 is used) whenever the  it hits arount the body the game_o func wil becalled
		{
			game_o();
		}
		if (x == -1)
		{
			game_o();
		}
		if (field[x][y] == -1)
		{
			frog = 0;
			tail -= 1;
			score += 5;
		}
		head++;
		field[x][y] = head;
	}
	if (dir == 's')
	{
		x++;
		if (field[x][y] != 0 && field[x][y] != -1) // it is used to indicate when the game is over here we are checking the snake can move aorund the border and can eat a frog(here for frog -1 is used) whenever the  it hits arount the body the game_o func wil becalled
		{
			game_o();
		}
		if (x == N_ROW - 1)
		{
			game_o();
		}
		if (field[x][y] == -1)
		{
			frog = 0;
			tail -= 1;
			score += 5;
		}
		head++;
		field[x][y] = head;
	}
	if (var == 'p')
	{
		system("pause>nul");
		return;
	}
}
#endif

#ifdef SNAKE_TAIL_REMOVE
void tail_remove()
{
	for (i = 0; i < N_ROW; i++)
	{
		for (j = 0; j < N_COL; j++)
		{
			if (field[i][j] == tail)
			{
				field[i][j] = 0;
			}
		}
	}
	tail++;
}
#endif

#ifdef SNAKE_GAME_O
void game_o() // used to indicate when the game is over
{
	printf("\a"); // for sound
	Sleep(3000);
	system("Cls"); // clear the screen

	if (score > high_score)
	{
		printf("\n\n\n\t\t **********************************************************************************************************************\n");
		printf("\n\t\t  @@    @@ @@@@@@@@ @@      @@    @@     @@ @@@@  @@@@@@   @@     @@     @@@@@@   @@@@@@   @@@@@@@  @@@@@@@@@ @@@@@@@@ ");
		printf("\n\t\t  @@@   @@ @@       @@  @@  @@    @@     @@  @@  @@    @@  @@     @@    @@    @@ @@    @@ @@     @@ @@     @@ @@       ");
		printf("\n\t\t  @@@@  @@ @@       @@  @@  @@    @@     @@  @@  @@        @@     @@    @@       @@       @@     @@ @@     @@ @@       ");
		printf("\n\t\t  @@ @@ @@ @@@@@@   @@  @@  @@    @@@@@@@@@  @@  @@   @@@@ @@@@@@@@@     @@@@@@  @@       @@     @@ @@@@@@@   @@@@@@   ");
		printf("\n\t\t  @@  @@@@ @@       @@  @@  @@    @@     @@  @@  @@    @@  @@     @@          @@ @@       @@     @@ @@   @@   @@       ");
		printf("\n\t\t  @@   @@@ @@       @@  @@  @@    @@     @@  @@  @@    @@  @@     @@    @@    @@ @@    @@ @@     @@ @@    @@  @@       ");
		printf("\n\t\t  @@    @@ @@@@@@@@  @@@  @@@     @@     @@ @@@@  @@@@@@   @@     @@     @@@@@@   @@@@@@   @@@@@@@  @@     @@ @@@@@@@@ ");
		printf("\n\n\t\t *************************************************************************************************************************");
		printf("\n\n\t\t****  Congrtulations %s You Have made a New High Score \n\n\t\t", plname);
		system("pause");
		f = fopen("Highscore.txt", "w");
		fprintf(f, "%d", score);
		fprintf(f, "\n%s", plname);
		fclose(f);
	}
	system("Cls");
	printf("\n\n\n\t **********************************************************************************************************************\n");
	printf("\n\t\t   @@@@@@      @@@    @@     @@ @@@@@@@@     @@@@@@@  @@     @@ @@@@@@@@ @@@@@@@@  ");
	printf("\n\t\t  @@    @@    @@ @@   @@@   @@@ @@          @@     @@ @@     @@ @@       @@     @@ ");
	printf("\n\t\t  @@         @@   @@  @@@@ @@@@ @@          @@     @@ @@     @@ @@       @@     @@ ");
	printf("\n\t\t  @@   @@@@ @@     @@ @@ @@@ @@ @@@@@@      @@     @@ @@     @@ @@@@@@   @@@@@@@@  ");
	printf("\n\t\t  @@    @@  @@@@@@@@@ @@     @@ @@          @@     @@  @@   @@  @@       @@   @@   ");
	printf("\n\t\t  @@    @@  @@     @@ @@     @@ @@          @@     @@   @@ @@   @@       @@    @@  ");
	printf("\n\t\t   @@@@@@   @@     @@ @@     @@ @@@@@@@@     @@@@@@@     @@@    @@@@@@@@ @@     @@ ");
	printf("\n\n\t *************************************************************************************************************************");
	printf("\n\n\n\t\t***You Played Well %s Try To Beat The High Score Next Time", plname);
	printf("\n\n\t\t\t***Score: %d", score);
	printf("\n\n\t\tPress ENTER to play again or ESC to exit...");

	//	Game=1;						//game stops4
	while (1)
	{
		var = getch_noblock(); // getting the data from keyboard
		if (var == 13)		   // if its enter(ascii value =13) its init the snake again
		{
			Game = 0;
			snake_init();
			break;
		}
		else if (var == 27) // if its esc it will exit
		{
			Game = 1;
			break;
		}
	}
	system("Cls");
}
#endif
