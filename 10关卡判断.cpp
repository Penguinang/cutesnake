#include"头文件.h"
#include"宏定义.h"
#include"结构体.h"
#include"所有函数声明.h"
#include"全局变量声明（写在其他次要文件）.h"

/*关卡判断*/
int _level()
{
	if (LENGTH >= 10) 
	{

		
		if (++level >= 10)
		{
			_playmusic("win");
			gameRes = 1;
			IMAGE img;
			loadimage(&img, "img/胜利.jpg");
			setfillcolor(WHITE);
			solidrectangle(0, 200, 1200, 600);
			_change_picture(&img/*图片指针*/, -30, 200, 0,
				200/*分别是开始的坐标，与结束时的坐标*/, 0/*图片移动的方向，一个角度值*/);
			gameRes = 1;
			Sleep(1000);
			_getch();

			return 1;
		}
		else
		{
			_playmusic("pass");
			load_map(level);
			IMAGE img;
			loadimage(&img, "img/8进入下一关.jpg");
			setfillcolor(WHITE);
			solidrectangle(0, 200, 1200, 600);
			_change_picture(&img/*图片指针*/, 0, 200, 300,
				200/*分别是开始的坐标，与结束时的坐标*/, 0/*图片移动的方向，一个角度值*/);
			Sleep(1000);
			tail = head;
			head->next = 0;
			initdata();
			initgame();
			
			/*若有敲回车就继续游戏，否则等待两秒继续游戏*/
			int wait=0;
			while (wait<=2000)
			{
				Sleep(300);
				wait += 300;
				if (_kbhit())
					if (_getch() == 13)
						break;
			}
		}
	}
	return 1;
}