#include"头文件.h"
#include"宏定义.h"
#include"结构体.h"
#include"所有函数声明.h"
#include"全局变量声明（写在其他次要文件）.h"

/*存档：
		*/
int pause()
{

	setfillcolor(RGB(255, 87, 88));
	solidroundrect(247, 117, 902, 200, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(247, 450 , 902, 499, 10, 10);

	IMAGE img,tittle;
	loadimage(&img, "img/暂停图片.jpg");
	putimage(247, 147, &img);
	loadimage(&tittle,"img/暂停标题.jpg");
	putimage(293, 120, &tittle);
	FlushBatchDraw();

	
	/*设置点击事件具体信息*/
	MOUSECLICK events[4] =
	{ { 415,236,777,264,1 },//输入
	{ 818,214,870,264,2 },//确定
	{ 415,375,458,421 ,3 },//继续
	{ 730,375,777,421,4 }//退出
	};

	int conti=0;//continue 的简写，代表“继续”按键的状态
	int signal=0;//输入状态的标志，0代表未输入，1代表已输入
	char name[20] = {0};//存档名称
	while (!conti)
	{
		switch (_get_mouse_msg(events, 4))
		{
		case 1:_get_name(name,&signal); break;
		case 2:_set_memory(name, &signal);  break;
		case 3:conti=1; break;
		case 4:gameRes = 0; exit(0);
		}
		FlushBatchDraw();
	}
	

	/*恢复图形*/
	setbkcolor(BKCOLOR);
	cleardevice();

	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);
	setfillcolor(0xecb923);
	solidrectangle(800, 0, 1200, 600);

	return 1;
}

/*得到输入的字符串*/
int _get_name(char*name,int *signal)
{
	/*把输入框清空*/
	setfillcolor(WHITE);
	solidrectangle(415, 236, 777, 252);
	solidrectangle(486, 265,672,342); 
	FlushBatchDraw();

	char *chp=name,ch;
	int i;
	for (i = 1; i <= 20 && (ch = _getch()) != 13; i++,chp++)
	{
		*chp = ch;
		settextcolor(BLACK);
		outtextxy(415+textwidth('我')*(i-1), 236, ch);
		FlushBatchDraw();
	}
	*signal = 1;

	return 1;

}

/*建立存档*/
int _set_memory(char*name,int *signal)
{
	if (*signal == 0)
	{
		settextcolor(BLACK);
		outtextxy(600, 100, "请输入");
		FlushBatchDraw();
		return 0;
	}

	FILE *fp;
	/*打开文件*/
	if (fopen_s(&fp, "dat/memory.dat", "r+") != 0)//文件不存在时，会采用第二种方式，否则采用第一种方式
	{
		if (fopen_s(&fp, "dat/memory.dat", "w") != 0)
		{
			settextcolor(BLACK);
			outtextxy(600, 300, "打开文件失败");
			FlushBatchDraw();
			_getch();
			exit(0);
		}
	};

	/*判断存档是否已经满了*/
	int memory_number;

	if (fscanf_s(fp, "%d", &memory_number) == -1)//fscanf()返回值是成功读取参数的个数，没有成功读取返回-1
		memory_number = 0;
	if (memory_number >= 8)
	{
		settextcolor(BLACK);
		outtextxy(600, 100, "存档已满");
		FlushBatchDraw();
		return 1;
	}

	/*将指针移动到文件开头*/
	fseek(fp, 0, 0);
	/*改写存档个数*/
	fprintf(fp, "%d", ++memory_number);

	/*将指针移动到文件末尾*/
	fseek(fp, 0, 2);
	/*输出*/
	fprintf(fp, "\n+%d序号/%s名字/*%d模式$%d得分@%d关卡/地图>%d难度\n", memory_number,name,mode, score,level, degree);

	/*输出蛇的信息*/
	fprintf(fp, "&snake:%d方向", direction);
	SNAKE*ps = head;
	for (; ps != 0;ps=ps->next)
	{
		fprintf(fp, ",%d,%d", ps->x, ps->y);
	}

	/*输出食物的信息*/
	fprintf(fp, "\n&fruit:");
	int (*p)[2]=fruit,i;
	for (i=1; **p != 0&&i<=10; p ++,i++)
	{
		fprintf(fp, ",%d,%d", **p, *(*p+1));
	}

	fprintf(fp, "\n&bomb:");
	p=bomb;
	for (i = 1; **p != 0 && i <= 10; p++, i++)
	{
		fprintf(fp, ",%d,%d", **p, *(*p + 1));
	}

	fprintf(fp, "\n&poison:");
	p = poison;
	for (i = 1; **p != 0 && i <= 10; p++, i++)
	{
		fprintf(fp, ",%d,%d", **p, *(*p + 1));
	}

	fprintf(fp, "\n&herb:");
	p = herb;
	for (i = 1; **p != 0 && i <= 10; p++, i++)
	{
		fprintf(fp, ",%d,%d", **p, *(*p + 1));
	}

	fprintf(fp, "\n-%fcommonT-%ldPoisonTimer-%ldHerbTimer-%dai-", commonT, PoisonTimer, HerbTimer, ai);

	fclose(fp);
	IMAGE success;

	loadimage(&success, "img/存储成功.jpg");
	putimage(486, 265, &success);
	signal = 0;
	return 1;
}