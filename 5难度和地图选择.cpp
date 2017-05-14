#include"头文件.h"
#include"宏定义.h"
#include"结构体.h"
#include"所有函数声明.h"
#include"全局变量声明（写在其他次要文件）.h"


/*难度和地图选择：
			*/
int _map_degree()
{
	if (mode == 1)
		mode1();
	else mode2();
	return 1;
}
/*战役模式界面*/
int mode1()
{

	/*出现选择页面*/
	IMAGE menu, select;
	loadimage(&menu, "img/mode1.jpg");
	loadimage(&select, "img/10选中.jpg");
	putimage(0, 0, &menu);
	FlushBatchDraw();

	/*设置点击事件具体信息*/
	MOUSECLICK events[4] =
	{ { 373,241,465,489,1 },//小白模式
	{ 517,241,609,489,2 },//专家模式
	{ 658,241,750,489 ,3 },//大佬模式
	{ 856,420,925,489,4 },//确定
	};

	int select_degree = 0, OK = 0;//选中的难度，和选择完毕
	while (!OK|| select_degree == 0)
	{

		/*执行点击事件，对结果进行分析*/
		switch (_get_mouse_msg(events, 4))
		{
			/*1~3 是难度的选项*/
		case 1:select_degree = 1; fruitNum = 5; bombNum = 1; poisonNum = 3; degree = 1; break;
		case 2:select_degree = 2; fruitNum = 6; bombNum = 5; poisonNum = 6; degree = 2; break;
		case 3:select_degree = 3; fruitNum = 10; bombNum = 10; poisonNum = 10; degree = 3; break;
			/*OK 为1时，循环会结束*/
		case 4:
			if (select_degree != 0)
				OK = 1; 
		}
		putimage(0, 0, &menu);
		if (select_degree != 0)
			putimage(events[select_degree-1].x1,397, &select);//难度选中图标       //这些是具体的坐标值
		//这个算法很烂，不过实在找不到更好的了

		FlushBatchDraw();
	}
	
	load_map(1);//加载地图

	set_speed(select_degree);//设置难度

	initdata();//游戏数据初始化

	return 1;
}

/*生存模式界面*/
int mode2()
{

	/*出现选择页面*/
	IMAGE menu, select;
	loadimage(&menu, "img/mode2.jpg");
	loadimage(&select, "img/10选中.jpg",32,30);
	putimage(0,0, &menu);
	FlushBatchDraw();

	/*设置点击事件具体信息*/
	MOUSECLICK events[13] =
	{ { 137,174,302,208,1 },//小白模式
	{ 137,249,302,285,2 },//专家模式
	{ 137,325,302,360 ,3 },//大佬模式
	{ 397,118,561,238, 4 },//地图一
	{ 606,118,773,237 ,5 },//地图二
	{ 810,118,977,237,6 },//地图三
	{ 397,272,562,387,7 },//地图四
	{ 602,272,723,387,8 },//地图五
	{ 810,272,977,387,9 },//地图六
	{ 397,423,562,543,10 },//地图七
	{ 602,429,773,543,11 },//地图八
	{ 810,429,977,543,12 },//地图九
	{ 127,489,196,558,13 },//确定
	};

	int select_map = 0, select_degree = 0, OK = 0;//选中的地图，选中的难度，和选择完毕
	while (!OK || select_map == 0 || select_degree == 0)
	{

		/*执行点击事件，对结果进行分析*/
		switch (_get_mouse_msg(events, 13))
		{
			/*1~3 是难度的选项*/
		case 1:select_degree = 1; fruitNum = 5; bombNum = 1; poisonNum = 3; degree = 1; break;
		case 2:select_degree = 2; fruitNum = 6; bombNum = 5; poisonNum = 6; degree = 2; break;
		case 3:select_degree = 3; fruitNum = 10; bombNum = 10; poisonNum = 10; degree = 3; break;
			/*4~9 是地图的选项*/
		case 4:select_map = 1; break;
		case 5:select_map = 2; break;
		case 6:select_map = 3; break;
		case 7:select_map = 4; break;
		case 8:select_map = 5; break;
		case 9:select_map = 6; break;
		case 10:select_map = 7; break;
		case 11:select_map = 8; break;
		case 12:select_map = 9; break;
			/*OK 为1时，循环会结束*/
		case 13:
			if (select_map == 0 || select_degree == 0)
				continue;
			else OK = 1;
		}
		putimage(0, 0, &menu);
		if (select_degree != 0)
			putimage(274, 4+events[select_degree-1].y1, &select);//难度选中图标       //这些是具体的坐标值
		if (select_map != 0)
			putimage(events[select_map+2].x1-33, events[select_map+2].y1, &select);
		//地图选中图标     //这个算法很烂，不过实在找不到更好的了

		FlushBatchDraw();
	}

	level = select_map;

	load_map(select_map);//加载地图

	set_speed(select_degree);//设置难度

	initdata();//游戏数据初始化
	return 1;
}


