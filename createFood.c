/*�������ʳ��: ����ʳ���������ڴ��ڵ�û�б�ռ�õĵط�,������Ҫ����һ������ÿ��λ���Ƿ�ռ��
���жϷ���,���ڵ�ÿ��λ�ÿ��Կ������е����,���Կ��Զ���һ����ά��������ʾ���ڵ�ÿһ��λ�õ�״̬*/

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

    /*�������һ��������,һ��������*/
	static int flag = 1;
	static int count = 0;
	count++;

	if (count > 90000)
	{
		count = 0;
		flag = 1;

		/*���������ͷ�ĸ���һ��,������ʧʱ���ʱ��,������ض�λ���ϴ�ʳ���λ��,Ȼ���ڴ�λ����
		���ո�,����ʳ��,Ȼ�������λ�����²���һ��*/
		CursorJump(foodx, foody);

		deleteConsole(foodx, foody);

		printf("  "); /*֮����ʹ�������ո�.�������ո�ſ���ȫ����ԭ����ʳ��(ʳ��ռ�������λ,��
		              ��ռһ�����λ)*/
	}

	/*���,���Ϊ�����,�����»�ȡ���ֵ,����߳ɹ��Ե�ʳ��,��ôʳ��ҲӦ����ʧ,������һ�����λ�ó�����һ��ʳ��*/
	if (flag || (shead.x == foodx && shead.y == foody))
	{
		foodx = rand() % 98 + 1;
		foody = rand() % 23 + 1;
	}

	if (checkUsing(foodx,foody) && flag)
	{

		CursorJump(foodx, foody);

		//useConsole(foodx, foody);

		printf("��");
		flag = 0;
	}

}