/*随机生成食物: 首先食物必须出现在窗口的没有被占用的地方,所以需要定义一个窗口每个位置是否被占用
的判断方法,窗口的每个位置可以看作行列的组合,所以可以定义一个二维数组来表示窗口的每一个位置的状态*/

#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include "comsoleSize.h"
#include "CursorJump.h"
#include "SnakeStruct.h"

extern int flag[100][25];
extern sHead shead;

int foodx;
int foody;

void createFood()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 0x0C);

	srand(time(0));

    /*随机生成一个横坐标,一个纵坐标*/
	static int flag = 1;
	static int count = 0;
	count++;

	if (count > 90000)
	{
		count = 0;
		flag = 1;

		/*与蛇身和蛇头的覆盖一致,到达消失时间的时候,将光标重定位到上次食物的位置,然会在此位置输
		出空格,覆盖食物,然会再随机位置重新产生一个*/
		CursorJump(foodx, foody);

		deleteConsole(foodx, foody);

		printf("  "); /*之所以使用两个空格.是两个空格才可以全覆盖原来的食物(食物占两个光标位,空
		              格占一个光标位)*/
	}

	/*如果,标记为可输出,则重新获取随机值,如果蛇成功吃到食物,那么食物也应该消失,并且在一个随机位置出现下一个食物*/
	if (flag || (shead.x == foodx && shead.y == foody))
	{
		foodx = rand() % 98 + 1;
		foody = rand() % 23 + 1;
	}

	if (checkUsing(foodx,foody) && flag)
	{

		CursorJump(foodx, foody);

		//useConsole(foodx, foody);

		printf("●");
		flag = 0;
	}

}