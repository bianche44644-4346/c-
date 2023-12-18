/*显示贪吃蛇墙体*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "initWall.h"
#include "comsoleSize.h"
#include "SnakeStruct.h"

//#define row 25
//#define col 50 /*输出■,旁边会带有间隙,所以实际输出的■数是窗口字符列数的一半左右,为了使■均匀
//                 分布在窗口的边框上,我们输出的■个数应该是窗口cols的一半*/


/*隐藏光标*/
void hideCursor()
{
	CONSOLE_CURSOR_INFO curinfo; /*定义光标信息的结构体变量*/
	curinfo.dwSize = 1; /*此属性如果没有赋值的话,隐藏光标失败*/
	curinfo.bVisible = FALSE; /*将光标设置为不可见*/

	/*将此设置设置到窗口上*/
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &curinfo);
}

void initWall()
{
	/*修改窗口的大小,引号内部的形式如下,lines=25 cols=100两个的位置可以互换,但是=左右不能有空格 */
	/*此处多一行是为了容纳最下面显示的游戏数据(在调试过程中是为了容纳最下面的(按任意键结束))*/
	system("mode con  lines=26 cols=101");

    /*输出边框*/
	for (int i = 0; i < wall_row; i++)
	{
		for (int j = 0; j < wall_col; j++) 
		{
			if (i == 0 || i == wall_row-1)
			{
				useConsole(j, i,WALL);
				useConsole(j + (cols-wall_col), i, WALL);  /*因为■的原因,我们在100列的窗口只能输出50个,所以此处j的最大值为50,只能
				                              占有前面的部分,我们的窗口比所占有的部分大50,所以此处+50之后,才能表示墙占有
											  上面的一行,不然只能占有一半的距离,导致后面无法发生碰撞检测*/
				printf("■");
			}
			if (j == 0 || j == wall_col -1)
			{
				/*需要一个光标跳转,循环是无法将光标移动的,才能正常输出*/
				CursorJump(2*j,i);  /*我们进行跳转是实现,可以将■输出到边框上,因为循环不会使光
				                    标移动,所以无法如愿,所以我们需要使用光标跳转,将光标跳转到
									窗口的第一列和最后一列,结合上面,我们输出的实际列数为窗口列
									数的一半,所以当j到最大时,应该在窗口的中间,要想跳转到窗口的
									后面,就得将光标跳转到2j了*/

				useConsole(2 * j, i,WALL);

				printf("■");
			}
		}

		if (i < wall_row -1)
		{
			printf("\n");
		}
	}

	hideCursor();
}