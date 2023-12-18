/*光标跳转的函数封装*/
#include <Windows.h>

/*光标跳转函数*/
void CursorJump(int x, int y)
{
	/*我们修改了光标的位置还要将光标设置到窗口上,所以要获得窗口句柄,然后调用设置光标位置的函数来将光标设置
	到窗口的指定位置*/
	COORD pos; /*定义光标位置的结构体变量*/
	pos.X = x; /*光标的横坐标*/
	pos.Y = y; /*光标的纵坐标*/
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); /*获取输出窗口句柄*/
	SetConsoleCursorPosition(handle, pos); /*将修改后光标的位置设置到输出窗口的对应位置*/
}