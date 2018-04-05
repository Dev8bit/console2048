#include "fun.h"

bool save(player *pPlyr)
{
	FILE *fp;

	if((fopen_s(&fp,"dat","w"))!=NULL)
	{
		printf("record data error!\n");
		return false;
	}

	if(fwrite(pPlyr, sizeof(player), SIZE, fp) != 1)
	{	
		printf("record data error!\n");
		return false;
	}

	fclose(fp);
	return true;
}

bool read(player *pPlyr)
{
	FILE *fp;

	if((fopen_s(&fp,"dat","r")) != NULL)
	{
		printf("record data error!\n");
		return false;
	}

	if(fread(pPlyr, sizeof(player), SIZE, fp) != 1)
	{
		printf("record data error!\n");
		return false;
	}

	fclose(fp);
	return true;
}

bool InputMsg(player *pPlyr,int score)		//input your name(in DIMENSION - 10 chars)
{
	int result = 0;
	while(result != 1)
	{
		result = scanf_s("%s",pPlyr->name,DIMENSION - 10) ;
		pPlyr->score = score ;
		if (result != 1)
		{
			printf("please input right value\n") ;
		}

		fflush(stdin);
	}

	return true;
}

bool InitMetrix(int (*sz)[DIMENSION])
{
	for (int i = 0 ; i < DIMENSION; ++i)
	{
		for (int j = 0 ; j < DIMENSION ; ++j)
		{
			sz[i][j] = 0; //array initialize 0
		}
	}
	RandNum(sz);
	RandNum(sz);
	return true;
}

bool ShowMetrix(int (*sz)[DIMENSION])
{
	int i = 0;
	int t = 0;
	while (i < DIMENSION*DIMENSION)
	{
		t = *(*sz+i++) ;
		if (0 == t)
		{
			printf("|   ");
		}
		else
		{
			printf("| %d ",t);
		}

		if (i%DIMENSION == 0)
		{
			printf("|\n");

			for(int i = 0; i < DIMENSION; ++i)
			{
				printf("----");
			}

			printf("\n");
		}	
	}

	return true;
}

bool IsAlive(int (*sz)[DIMENSION],int score)
{
	//	memcpy
	int temp[DIMENSION][DIMENSION] = {0};
	memcpy(temp,sz,DIMENSION*DIMENSION*sizeof(int));

	int MemScore = score ;

	MemScore += MoveDown(sz);
	MemScore += MoveRight(sz);
	MemScore += MoveLeft(sz);
	MemScore += MoveUp(sz);

	int i = 0;
	int t = 0;
	bool bflag_0 = false ;

	while (i < DIMENSION*DIMENSION)
	{
		t = *(*sz+i++) ;

		if (0 == t)
		{
			bflag_0 = true;
			break;
		}
	}

	if ( (score == MemScore) && (!bflag_0) )
	{
		return false;
	}

	memcpy(sz,temp,DIMENSION*DIMENSION*sizeof(int));

	return true;
}

bool IsWin(int (*sz)[DIMENSION])
{
	bool bflag_Win = false ;
	int i = 0 ;
	int t = 0 ;

	while (i < DIMENSION*DIMENSION)
	{
		t = *(*sz+i++) ;

		if (NUM_2048 == t)
		{
			bflag_Win = true;
			break;
		}
	}

	return bflag_Win;
}


int MoveUp(int (*sz)[DIMENSION])   
{
	int score = 0 ;
	int temp = 0 ;

	for (int i=0;i<DIMENSION;++i)		//move 0
	{
		for (int y=0;y<DIMENSION - 1;++y)
		{
			for(int j=0;j<DIMENSION - 1;++j)
			{
				if (0 == sz[j][i])
				{
					temp = sz[j][i];
					sz[j][i] = sz[j+1][i];
					sz[j+1][i] = temp;
				}
			}
		}
	}

	for (int i = 0 ; i < DIMENSION; ++i)
	{
		int step = 0 ;
		for (int j = DIMENSION - 1 ; j >0 ; --j)
		{
			if (0 != sz[j][i])
			{
				if (sz[j][i] == sz[j-1][i])
				{ 
					sz[j-1][i] *= 2;
					score += sz[j-1][i];
					sz[j][i] = 0;

					while (0 < step)   //move 0
					{
						temp = sz[j][i] ;
						sz[j][i] = sz[j+1][i] ;
						sz[j+1][i] = temp ;
						++j;
						--step ;
					}

					break;
				}			
			}

			++step;
		}
	}

	return score;
}

