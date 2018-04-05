#include <conio.h>

#include "fun.h"
#include "myHead.h"


int g_sz[DIMENSION][DIMENSION] = {0};

int score = 0;

int main()
{
	player plyr[SIZE] = {0};
	char t = 0;

	if (false == read(plyr))
	{
		save(plyr);
	}

	printf("2048 game    control w:up s:down a:right d:left\n\n");

	InitMetrix(g_sz);
	ShowMetrix(g_sz);

	while((t=_getche()) != '\r') 
	{
		system("cls");	//clear screen
		printf("2048 game    control w:up s:down a:right d:left\n\n");

		switch(t)
		{
		case 'w':
			score += MoveUp(g_sz);
			break;
		case 's':
			score += MoveDown(g_sz);
			break;
		case 'a':
			score += MoveLeft(g_sz);
			break;
		case 'd':
			score += MoveRight(g_sz);
			break;
		}
 		
		//only if push the control button,do RandNum function  
		if ( ('w'==t) || ('s'==t) || ('a'==t) || ('d'==t) )
		{
			RandNum(g_sz);
		}

		
		ShowMetrix(g_sz);

		printf("your score = %d\n",score);
		printf("top score is %s %d\n\n",plyr->name,plyr->score);

		if (false == IsAlive(g_sz,score))
		{
			printf("No more step!!\n");
			break;
		}
		if (true == IsWin(g_sz))
		{
			printf("Congratulation! You got 2048!!\n");
		}
		
	}

	if (score > plyr->score)
	{
		printf("You got the top score!\n");
		printf("input your name(in 30 chars):") ;

		InputMsg(plyr,score);
		save(plyr);
	}


	system("pause");
	return 0;
}

