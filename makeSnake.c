/*̰��������*/

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

/*���ڼ�¼��ĩβ������,���ƶ�λ��*/
body_temp snake_tail;

void initData()
{
	/*��ʼ����ͷ*/
	shead.x = cols / 2;
	shead.y = lines / 2;
	shead.speedy = 1;
	shead.speedx = 2;
	shead.status = 1;
	shead.location = RIGHT;

    /*��ʼ������*/
	sbody.count = 2; /*�ʼ����Ĭ��Ϊ����*/

	/*�������е�����*/
	for (int i = 0; i < sbody.count; i++)
	{
		/*����Ĭ����������ͷ�����,Ҳ����ÿ���������һ��λ��*/

		/*��һ���������������ͷ�����⴦��*/
		if (i == 0)
		{
			sbody.body[i].x = shead.x - 2;  /*-2��ԭ������Ϊ���͡�֮���пո�,��Ȼ��1�����пո�,��
										  ��ռ��һλ����-2,ǰ���ֻ�ǲ���,��Ҫ��Ϊ������������һ��Ḳ��ǰ��İ��
										  ����,�ź�ǰ����������*/
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

	/*�������ֱ���ɫΪ��ɫ,�������Ϊ��ɫ*/
	//system("color 0C"); /*ʹ��system�޸���ɫʹ������������޸�,������������Ҫʵ��ͷ�������岿λ
	// ��ɫ��ͬ,���Բ�����,ʹ��SetConsoleTextAtribute���Ը���ͬ�ַ����ò�ͬ����ɫ,ֻ��Ҫ���ַ�
	// ǰ��������һ����ɫ����,system������,��ֻ�ܶ�ȫ��������ͬ����ɫ*/

	/*��ǰ������תһ��,����������ɫ����Ҳ��Ӧ�õ�������,������Ҫ��ô��ھ��*/
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	/*����õĴ�������������������*/
	SetConsoleTextAttribute(handle, 0x0C); /*�ڶ�������Ϊ,ʮ�����Ƶ���,��λ��ʾ���ֵ�ɫ,��λ��
	                                       ʾ���ֵ���ɫ*/

	/*��ת����ڴ������������ͷ(�ʼ��ʱ��)*/
	CursorJump(shead.x,shead.y);

	/*��ͷռ��λ��*/
	useConsole(shead.x, shead.y,HEAD);

	printf("��");
}


void makeSnakeBody()
{

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 0x08);

	
	for (int i = 0; i < sbody.count; i++)
	{
		/*�ض�λ����*/
		CursorJump(sbody.body[i].x, sbody.body[i].y);

		useConsole(sbody.body[i].x, sbody.body[i].y,BODY);

		printf("��");
	}

	/*sbody.body[0].x = shead.x - 1.5;
	sbody.body[0].y = shead.y;

	CursorJump(sbody.body[0].x, sbody.body[0].y);

	printf("��");*/
}

/*�߸���: ������ǰ���ƶ��ĺۼ�(ʵ��ԭ��:��������¶�λ��ǰ���ӡ��λ��Ȼ���ӡһ���ո�,���ܽ�ǰ
���ӡ�����ߺۼ���������,��Ϊ����C����д�����ͨ����ӡ������,û�а취����ǰ���ӡ��,����һ��˼��
: �޷�����,�Ǿ����ĸ�λ����һ������ʾ���������ԭ�����(�˴�ʹ�ÿո�),������������ԭ���ĺۼ�)*/
void snakeClear()
{
	/*��ͷǰ��λ�ø���*/

	CursorJump(shead.x, shead.y);

	/*��ͷռ��λ��*/
	deleteConsole(shead.x, shead.y);

	printf("  "); /*��Ҫ�����ո�,ԭ������˵����*/

	/*����ǰ��λ�ø���*/

	//if (food_flag)
	//{
	//	for (int i = 0; i < sbody.count - 1; i++)
	//	{
	//		food_flag = 0;
	//		/*�ض�λ����*/
	//		CursorJump(sbody.body[i].x, sbody.body[i].y);

	//		deleteConsole(sbody.body[i].x, sbody.body[i].y);

	//		printf("  ");  /*���Ҳ��Ҫ�����ո�,ԭ����ͬ*/
	//	}
	//}

	for (int i = 0; i < sbody.count; i++)
	{
		/*�ض�λ����*/
		CursorJump(sbody.body[i].x, sbody.body[i].y);

		deleteConsole(sbody.body[i].x, sbody.body[i].y);

		printf("  ");  /*���Ҳ��Ҫ�����ո�,ԭ����ͬ*/
	}
}

void makeSnake()
{
	/*ͷ������*/
	makeSnakeHead();

	/*��������*/
    makeSnakeBody();
}

/*�ڴ��ڵײ���ʾ��ǰ�÷ֺ���ʷ��߷�*/
void currentScore()
{

	CursorJump(0, lines - 1);  /*��Ϊ�������������Ǵ�0��ʼ��,���Ե�26��ʵ������ת��25�о���*/

	printf("��ǰ�÷�: %d ��", score);
}

void max_zhi_view()
{
	FILE* fp;
	char temp[10];

	/*��ӡ��ʷ��߷�: ��Ϊ����Ҫ����ʷ��߷������ñ����,�������ǽ�����ŵ�������(�ļ���)*/

	fp = fopen("./̰������ʷ��߷�.txt", "r+");
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

	printf("��ʷ��߷�: %d ��", max_score);

	fclose(fp);
}

void max_zhi_update()
{
	FILE* fp;
	char temp[10];

	fp = fopen("./̰������ʷ��߷�.txt", "r+");
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

		/*�ƶ�֮��,�ڴ�λ��ռ�ô��ڵ�λ��*/
		useConsole(sbody.body[sbody.count - 1].x, sbody.body[sbody.count - 1].y,BODY);

		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, 0x08);

		printf("��");

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

	/*�м��̲����Ļ�,�ٽ�����Ӧ�仯*/
	if (kbhit()) /*kbhit�������ڼ���Ƿ��м�������,�з��ط���ֵ,û�з�����ֵ*/
	{
		ch = getch();

		alterWay(ch);
	}

}

