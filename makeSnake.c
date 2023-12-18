/*贪吃蛇制作*/

#include <Windows.h>
#include <stdio.h>
#include "comsoleSize.h"
#include "CursorJump.h"
#include "SnakeStruct.h"
#include "initWall.h"
#include <conio.h>
#include <assert.h>

sHead shead;
sBody sbody;

extern int flag[lines][cols];
extern int foodx;
extern int foody;
int food_flag = 0;
int score = 0; 
int max_score = 0;
int cls = 0;


typedef struct
{
	int x;
	int y;
	int location;
}body_temp;

/*用于记录蛇末尾的坐标,和移动位置*/
body_temp snake_tail;

void initData()
{
	/*初始化蛇头*/
	shead.x = cols / 2;
	shead.y = lines / 2;
	shead.speedy = 1;
	shead.speedx = 2;
	shead.status = 1;
	shead.location = RIGHT;

    /*初始化蛇身*/
	sbody.count = 2; /*最开始蛇身默认为两个*/

	/*遍历所有的蛇身*/
	for (int i = 0; i < sbody.count; i++)
	{
		/*我们默认蛇身在蛇头的左侧,也就是每个蛇身比上一个位置*/

		/*第一个蛇身是相对于蛇头的特殊处理*/
		if (i == 0)
		{
			sbody.body[i].x = shead.x - 2;  /*-2的原因是因为■和■之间有空格,虽然差1但是有空格,空
										  格占了一位就是-2,前面的只是猜想,主要因为横向上如果相差一格会覆盖前面的半个
										  所以,才和前面的相聚两格*/
			sbody.body[i].y = shead.y;

			sbody.body[i].location = RIGHT;

		}
		else
		{
			sbody.body[i].x = sbody.body[i - 1].x - 2;

			sbody.body[i].y = sbody.body[i - 1].y;

			sbody.body[i].location = RIGHT;
		}
	}
	snake_tail.x = sbody.body[sbody.count - 1].x;
	snake_tail.y = sbody.body[sbody.count - 1].y;
}

void makeSnakeHead()
{
	initData();

	/*设置文字背景色为黑色,输出文字为红色*/
	//system("color 0C"); /*使用system修改颜色使对整体进行了修改,可我们这里需要实现头部和身体部位
	// 颜色不同,所以不适用,使用SetConsoleTextAtribute可以给不同字符设置不同的颜色,只需要在字符
	// 前重新设置一次颜色即可,system做不到,它只能对全体设置相同的颜色*/

	/*和前面光标跳转一样,我们设置颜色最终也是应用到窗口上,所以需要获得窗口句柄*/
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	/*给获得的窗口上面设置文字属性*/
	SetConsoleTextAttribute(handle, 0x0C); /*第二个参数为,十六进制的数,高位表示数字底色,低位表
	                                       示数字的颜色*/

	/*跳转光标在窗口中心输出蛇头(最开始的时候)*/
	CursorJump(shead.x,shead.y);

	/*蛇头占用位置*/
	useConsole(shead.x, shead.y,HEAD);

	printf("■");
}


void makeSnakeBody()
{

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 0x08);

	
	for (int i = 0; i < sbody.count; i++)
	{
		/*重定位蛇身*/
		CursorJump(sbody.body[i].x, sbody.body[i].y);

		useConsole(sbody.body[i].x, sbody.body[i].y,BODY);

		printf("■");
	}

	/*sbody.body[0].x = shead.x - 1.5;
	sbody.body[0].y = shead.y;

	CursorJump(sbody.body[0].x, sbody.body[0].y);

	printf("■");*/
}

/*蛇覆盖: 覆盖蛇前面移动的痕迹(实现原理:将光标重新定位到前面打印的位置然后打印一个空格,就能将前
面打印过的蛇痕迹消除掉了,因为我们C语言写这个是通过打印出来的,没有办法撤销前面打印的,所以一个思想
: 无法撤销,那就在哪个位置用一个不显示的输出覆盖原来输出(此处使用空格),这样就能消除原来的痕迹)*/
void snakeClear()
{
	/*蛇头前面位置覆盖*/

	CursorJump(shead.x, shead.y);

	/*蛇头占用位置*/
	deleteConsole(shead.x, shead.y);

	printf("  "); /*需要两个空格,原理上面说明了*/

	/*蛇身前面位置覆盖*/

	//if (food_flag)
	//{
	//	for (int i = 0; i < sbody.count - 1; i++)
	//	{
	//		food_flag = 0;
	//		/*重定位蛇身*/
	//		CursorJump(sbody.body[i].x, sbody.body[i].y);

	//		deleteConsole(sbody.body[i].x, sbody.body[i].y);

	//		printf("  ");  /*这块也需要两个空格,原理相同*/
	//	}
	//}

	for (int i = 0; i < sbody.count; i++)
	{
		/*重定位蛇身*/
		CursorJump(sbody.body[i].x, sbody.body[i].y);

		deleteConsole(sbody.body[i].x, sbody.body[i].y);

		printf("  ");  /*这块也需要两个空格,原理相同*/
	}
}

