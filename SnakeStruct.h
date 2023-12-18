#ifndef SNAKESTRUCT
#define SNAKESTRUCT

#define SnakeBodySize 100

#define snakeScore 5 /*吃一个得五分*/

/*蛇移动的方向*/
#define UP 1  
#define DOWN -1
#define LEFT 2
#define RIGHT -2

/*什么占用窗口*/
#define WALL 1
#define HEAD 2
#define BODY 3

/*定义蛇头和蛇身的结构体,用于记录它们的一些属性,比如坐标等*/
typedef struct SnakeHead
{
	int x;
	int y;
	/*设置一个横向速度和纵向速度*/ 
	int speedx;   /*原因是因为,1.■的输出在横向上,可能由于字符的原因,如果一次移动一个会覆盖前面的一半,所以在横向上一次
	              移动两个位置,2.但是在纵向上移动两个位置就会太宽,所以纵向上只移动一个位置*/
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

/*定义此结构方便存放蛇的长度*/
typedef struct SnakeBodyTow
{
	s_Body body[SnakeBodySize]; /*因为蛇身体不止一个所以使用数组来存放,又因为蛇的身体会变长,所以我们
							建立一个足够大的内存,(这里用的100,也可以用窗口的长和宽的乘积来表示,因
							为蛇的长度不可能超过窗口,超过也没意义)*/
	int count; /*记录舍身长度*/
}sBody;

#endif // !SNAKESTRUCT

