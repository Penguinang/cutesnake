#include"头文件.h"
#include"宏定义.h"
#include"结构体.h"
#include"所有函数声明.h"
#include"全局变量声明（写在其他次要文件）.h"

/*失败：
		*/
int end()
{

	if (gameRes == -1)
		_playmusic("end");
	paint();

	LOGFONT default;
	gettextstyle(&default);
	RECT textr;
	char string[20];

	setfillcolor(WHITE);
	solidroundrect(370, 110, 830, 380, 10, 10);

	settextstyle(40, 20, _T("黑体"));
	settextcolor(BLACK);
	sprintf_s(string, 20, "%d", LENGTH);
	textr = { 370,200,830,250 };
	drawtext(string, &textr, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	sprintf_s(string, 20, "%d", level);
	textr = { 370,310,830,360 };
	drawtext(string, &textr, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setfillcolor(RGB(255, 87, 87));
	solidroundrect(440, 55, 755, 125, 7, 7);
	FlushBatchDraw();

	settextstyle(&default);
	setrecord();
	head->next = 0; 
	tail = head;
	score = 0;
	level = 1;
	return (end_select());
}

/*建立排行信息*/
int setrecord(){    
	FILE*fp;
	if (fopen_s(&fp,"dat/paihang.dat", "r+") != 0)
	{
		outtextxy(600, 300, "打开文件失败");
		_getch();
		exit(0);
	};

	PAIHANG pai[10] = { 0 };
	PAIHANG*p = pai;
	char ch,c,*chp;
	int i;
	for (i = 1; !feof(fp) && i <= 10; i++, p++)
	{
		fscanf_s(fp, "%d");//跳过序号和句号
		fgetc(fp);//跳过 *
		fscanf_s(fp, "%d", &p->mode);
		fgetc(fp);//跳过句号
		for (chp=p->name;(ch = fgetc(fp)) != '$'&& (!feof(fp));chp++)
		{
			*chp = ch;
		}
		fscanf_s(fp, "%d", &p->score);
		fgetc(fp);
		fscanf_s(fp, "%d", &p->level);
		fgetc(fp);
		fscanf_s(fp, "%d", &p->length);
		fgetc(fp);//跳过换行
	}

	fclose(fp);//关闭文件，用写的方式重新打开文件,以覆盖掉以前的记录

	if (fopen_s(&fp, "dat/paihang.dat", "w") != 0)
	{
		outtextxy(600, 300, "打开文件失败");
		_getch();
		exit(0);
	};

	int signal=1;
	char name[20];

	/*比较旧记录和新纪录，将大的输出，直到输出十个：
				signal 记录新纪录是否已经输出过了，1代表没有*/
	for (i = 1, p = pai; i <= 10&&!feof(fp)&&p->score!=0; i++, p++)
	{
		if (score >= p->score&&signal)
		{
			InputBox(name, 20, "请输入名字");
			fprintf(fp, "%d*%d.%s$%d@%d#%d\n", i ,mode, name, score, level, LENGTH);
			signal = 0;
			p--;
		}
		else fprintf(fp, "%d*%d.%s$%d@%d#%d\n", i ,p->mode, p->name, p->score, p->level, p->length);
	}

	/*如果新纪录没有输出，并且输出记录总数不满十个*/
	if(i<=10&&signal)
	{
		InputBox(name, 20, "请输入名字");
		fprintf(fp, "%d*%d.%s$%d@%d#%d\n", i ,mode, name, score, level, LENGTH);
		signal = 0;
	}
	fclose(fp);
	return 1;
}

/*加载排行榜文件*/
int loadpaihang()
{
	FILE*fp;
	if (fopen_s(&fp, "dat/paihang.dat", "r+") != 0)
	{
		outtextxy(600, 300, "打开文件失败");
		_getch();
		exit(0);
	};

	PAIHANG pai[10] = { 0 }, *p = pai;
	char ch, *chp;

	for (; !feof(fp); p++)
	{
		fgetc(fp);
		fgetc(fp);//跳过序号和句号
		for (chp = p->name; (ch = fgetc(fp)) != '$'; chp++)
		{
			*chp = ch;
		}
		fscanf_s(fp, "%d", &p->score);
		fgetc(fp);
		fscanf_s(fp, "%d", &p->level);
		fgetc(fp);
		fscanf_s(fp, "%d", &p->length);
		fgetc(fp);//跳过换行
	}
	return 1;
}

/*游戏失败后的选择*/
int end_select()
{

	IMAGE img1,img2;
	loadimage(&img1, "img/游戏结束.jpg");
	putimage(537, 75,&img1);
	loadimage(&img2, "img/长度.jpg");
	putimage(573, 156,&img2 );
	loadimage(&img2, "img/关卡.jpg");
	putimage(573, 263, &img2);

	LOGFONT default;

	gettextstyle(&default);


	settextstyle(26, 0, "默认");
	setfillcolor(RGB(105, 195, 108));
	solidcircle(600, 450, 40);
	settextcolor(RGB(105, 195, 108));
	outtextxy(574,507,"返回");
	setfillcolor(RGB(255, 87, 87));
	solidcircle(395, 450, 40);
	settextcolor(RGB(255,87,87));
	outtextxy(370, 507, "炫耀");
	setfillcolor(RGB(243, 209, 75));
	solidcircle(805, 450, 40);
	settextcolor(RGB(243,209,75));
	outtextxy(778,507,"重来");

	settextstyle(&default);

	IMAGE icon;
	loadimage(&icon, "img/重来.jpg");
	putimage(782, 433, &icon);
	loadimage(&icon,"img/炫耀.jpg");
	putimage(376, 432, &icon);
	loadimage(&icon, "img/返回.jpg");
	putimage(577, 428, &icon);
	FlushBatchDraw();

	/*设置点击事件具体信息*/
	MOUSECLICK events[3] =
	{ { 355,410,435,490, 1 },/*炫耀*/
	{ 560,410,640,490, 2 },/*返回*/
	{ 765,410,845,490,3 },/*重来*/
	};

	IMAGE savemessage;
	loadimage(&savemessage, "img/已保存.jpg");
	while (true)
	{

		/*执行点击事件，对结果进行分析*/
		switch (_get_mouse_msg(events, 3))
		{

		case 1: saveimage("分享.bmp", 0); putimage(535, 355, &savemessage); FlushBatchDraw(); break;
		case 2:return 0; break;
		case 3:if (mode == 1)
				load_map(1);
			set_speed(degree);
			initdata();
			return 1; break;
		}

	}

}