int MoveDown(int (*sz)[DIMENSION])   //
{
	int score = 0 ;
	int temp = 0;

	for(int i=0;i<DIMENSION;++i)	//move 0
	{
		for (int y=DIMENSION - 1;y>0;--y)
		{
			for (int j=DIMENSION - 1;j>0;--j)
			{
				if (0 == sz[j][i])
				{
					temp = sz[j][i];
					sz[j][i] = sz[j-1][i];
					sz[j-1][i] = temp;
				}
			}
		}
	}

	for (int i = 0 ; i < DIMENSION; ++i)
	{
		int step = 0;
		for (int j = 0 ; j < DIMENSION - 1 ; ++j)
		{
			if (0 != sz[j][i])
			{
				if (sz[j][i] == sz[j+1][i])
				{
					sz[j+1][i] *= 2;
					score += sz[j+1][i];
					sz[j][i] = 0;

					while (0 < step)   //move 0
					{
						temp = sz[j][i] ;
						sz[j][i] = sz[j-1][i] ;
						sz[j-1][i] = temp ;
						--j;
						--step ;
					}

					break;
				}			

			}

			++step;			
		}
	}

	return score;
}

int MoveRight(int (*sz)[DIMENSION])   //
{
	int score = 0 ;
	int temp = 0 ;

	for (int i=0;i<DIMENSION;++i)
	{
		for (int y=DIMENSION - 1;y>0;--y)
		{
			for (int j=DIMENSION - 1;j>0;--j)
			{
				if (0 == sz[i][j])
				{
					temp = sz[i][j];
					sz[i][j] = sz[i][j-1];
					sz[i][j-1] = temp;
				}			
			}
		}
	}

	for (int i = 0 ; i < DIMENSION; ++i)
	{
		int step = 0;
		for (int j = 0 ; j < DIMENSION - 1 ; ++j)
		{
			if (0 != sz[i][j])
			{
				if (sz[i][j] == sz[i][j+1])
				{
					sz[i][j+1] *= 2;
					score += sz[i][j+1];
					sz[i][j] = 0;

					while (0 < step)   //move 0
					{
						temp = sz[i][j] ;
						sz[i][j] = sz[i][j-1] ;
						sz[i][j-1] = temp ;
						--j;
						--step ;
					}

					break;
				}
			}
			++step ;
		}
	}

	return score;
}

int MoveLeft(int (*sz)[DIMENSION])   //
{
	int score = 0 ;
	int temp = 0 ;

	for (int i=0;i<DIMENSION;++i)
	{
		for (int y=0;y<DIMENSION - 1;++y)
		{
			for (int j=0;j<DIMENSION - 1;++j)
			{
				if (0 == sz[i][j])
				{
					temp = sz[i][j];
					sz[i][j] = sz[i][j+1];
					sz[i][j+1] = temp;
				}			
			}
		}
	}

	for (int i = 0 ; i < DIMENSION; ++i)
	{
		int step = 0 ;
		for (int j = DIMENSION - 1 ; j >0 ; --j)
		{
			if (0 != sz[i][j])
			{
				if (sz[i][j] == sz[i][j-1])
				{
					sz[i][j-1] *= 2;
					score += sz[i][j-1];
					sz[i][j] = 0;

					while (0 < step)   //move 0
					{
						temp = sz[i][j] ;
						sz[i][j] = sz[i][j+1] ;
						sz[i][j+1] = temp ;
						++j;
						--step ;
					}

					break;
				}
			}

			++step ;

		}
	}

	return score;
}

int RandNum(int (*sz)[DIMENSION])
{
	srand((unsigned int)time(NULL));
	int num = 0;
	int count = DIMENSION*DIMENSION;

	int x = 0;
	int y = 0;

	num = (rand()%5) ? 2 : 4;	//create number 2 DIMENSION   DIMENSION:1

	while(--count)
	{
		x = rand()%DIMENSION;
		y = rand()%DIMENSION;

		if (0 == sz[x][y])
		{
			sz[x][y] = num;
			break;
		}
	}


	return 0;
}