void makeSnake()
{
	/*头部制作*/
	makeSnakeHead();

	/*蛇身制作*/
    makeSnakeBody();
}

/*在窗口底部显示当前得分和历史最高分*/
void currentScore()
{

	CursorJump(0, lines - 1);  /*因为行数和列数都是从0开始的,所以第26行实际是跳转到25行就行*/

	printf("当前得分: %d 分", score);
}

void max_zhi_view()
{
	FILE* fp;
	char temp[10];

	/*打印历史最高分: 因为我们要求历史最高分是永久保存的,所以我们将它存放到磁盘中(文件中)*/

	fp = fopen("./贪吃蛇历史最高分.txt", "r+");
	assert(fp);


	rewind(fp);

	if (fgets(temp, 10, fp) == NULL)
	{
		exit(1);
	}

	//printf("%s", temp);

	max_score = atoi(temp);

	//if (score > max_score)
	//{
	//	//max_flag = 1;

	//	max_score = score;

	//	itoa(max_score, temp, 10);

	//	//printf("%s")

	//	if (fputs(temp, fp) == EOF)
	//	{
	//		exit(1);
	//	}
	//}

	CursorJump(20, lines - 1);

	printf("历史最高分: %d 分", max_score);

	fclose(fp);
}

void max_zhi_update()
{
	FILE* fp;
	char temp[10];

	fp = fopen("./贪吃蛇历史最高分.txt", "r+");
	assert(fp);

	max_score = atoi(temp);

	if (score > max_score)
	{
		//max_flag = 1;

		max_score = score;

		itoa(max_score, temp, 10);

		//printf("%s")

		if (fputs(temp, fp) == EOF)
		{
			exit(1);
		}
	}

	fclose(fp);
}

void snakEatFood()
{
	snake_tail.x = sbody.body[sbody.count - 1].x;
	snake_tail.y = sbody.body[sbody.count - 1].y;
	snake_tail.location = sbody.body[sbody.count - 1].location;

	currentScore();

	if (shead.x == foodx && shead.y == foody)
	{
		//printf("1");
		sbody.count++;
		//food_flag = 1;

		/*sbody.body[sbody.count - 1].x = snake_tail.x;
		sbody.body[sbody.count - 1].y = snake_tail.y;*/

		if (snake_tail.location == UP)
		{
			sbody.body[sbody.count - 1].x = snake_tail.x;
		    sbody.body[sbody.count - 1].y = snake_tail.y+1;
		}

		if (snake_tail.location == DOWN)
		{
			sbody.body[sbody.count - 1].x = snake_tail.x;
			sbody.body[sbody.count - 1].y = snake_tail.y - 1;
		}

		if (snake_tail.location == LEFT)
		{
			sbody.body[sbody.count - 1].x = snake_tail.x+1;
			sbody.body[sbody.count - 1].y = snake_tail.y;
		}

		if (snake_tail.location == RIGHT)
		{
			sbody.body[sbody.count - 1].x = snake_tail.x - 1;
			sbody.body[sbody.count - 1].y = snake_tail.y;
		}

		CursorJump(sbody.body[sbody.count - 1].x, sbody.body[sbody.count - 1].y);

		/*移动之后,在此位置占用窗口的位置*/
		useConsole(sbody.body[sbody.count - 1].x, sbody.body[sbody.count - 1].y,BODY);

		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, 0x08);

		printf("■");

		score += snakeScore;
	}

}

void alterWay(char ch)
{
	if (ch == 'w' || ch == 'W')
	{
		shead.location = UP;
	}
	else if (ch == 's' || ch == 'S')
	{
		shead.location = DOWN;
	}
	else if (ch == 'a' || ch == 'A')
	{
		shead.location = LEFT;
	}
	else if (ch == 'd' || ch == 'D')
	{
		shead.location = RIGHT;
	}
}

