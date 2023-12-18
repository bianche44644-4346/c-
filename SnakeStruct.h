#ifndef SNAKESTRUCT
#define SNAKESTRUCT

#define SnakeBodySize 100

#define snakeScore 5 /*��һ�������*/

/*���ƶ��ķ���*/
#define UP 1  
#define DOWN -1
#define LEFT 2
#define RIGHT -2

/*ʲôռ�ô���*/
#define WALL 1
#define HEAD 2
#define BODY 3

/*������ͷ������Ľṹ��,���ڼ�¼���ǵ�һЩ����,���������*/
typedef struct SnakeHead
{
	int x;
	int y;
	/*����һ�������ٶȺ������ٶ�*/ 
	int speedx;   /*ԭ������Ϊ,1.��������ں�����,���������ַ���ԭ��,���һ���ƶ�һ���Ḳ��ǰ���һ��,�����ں�����һ��
	              �ƶ�����λ��,2.�������������ƶ�����λ�þͻ�̫��,����������ֻ�ƶ�һ��λ��*/
	int speedy;
	int status;
	int location;

}sHead;

typedef struct SnakeBody
{
	int x;
	int y;
	//int speed;
	int status;
	int location;

}s_Body;

/*����˽ṹ�������ߵĳ���*/
typedef struct SnakeBodyTow
{
	s_Body body[SnakeBodySize]; /*��Ϊ�����岻ֹһ������ʹ�����������,����Ϊ�ߵ������䳤,��������
							����һ���㹻����ڴ�,(�����õ�100,Ҳ�����ô��ڵĳ��Ϳ�ĳ˻�����ʾ,��
							Ϊ�ߵĳ��Ȳ����ܳ�������,����Ҳû����)*/
	int count; /*��¼������*/
}sBody;

#endif // !SNAKESTRUCT

