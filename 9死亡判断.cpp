#include"头文件.h"
#include"宏定义.h"
#include"结构体.h"
#include"所有函数声明.h"
#include"全局变量声明（写在其他次要文件）.h"

/*死亡判断：
		*/
int _death_judge()
{

	SNAKE*p;
	p = head == tail ? head : head->next;
	/*检测自身有没有碰撞，只有两节或一节时不会碰撞*/
	if (head != tail&&head->next != tail)
		for (p = head->next->next; p != 0; p = p->next) 
		{
			if (pow(p->x - head->x, 2) + pow(p->y - head->y, 2) < pow(2 * R, 2))
			{
				gameRes = -1;
				return 1;
			}
		}

	/*翻墙不可用*/
	if(***map==0)
	/*检测有没有与墙碰撞*/
	if (fabs(head->x-400) > 400-R || fabs(head->y-300) > 300-R)
	{
		gameRes = -1;
		return 1;
	}

	if (wall_check(head->x, head->y, R))
		gameRes = -1;
	//int(*p_poly)[11][2],*xy,i;//p_poly指向多边形

	//for (p_poly = map+1,i=1;***p_poly!=0&&i<=20;p_poly++,i++)//检测有没有与障碍碰撞，***p_poly是多边形边数
	//{
	//	xy = *(*p_poly + 1);
	//				//xy指向当前二维数组的第二个一维数组的第一个元素，即当前多边形的第一个顶点的横坐标
	//	if (_duang(xy, head->x, head->y, R) == 1)
	//	{
	//		
	//		gameRes = -1;
	//		return 1;
	//	}
	//		
	//	
	//}
	return 0;
}


/*检测一个圆是否与一个直线相交：
			传入的参数是圆的坐标、直线上两点坐标*/
int _meet_line(int circlex,int circley,int r,int x1,int y1,int x2,int y2)
{
	int d,a,b,c;
	a = y1 - y2;
	b = x2 - x1;
	c = y1*x2 - y2*x1;
	d = abs(a*circlex + b*circley + c) / sqrt(a*a + b*b);
	if (d < r)
		return 1;
	return 1;
}

/*检测圆是否与一个多边形发生碰撞：
			传入的参数是矩形第一个点的横坐标地址，和圆的坐标、半径*/
int _duang(int *p,int circle_x,int circle_y,int r)
{
	/*x1,x2,y1,y2是障碍物的四条边的坐标*/
	int x1, x2, y1, y2;
	x1 = *p;
	y1 = *(++p);
	x2 = *(p = p + 3);
	y2 = *(++p);

	/*如果圆在障碍物外半径r以内，就认为发生了碰撞*/
	if (circle_x >= x1 - r&&circle_x <= x2 + r)
		if (circle_y >= y1 - r&&circle_y <= y2 + r)
			return 1;
	return 0;
}

/*检测一个圆是否与障碍物发生碰撞*/
int wall_check(int circle_x,int circle_y,int r)
{
	int(*p_poly)[11][2], *xy,i;//p_poly指向多边形

	/*每个这样的过程必须加 i 来计数，以后在使用指针法时都注意*/
	for (p_poly = map+1,i=1; ***p_poly != 0&&i<=20; p_poly++,i++)//检测有没有与障碍碰撞，***p_poly是多边形边数
	{
		xy = *(*p_poly + 1);
		//xy指向当前二维数组的第二个一维数组的第一个元素，即当前多边形的第一个顶点的横坐标
		if (_duang(xy, circle_x, circle_y, r) == 1)
		{

			return 1;
		}


	}
	return 0;
}