void keyOpera()
{
	char ch;

	/*有键盘操作的话,再进行相应变化*/
	if (kbhit()) /*kbhit函数用于检测是否有键盘输入,有返回非零值,没有返回零值*/
	{
		ch = getch();

		alterWay(ch);
	}

}

///*碰撞检测*/
//void collision()
//{
//	/*当蛇头撞墙的时候游戏失败*/
//	if ((checkUseWhat(shead.x,shead.y) == WALL || checkUseWhat(shead.x, shead.y) == BODY) && checkUsing(shead.x,shead.y) == 0)
//	{
//		exit(1);
//	}
//
//}

/*根据移动方向判断蛇的具体移动*/
/*子所以使用指针是因为,蛇头和身体中的坐标值随蛇移动发生变化,需要将内部的值进行修改,自然需要使用
指针*/
//void snake_Move(int *locate,int *x,int *y,int *speed)
//{
//	if (*locate == UP)
//	{
//		*y -= *speed;
//
//		CursorJump(*x, *y);
//	}
//	else if (*locate == DOWN)
//	{
//		*y += *speed;
//
//		CursorJump(*x, *y);
//	}
//	else if (*locate == LEFT)
//	{
//		*x -= *speed;
//
//		CursorJump(*x, *y);
//	}
//	else if (*locate == RIGHT)
//	{
//		*x += *speed;
//
//		CursorJump(*x, *y);
//	}
//
//}

void snake_Move()
{
	/*蛇移动没必要每个都移动,只需要控制好蛇头就行,后面的只要移动到前面蛇头或者蛇身的位置就行*/
    
	int temp_head_x = shead.x;
	int temp_head_y = shead.y;
	int temp_head_location = shead.location;
	body_temp btemp[100];
	int i;

	if (shead.location == UP)
	{
		shead.y -= shead.speedy;
		
		//CursorJump(shead.x, shead.y);
	}
	else if (shead.location == DOWN)
	{
		shead.y += shead.speedy;

		//CursorJump(shead.x, shead.y);
	}
	else if (shead.location == LEFT)
	{
		shead.x -= shead.speedx;

		//CursorJump(shead.x, shead.y);
	}
	else if (shead.location == RIGHT)
	{
		shead.x += shead.speedx;

		//CursorJump(shead.x, shead.y);
	}

	if (checkUsing(shead.x, shead.y))
	{
		useConsole(shead.x, shead.y, HEAD);
	}
	else
	{

		cls = 1;
	}

	CursorJump(shead.x, shead.y);

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 0x0C);

	printf("■");

	/*蛇身的移动,第一个位置的蛇身移动到蛇头的位置,后面的移动到前面身体的位置*/
	for (i = 0; i < sbody.count; i++)
	{
		btemp[i].x = sbody.body[i].x;
		btemp[i].y = sbody.body[i].y;
		btemp[i].location = sbody.body[i].location;

		if (i == 0)
		{
			sbody.body[i].x = temp_head_x;
			sbody.body[i].y = temp_head_y;
			sbody.body[i].location = temp_head_location;

			//CursorJump(sbody.body[i].x, sbody.body[i].y);
		}
		else {
			sbody.body[i].x = btemp[i-1].x;
			sbody.body[i].y = btemp[i-1].y;
			sbody.body[i].location = btemp[i-1].location;

			//CursorJump(sbody.body[i].x, sbody.body[i].y);
		}

		CursorJump(sbody.body[i].x, sbody.body[i].y);

		/*移动之后,在此位置占用窗口的位置*/
		useConsole(sbody.body[i].x, sbody.body[i].y,BODY);

		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, 0x08);

		printf("■");
	}
}

void snakeMove()
{
	static int count = 0;
	count++;
	
	if (count > 2000)
	{
		count = 0;

		snakeClear();

		/*移动*/
		//snake_Move(&shead.location, &shead.x, &shead.y, &shead.speed);

		/*HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, 0x0C);

		printf("■");*/

		//for (int i = 0; i < sbody.count; i++)
		//{

		//	//snake_Move(&sbody.body[i].location, &sbody.body[i].x, &sbody.body[i].y, 
		//		//&sbody.body[i].speed);

		//	/*HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		//	SetConsoleTextAttribute(handle, 0x08);

		//	printf("■");*/
		//}
		snake_Move();

		//collision();
	}

	keyOpera();
}