/*加载地图：
		将文件中的数据写到数组里面*/
int load_map(int select_map)
{

	/*先将上一把的图清了，再加载这一把的图*/
	int(*p)[11][2] = map + 1, i;
	for (i = 1; i <= 20; i++, p++)
		***p = 0;//每个多边形的第一个元素是他的边数，改为0在刷新时不会输出后面的数据

	FILE *fp;

	if(mode==1)//战役模式
	{
		if (fopen_s(&fp, "dat/mode1.dat", "r") != NULL)//不能在字符串中加\，只好把地图文件放在与源文件同级
		{
			outtextxy(600, 300, "无法打开地图");
			settextcolor(BLACK);
			FlushBatchDraw();
			_getch();
			exit(0);
		}
	}
	else {
		if (fopen_s(&fp, "dat/mode2.dat", "r") != NULL)//不能在字符串中加\，只好把地图文件放在与源文件同级
		{
			outtextxy(600, 300, "无法打开地图");
			settextcolor(BLACK);
			FlushBatchDraw();
			_getch();
			exit(0);
		}
	}
	

	while (!feof(fp))
	{
		/*在地图文件中的格式是$1.1@400,290,150@3，4，5，5；$2.1@34，56，23，3，···等等:
				$1.   代表第一个地图
				后面的   1   代表该地图允许翻墙
				两个 @ 里面是蛇的坐标和方向
				后面是每个多边形的坐标值
			逗号是坐标值的分界，分号是多边形的划分,每个多边形后面必须写一个分号，$ 美元符号是地图的划分*/
		if (fgetc(fp) != '$')
			continue;
		if (fgetc(fp) == select_map + 48)
			break;
	}
	fgetc(fp);//把序号后面的句号跳过

	/*读取该地图对翻墙的许可*/
	***map = fgetc(fp) - 48;//把许可存进地图第一个多边形第一个一维数组的第二个元素内
	fgetc(fp);//把后面的 @ 跳过


	int (*poly)[11][2]=map+1;//poly 指向二维数组，因为每一个多边形由一个二维数组内的点组成；
	int *polypointxy=&map[0][1][0];//polypoint 指向一个点，也是一个一维数组，
	int xy=0;//xy暂时存储从文件获取到的数字
	char ch;//ch暂时存储从文件获取到的字符

	/*加载关于蛇的信息:
				蛇的信息放在啊第一个二维数组中第二、三个一维数组*/
	for (; (ch = fgetc(fp)) != '@';)
	{
		if (ch == ',')
		{
			*polypointxy++ = xy;
			xy = 0;
			continue;
		}
		xy = xy * 10 + ch - 48;
	}
	*polypointxy++ = xy;
	xy = 0;


	/*读取地图的信息*/
	polypointxy = &map[1][1][0];
	for (i=0;(ch=fgetc(fp)) != '$';)//再次读到$时代表地图加载完毕
	{
		if (ch == '\n')
			continue;
		if (ch == ',')//读到逗号时将xy暂存的数字赋给 polypointxy ，再清空
		{
			*polypointxy++ = xy;
			i++;//获取一个坐标，加一个
			xy = 0;
			continue;
		}
		if (ch == ';')//读到分号指针指向下一个多边形
		{
			*polypointxy++ = xy;
			i++;//获取一个坐标，加一个
			i = i / 2;//由坐标数转换为边数
			***poly = i;//把多边形边数存在多边形第一个元素里
			i = 0;
			xy = 0;
			polypointxy = **(++poly)+2;//polypoint又指向下一个多边形的第一个点的坐标
			continue;
		}
		xy = xy * 10 + ch - 48;
	}

	return 1;
}

/*设置速度大小*/
int set_speed(int select_degree)
{
	switch (select_degree)
	{
	case 1:T0 = 180; DT = 0.030; break;
	case 2:T0 = 170; DT = 0.050; break;
	case 3:T0 = 150; DT = 0.070; break;
	}

	
	return 1;
}

/*游戏数据初始化*/
int  initdata()
{
	snake_head = { map[0][1][0],map[0][1][1],1,0,0 };
	direction = map[0][2][0];
	//第一种模式第一关或第二种模式都需要把score归零
	if (mode == 2 || level == 1)
		score = 0;
	commonT = T0;

	/*毒草清零*/
	int *p = *poison, i;
	for (i = 1; i <= 20; i++, p++)
		*p = 0;
	for (p = *fruit, i = 1; i <= 20; i++, p++)
		*p = 0;
	for (p = *bomb, i = 1; i <= 20; i++, p++)
		*p = 0;

	for (p = *fruit, i = 1; i <= fruitNum; i++, p += 2)
	{
		_food_create(p, FRUITR);
	}

	for (p = *bomb, i = 1; i <= bombNum; i++, p += 2)
	{
		_food_create(p, BOMBR);
	}

	PoisonTimer = 10000;
	gameRes = 2;
	return 1;
}