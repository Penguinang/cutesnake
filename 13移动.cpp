#include"头文件.h"
#include"宏定义.h"
#include"结构体.h"
#include"所有函数声明.h"
#include"全局变量声明（写在其他次要文件）.h"

/*移动：
		*/
int move()
{

	float x0, y0;
	char key ;

	/*对输入的键值进行采集*/
	if (_kbhit()) 
	{
		while ((key = _getch()) == 224)
			key = _getch();
		
		switch (key)
		{
		case'a':direction += B; break;
		case'd':direction -= B; break;
		case'W':case 72:_up(); break;
		case'S':case 80:_down(); break;
		case'A':case 75:_left(); break;
		case'D':case 77:_right(); break;
		case's':case 27:pause(); break;//U s Esc 都是暂停
		case'w':case'I':realT=RUSHT; break;//w I 是加速
		}
		
		if (direction > 360)
			direction -= 360;
		if (direction < 0)
			direction += 360;
	}

	/*身体移动*/
	SNAKE*p1 = tail, *p2 = tail;
	p1 = p2->preview;
	if (p1 != 0)
	{
		for (; p1 != 0;)
		{
			p2->x = p1->x;
			p2->y = p1->y;
			p2 = p1;
			p1 = p2->preview;
		}
	}

	/*头部移动*/
	head->x += cos(direction*DEGREE)*DX;
	head->y -= sin(direction*DEGREE)*DX;

	/*翻墙可用*/
	if (***map == 1)
	{
		if (head->x > 800)
			head->x -= 800;
		if (head->x < 0)
			head->x += 800;
		if (head->y > 600)
			head->y -= 600;
		if (head->y < 0)
			head->y += 600;
	}

	
	return 1;
}

/*向上走*/
int _up()
{
	if (direction == 270)//方向向下时不能向上走
		return 1;
	if (direction <= 90 + B&&direction >= 90 - B)
	{
		direction = 90;
		return 1;
	}
	if (direction > 90 + B&&direction < 270)
	{
		direction -= B;
		return 1;
	}
	else
	{
		direction += B;
		return 1;
	}
	return 1;
}

/*向下走*/
int _down()
{
	if (direction == 90)
		return 1;
	if (direction <= 270 + B&&direction >= 270 - B)
	{
		direction = 270;
		return 1;
	}
	if (direction < 270 - B&&direction > 90)
	{
		direction += B;
		return 1;
	}
	else
	{
		direction -= B;
		return 1;
	}
	return 1;
}

/*向左走*/
int _left()
{
	if (direction == 0)
		return 1;
	if (direction <= 180 + B&&direction >= 180 - B)
	{
		direction = 180;
		return 1;
	}
	if (direction < 180 - B&&direction > 0)
	{
		direction += B;
		return 1;
	}
	else
	{
		direction -= B;
		return 1;
	}
	return 1;
}

/*向右走*/
int _right()
{
	if (direction == 180)
		return 1;
	if (direction <=  B||direction >= 360 - B)
	{
		direction = 0;
		return 1;
	}
	if (direction < 180&&direction > B)
	{
		direction -= B;
		return 1;
	}
	else
	{
		direction += B;
		return 1;
	}
	return 1;
}