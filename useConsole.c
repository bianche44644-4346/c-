#include <stdio.h>
int flag[101][26];

void useConsole(int x, int y,int use)
{

	flag[x][y] = use;
}

void deleteConsole(int x, int y)
{
	flag[x][y] = 0;
}

//int checkUseWhat(int x, int y)
//{
//	if (flag[x][y] != 0)
//	{
//		return flag[x][y];
//	}
//	return -1;
//}

int checkUsing(int x, int y)
{
	if (flag[x][y] == 0)
	{
		//printf("%d",flag[0][55]);
		return 1;
	}
	else {
		return 0;
	}
}