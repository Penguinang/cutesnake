#include"头文件.h"
#include"宏定义.h"
#include"结构体.h"
#include"所有函数声明.h"
#include"全局变量声明（写在其他次要文件）.h"

/*绘制屏幕：
		*/
int paint()
{

	SNAKE* p1;
	

	/*恢复画笔颜色*/
	setlinecolor(BLACK);

	/*画参考线*/
	int i;
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);
	setlinecolor(LINE_COLOR);
	for (i = 0; i <= 800; i += 20)
		line(i, 0, i, 600);
	for (i = 0; i <= 600; i += 20)
		line(0, i, 800, i);

	/*画外框*/
	
	if (***map == 0)//翻墙不可用时
	{

		setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 5);
		setlinecolor(BLACK);
		rectangle(0, 0, 800, 600);
	}


	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);
	setlinecolor(LINE_COLOR);
	/*画障碍物*/
	int(*p)[11][2], *xy;//p指向点（一维数组），xy指向具体坐标（整型变量）
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);
	setfillcolor(RED);
	for (p = map+1, xy = *(*p + 1),i=1; ***p != 0&&i<=20;i++)
	{
		fillpoly(***p, xy);
		p++;
		xy = *(*p + 1);
	}


	/*画蛇头*/
	setfillcolor(COLOR_1);
	setlinecolor(RGB(172, 177, 189));
	fillcircle(head->x, head->y, R);
	setfillcolor(0x000000);

	/*画两个眼睛*/
	fillcircle(head->x + R*sin(direction*DEGREE), head->y + 0.7*R*cos(direction*DEGREE), 2);
	fillcircle(head->x - R*sin(direction*DEGREE), head->y - 0.7*R*cos(direction*DEGREE), 2);

	/*画蛇身*/
	setfillcolor(COLOR_2);
	p1 = head->next;
	for (; p1 != 0; p1 = p1->next) {
		fillcircle(p1->x, p1->y, R);
		if (getfillcolor() == COLOR_2)
			setfillcolor(COLOR_1);
		else setfillcolor(COLOR_2);
	}

	/*画各种食物*/
	paint_food(*fruit,FRUITR, 0x24c097);//画水果
	paint_food(*bomb,FRUITR, 0x000000);//画炸弹
	paint_food(*herb, FRUITR, 0x16e1ea);//画智慧草
	paint_food(*poison,POISONR, HSLtoRGB((poison_color_h+=7)%360,(poison_color_h%4+3)/10.0, (poison_color_h % 4 + 3) / 10.0));//画毒草


	/*画信息栏*/
	char information[40];
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	sprintf_s(information, "分数：%d", score);//分数栏
	outtextxy(820, 100,information); 
	sprintf_s(information, "长度：%d", LENGTH);//长度栏
	outtextxy(820, 150, information);
	sprintf_s(information, "关卡：%d", level);//关卡栏
	outtextxy(820, 200, information);

	/*画对话框*/
	char conversation[50];
	sprintf_s(conversation, "毒草还有%d秒到达", 15-PoisonTimer/1000>0? 15 - PoisonTimer / 1000:0);
	outtextxy(820, 400, conversation);
	FlushBatchDraw();
	return 1;
}

/*画食物:
		读取所给指针后面的数据，两个一组画一个指定大小和颜色的圆，直到读到0为止*/
int paint_food(int *food,int food_r,int color)
{
	int *p=food,i=1;
	setfillcolor(color);
	while (*p != 0&&i<=10)
	{
		solidcircle(*p, *(p+1), food_r);
		p+=2;
		i++;
	}
	
	return 1;
}

