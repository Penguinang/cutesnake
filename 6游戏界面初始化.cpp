#include"头文件.h"
#include"宏定义.h"
#include"结构体.h"
#include"所有函数声明.h"
#include"全局变量声明（写在其他次要文件）.h"


/*游戏界面初始化*/
int initgame()
{
	setbkcolor(BKCOLOR);
	cleardevice();
	
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);
	setfillcolor(0xecb923);
	solidrectangle(800, 0, 1200, 600);

	
	return 1;
}