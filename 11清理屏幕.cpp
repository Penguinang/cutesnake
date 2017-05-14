#include"头文件.h"
#include"宏定义.h"
#include"结构体.h"
#include"所有函数声明.h"
#include"全局变量声明（写在其他次要文件）.h"


int clear()
{
	
	SNAKE* p1;

	/*画笔和边框颜色设置为背景色，以便擦掉屏幕上的各种图形*/


	setfillcolor(BKCOLOR);
	setlinecolor(BKCOLOR);

	/*擦掉蛇头*/
	fillcircle(head->x, head->y, R);

	/*擦掉两个眼睛*/
	fillcircle(head->x + R*sin(direction*DEGREE), head->y + 0.7*R*cos(direction*DEGREE), 2);
	fillcircle(head->x - R*sin(direction*DEGREE), head->y - 0.7*R*cos(direction*DEGREE), 2);

	/*擦掉蛇身*/
	p1 = head->next;
	for (; p1 != 0; p1 = p1->next) {
		fillcircle(p1->x, p1->y, R);
	}

	/*擦掉各种食物*/
	paint_food(*fruit, FRUITR, BKCOLOR);//画水果
	paint_food(*bomb, BOMBR, BKCOLOR);//画炸弹
	paint_food(*herb, HERBR, BKCOLOR);//画智慧草
	paint_food(*poison,POISONR, BKCOLOR);//画毒草

	/*擦掉信息栏*/
	setbkcolor(0xecb923);
	clearrectangle(820, 100, 1200, 250);
	clearrectangle(820, 400, 1000, 450);
	clearrectangle(800, 0, 820, 600);//还原蛇跑过之后右墙上的缺口
	
	return 1;
}