/*��ʾ̰����ǽ��*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "initWall.h"
#include "comsoleSize.h"
#include "SnakeStruct.h"

//#define row 25
//#define col 50 /*�����,�Ա߻���м�϶,����ʵ������ġ����Ǵ����ַ�������һ������,Ϊ��ʹ������
//                 �ֲ��ڴ��ڵı߿���,��������ġ�����Ӧ���Ǵ���cols��һ��*/


/*���ع��*/
void hideCursor()
{
	CONSOLE_CURSOR_INFO curinfo; /*��������Ϣ�Ľṹ�����*/
	curinfo.dwSize = 1; /*���������û�и�ֵ�Ļ�,���ع��ʧ��*/
	curinfo.bVisible = FALSE; /*���������Ϊ���ɼ�*/

	/*�����������õ�������*/
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &curinfo);
}

void initWall()
{
	/*�޸Ĵ��ڵĴ�С,�����ڲ�����ʽ����,lines=25 cols=100������λ�ÿ��Ի���,����=���Ҳ����пո� */
	/*�˴���һ����Ϊ��������������ʾ����Ϸ����(�ڵ��Թ�������Ϊ�������������(�����������))*/
	system("mode con  lines=26 cols=101");

    /*����߿�*/
	for (int i = 0; i < wall_row; i++)
	{
		for (int j = 0; j < wall_col; j++) 
		{
			if (i == 0 || i == wall_row-1)
			{
				useConsole(j, i,WALL);
				useConsole(j + (cols-wall_col), i, WALL);  /*��Ϊ����ԭ��,������100�еĴ���ֻ�����50��,���Դ˴�j�����ֵΪ50,ֻ��
				                              ռ��ǰ��Ĳ���,���ǵĴ��ڱ���ռ�еĲ��ִ�50,���Դ˴�+50֮��,���ܱ�ʾǽռ��
											  �����һ��,��Ȼֻ��ռ��һ��ľ���,���º����޷�������ײ���*/
				printf("��");
			}
			if (j == 0 || j == wall_col -1)
			{
				/*��Ҫһ�������ת,ѭ�����޷�������ƶ���,�����������*/
				CursorJump(2*j,i);  /*���ǽ�����ת��ʵ��,���Խ���������߿���,��Ϊѭ������ʹ��
				                    ���ƶ�,�����޷���Ը,����������Ҫʹ�ù����ת,�������ת��
									���ڵĵ�һ�к����һ��,�������,���������ʵ������Ϊ������
									����һ��,���Ե�j�����ʱ,Ӧ���ڴ��ڵ��м�,Ҫ����ת�����ڵ�
									����,�͵ý������ת��2j��*/

				useConsole(2 * j, i,WALL);

				printf("��");
			}
		}

		if (i < wall_row -1)
		{
			printf("\n");
		}
	}

	hideCursor();
}