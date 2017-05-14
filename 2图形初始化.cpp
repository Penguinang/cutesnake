#include"头文件.h"
#include"宏定义.h"
#include"结构体.h"
#include"所有函数声明.h"
#include"全局变量声明（写在其他次要文件）.h"

/*图形初始化：
		打开图形模式，设置背景色和窗口大小*/

int initwindow()
{
	SetWindowText(initgraph(WIDTH + 400, HEIGHT), "Penguinang的Mario贪吃蛇");//初始化图形模式//设置窗口和标题
	HWND hwnd = GetHWnd();

	/*裁切窗口*/
	// 获取窗口边框宽高
	int cx = GetSystemMetrics(SM_CXFIXEDFRAME)+4;
	int cy = GetSystemMetrics(SM_CYFIXEDFRAME) + GetSystemMetrics(SM_CYCAPTION)+4;
	HRGN clip = CreateRectRgn(cx, cy, WIDTH + 400+cx+2, HEIGHT+cy+2);
	SetWindowRgn(hwnd, clip, true);

	setbkcolor(WHITE);//设置背景颜色
	cleardevice();

	BeginBatchDraw();
	return 1;
}