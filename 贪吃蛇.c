#include "comsoleSize.h"
#include "CursorJump.h"
#include "SnakeStruct.h"
#include "initWall.h"
#include <stdio.h>

extern int cls;

int main()
{
	system("TITLE Ã∞≥‘…ﬂ");

	system("mode con  lines=26 cols=101");

	initWall();

	max_zhi_view();

	makeSnake();

	//currentScore();

	while (1)
	{
		createFood();

		//snakEatFood();

		snakeMove();

		snakEatFood();

		max_zhi_update();

		if (cls)
		{
			system("cls");

			system("color 0C");

			CursorJump(cols / 2 - 5, lines / 2);
			printf("GameOver!!!");

			getchar(); /*‘› ±»√≥Ã–Ú‘›Õ£*/
		}
	}

	return 0;
}