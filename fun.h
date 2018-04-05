#pragma once

#include<stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "myHead.h"

#define SIZE 1

typedef struct
{
	char name[30];
	int score;
}player;


bool InitMetrix(int (*sz)[DIMENSION]);
bool ShowMetrix(int (*sz)[DIMENSION]);
bool IsAlive(int (*sz)[DIMENSION],int score);
bool IsWin(int (*sz)[DIMENSION]);

bool save(player *pPlyr);
bool read(player *pPlyr);
bool InputMsg(player *pPlyr,int score);

int MoveUp(int (*sz)[DIMENSION]);
int MoveDown(int (*sz)[DIMENSION]);
int MoveLeft(int (*sz)[DIMENSION]);
int MoveRight(int (*sz)[DIMENSION]);
int RandNum(int (*sz)[DIMENSION]);