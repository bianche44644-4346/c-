/*�����ת�ĺ�����װ*/
#include <Windows.h>

/*�����ת����*/
void CursorJump(int x, int y)
{
	/*�����޸��˹���λ�û�Ҫ��������õ�������,����Ҫ��ô��ھ��,Ȼ��������ù��λ�õĺ��������������
	�����ڵ�ָ��λ��*/
	COORD pos; /*������λ�õĽṹ�����*/
	pos.X = x; /*���ĺ�����*/
	pos.Y = y; /*����������*/
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); /*��ȡ������ھ��*/
	SetConsoleCursorPosition(handle, pos); /*���޸ĺ����λ�����õ�������ڵĶ�Ӧλ��*/
}