///*��ײ���*/
//void collision()
//{
//	/*����ͷײǽ��ʱ����Ϸʧ��*/
//	if ((checkUseWhat(shead.x,shead.y) == WALL || checkUseWhat(shead.x, shead.y) == BODY) && checkUsing(shead.x,shead.y) == 0)
//	{
//		exit(1);
//	}
//
//}

/*�����ƶ������ж��ߵľ����ƶ�*/
/*������ʹ��ָ������Ϊ,��ͷ�������е�����ֵ�����ƶ������仯,��Ҫ���ڲ���ֵ�����޸�,��Ȼ��Ҫʹ��
ָ��*/
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
	/*���ƶ�û��Ҫÿ�����ƶ�,ֻ��Ҫ���ƺ���ͷ����,�����ֻҪ�ƶ���ǰ����ͷ���������λ�þ���*/
    
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

	printf("��");

	/*������ƶ�,��һ��λ�õ������ƶ�����ͷ��λ��,������ƶ���ǰ�������λ��*/
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

		/*�ƶ�֮��,�ڴ�λ��ռ�ô��ڵ�λ��*/
		useConsole(sbody.body[i].x, sbody.body[i].y,BODY);

		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, 0x08);

		printf("��");
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

		/*�ƶ�*/
		//snake_Move(&shead.location, &shead.x, &shead.y, &shead.speed);

		/*HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, 0x0C);

		printf("��");*/

		//for (int i = 0; i < sbody.count; i++)
		//{

		//	//snake_Move(&sbody.body[i].location, &sbody.body[i].x, &sbody.body[i].y, 
		//		//&sbody.body[i].speed);

		//	/*HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		//	SetConsoleTextAttribute(handle, 0x08);

		//	printf("��");*/
		//}
		snake_Move();

		//collision();
	}

	keyOpera();
}