//////////////////////////////
////   cutesnake
//////////////////////////////

#include"头文件.h"
#include"宏定义.h"
#include"结构体.h"
#include"全局变量定义（写在主函数文件）.h"
#include"所有函数声明.h"
#pragma comment(lib, "Winmm.lib")



void main()
{

	initwindow();//图形界面初始化
	do
	{

		if (music)
			_playmusic("BGM");//开启BGM的播放
		start();//引入游戏
		if (score == 0)//从0开始，代表不是载入存档
			_map_degree();//难度和地图选择 


		do
		{
			initgame();//游戏界面初始化

			while (gameRes == 2)
			{
				if (music)
					_playmusic("BGM");//播放BGM
				paint();//绘制屏幕
				Sleep((int)realT);//屏幕视觉暂时保存 T 毫秒
				_death_judge();//检查有没有发生撞墙之类的导致死亡的事情
				if (mode == 1)
					_level();
				addspeed();
				clear();
				_food_judge();//检查有没有吃到什么东西
				move();//对蛇进行移动
			}
		} while (end());
			
	} while (1);
}