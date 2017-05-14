#include"头文件.h"
#include"宏定义.h"
#include"结构体.h"
#include"所有函数声明.h"
#include"全局变量声明（写在其他次要文件）.h"

/*开始选项：
		*/
int start()
{

		/*从屏幕右边将开始菜单选项卡拉入*/
		IMAGE menu;
		loadimage(&menu, "img/1开始.jpg");
		_change_picture(&menu/*图片指针*/, 1200, 0, 0, 0/*分别是开始的坐标，与结束时的坐标*/,180/*图片移动的方向，一个角度值*/);
		putimage(0,0,&menu);
		FlushBatchDraw();


		/*设置点击事件具体信息*/
		MOUSECLICK events[7] =
		{	{ 225,40,474,300 , 1 },/*战役模式*/
			{ 696,40,946,300 , 2 },/*生存模式*/
			{ 313,337,391,414 ,3 },/*规则*/
			{ 562,337,639,414 ,4 },/*排行榜*/
			{ 776,337,853,414,5 },/*设置*/
			{ 449,466,529,542,6 },/*载入存档*/
			{ 674,465,752,542 ,7 }/*退出*/
		};


		while (true)
		{

			/*执行点击事件，对结果进行分析*/
			switch (_get_mouse_msg(events,7))
			{
			
			case 1:mode = 1; level = 1; return 1; break;
			case 2:mode = 2; return 1; break;
			case 3:rule(); break;
			case 4: paihangbang();break;
			case 5: shezhi();break;
			case 6:if (zairucundang())	return 1; break;
			case 7:exit(0);
		}
			putimage( 0, 0, &menu);
			FlushBatchDraw();

		}
}



/*图片移动动画：
			给定初始坐标，结束坐标，运动方向*/

int _change_picture(IMAGE* img/*图片指针*/, int x_start, int y_start, int x_end,
	int y_end/*分别是开始的坐标，与结束时的坐标*/, int dir/*图片移动的方向，一个角度值*/)
{
	int x, y, dx = round(cos(dir*DEGREE) * 10), dy = round(sin(dir*DEGREE) * 10);
	for (x = x_start, y = y_start; abs(x - x_start)<=abs(x_end - x_start) && abs(y - y_start)<=abs(y_end - y_start);
		x += dx, y -= dy)
	{
		putimage(x, y, img);
		FlushBatchDraw();
		Sleep(10);
	}
	
	return 1;
}


/*设置点击事件的效果：
			给定一个结构体数组，每一个结构体存放一个事件；给定一个结构体数组长度*/

int _get_mouse_msg(MOUSECLICK* eventarray/*一个结构体数组，每个数组元素存放事件具体的参数，即点击区域的坐标*/,int length/*数组长度*/)
{

	MOUSEMSG mouse;//p是用来计量数组的游标，
	MOUSECLICK*p; //mouse用来存储事件发生时的信息
	int i;
	while (true)
	{
		mouse = GetMouseMsg();//得到当前鼠标的信息
		if (mouse.uMsg != WM_LBUTTONDOWN)//没有点击的话就跳过，
			continue;
		for (p = eventarray,i=1; i <= length; i++, p++)//有就依次检索，找到符合的区域后将值返回
		{
			if (mouse.x >= p->x1&&mouse.x <= p->x2)
				if (mouse.y >= p->y1&&mouse.y <= p->y2)
					return p->value;
		}
	}

	return 1;
}

int shezhi()//修改游戏设置
{
	/*显示设置页面*/
	IMAGE setting;
	loadimage(&setting, "img/2设置.jpg");
	IMAGE select;
	loadimage(&select,"img/10选中.jpg");
	
	/*设置点击事件具体信息*/
	MOUSECLICK events[3] =
	{	{ 1031,74,1069,112, 1 },//关闭
		{ 232,288,323,382, 2 },//音乐
		{ 677,288,770,382,3 }//音效
	};

	int OK=0;
	/*执行点击事件，对结果进行分析*/
	while (!OK)
	{
		putimage(99, 59, &setting);
		if (music == 1)
			putimage(232, 288, &select);
		if (sound == 1)
			putimage(677,288, &select);
		FlushBatchDraw();
		switch (_get_mouse_msg(events, 3))
		{

		case 1: OK = 1; break;
		case 2:music = 1 - music;
			if (music == 0)
				mciSendString(_T("pause BGM"), 0, 0, 0);
			else
				mciSendString(_T("resume BGM"), 0, 0, 0); break;
		case 3: sound = 1 - sound; break;

		}

	}

	return 1;
}

int paihangbang()//提取排行榜文件，显示
{
	LOGFONT default;
	gettextstyle(&default);
	settextstyle(0, 0, "方正兰亭超细黑简体");
	/*显示排行榜页面*/
	IMAGE image;
	loadimage(&image, "img/4排行榜战役得分.jpg");
	putimage(0, 0, &image);
	FlushBatchDraw();
	/*读取排行榜信息*/
	FILE*fp;
	if (fopen_s(&fp, "dat/paihang.dat", "r+") != 0)
	{
		outtextxy(600, 300, "打开文件失败");
		_getch();
		exit(0);
	};

	PAIHANG pai[10] = { 0 };
	PAIHANG*p = pai;
	char ch, *chp;
	int c;
	int i;
	for (i=1; !feof(fp)&&i<=10;i++, p++)
	{
		fscanf_s(fp, "%d",&c);//跳过序号和句号, 不写c 无法通过
		fgetc(fp);//跳过 *
		fscanf_s(fp, "%d", &p->mode);
		fgetc(fp);//跳过句号
		for (chp = p->name; (ch = fgetc(fp)) != '$' && (!feof(fp)); chp++)
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
	char string[50];
	RECT textr_1 = { 348,159,637,179 }, textr_2 = { 714, 159, 954, 179 };

	settextcolor(RGB(135,135,135));
	/*显示排行榜*/
	for (i = 1,p=pai; i <= 10 && p->score != 0; i++,p++)
	{

		sprintf_s(string, 50, "%s",p->name);
		drawtext(string, &textr_1, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		//outtextxy(210, 170+35*(i-1),string);
		//sprintf_s(string, 50, "%s", p->mode==1?"战役模式":"生存模式");
		//outtextxy(450, 170 + 35 * (i - 1), string);
		sprintf_s(string, 50, "%d", p->score);
		drawtext(string,&textr_2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//outtextxy(630, 170 + 35 * (i - 1), string);
		//sprintf_s(string, 50, mode==1?"第%d关":"地图%d", p->level);
		//outtextxy(810, 170 + 35 * (i - 1), string);
		//sprintf_s(string, 50, "%d节", p->length);
		//outtextxy(960, 170 + 35 * (i - 1), string);
		textr_1.bottom += 43;
		textr_1.top += 43;
		textr_2.top += 43;
		textr_2.bottom += 43;
	}
	FlushBatchDraw();

	/*设置点击事件具体信息*/
	MOUSECLICK events[1] =
	{ { 1092,494,1161,564, 1 }//关闭
	};

	/*执行点击事件，对结果进行分析*/
	switch (_get_mouse_msg(events, 1))
	{

	case 1:return 1;
	}

	settextstyle(&default);
}

int rule()//提取规则图片，显示
{
	/*显示规则页面*/
	IMAGE image_1,image_2,image_3;
	loadimage(&image_1, "img/规则-1.jpg");
	loadimage(&image_2, "img/规则-2.jpg");
	loadimage(&image_3, "img/规则-3.jpg");
	putimage(0, 0, &image_1);
	FlushBatchDraw();

	/*设置点击事件具体信息*/
	MOUSECLICK events[4] =
	{
		{ 487,534,515,563 ,1},
		{ 587,534,615,563 ,2},
		{ 687,534,715,563 ,3},
		{ 1092,494,1161,564, 4 }//关闭
	};

	/*执行点击事件，对结果进行分析*/
	while(true)
	{
		switch (_get_mouse_msg(events, 4))
		{
		case 1:putimage(0, 0, &image_1); break;
		case 2:putimage(0, 0, &image_2); break;
		case 3:putimage(0, 0, &image_3); break;
		case 4:return 1;
		}
		FlushBatchDraw();
	};

}

/*返回值为1，代表选中一个存档进入，返回0代表没有选中，返回上一层*/
int zairucundang()//载入存档
{
	/*显示存档页面*/
	IMAGE image;
	loadimage(&image, "img/5载入存档.jpg");
	putimage(0, 0, &image);
	FlushBatchDraw();
	
	MEMORY memo[8] = { 0 },*mp;
	int num=_read_memory(memo);//将读取到的左右内容存在memo[5]中，读取到的存档个数在num中
	
	/*设置点击事件具体信息*/
	MOUSECLICK events[11] =
	{ { 61,124,223,286 ,1},//1号存档
	{ 306,124,471,286 ,2},//2号存档
	{ 553,124,720,286 ,3},//3号存档
	{ 798,124,960,286 ,4},//4号存档
	{ 798,330,960,492 ,5},//5号存档
	{ 553,330,720,492, 6 },//6号存档
	{ 306,330,471,492 ,7},//7号存档
	{ 61,330,223,492 ,8},//8号存档
	{1143,24,1182,61,9},//关闭
	{ 986,476,1055,545 ,10},//删除
	{ 1084,476,1153,545 ,11}//开始
	};

	_display_text(memo,num,events);

	IMAGE select;
	loadimage(&select, "img/10选中.jpg",32,30);
	int select_memory=0,OK=0;
	/*执行点击事件，对结果进行分析*/
	while (!OK)
	{
		switch (_get_mouse_msg(events, 11))
		{

		case 1:select_memory = 1; break;//存档一
		case 2:select_memory = 2; break;//存档二
		case 3:select_memory = 3; break;//存档三
		case 4:select_memory = 4; break;//存档四
		case 5:select_memory = 5; break;//存档五
		case 6:select_memory = 6; break;//存档六
		case 7:select_memory = 7; break;//存档七
		case 8:select_memory = 8; break;//存档八
		case 9:return 0;//返回
		case 10:if (_delete_memory(memo, select_memory,num))
					num--; break;
		case 11:if(select_memory>0&&select_memory<=num)
					OK = 1;
		}
		putimage(0, 0, &image);
		putimage(events[select_memory-1].x1-10, events[select_memory-1].y1-10, &select);
		FlushBatchDraw();
		_display_text(memo, num,events);
	}

	/*把存档信息加载到全局变量中*/
	_load_memory(&memo[select_memory-1]);

	gameRes = 2;
	return 1;
}

/*读取存档*/
int _read_memory(MEMORY* memo)
{


	FILE *fp;
	/*打开文件*/
	if (fopen_s(&fp, "dat/memory.dat", "r") != 0)//文件不存在时
	{
		settextcolor(BLACK);
		outtextxy(600, 300, "存档为空");
		FlushBatchDraw();
		return 0;
	};

	MEMORY*mp;
	int num,i;//记录存档个数
	fscanf_s(fp, "%d", &num);
	char ch,*chp;
	int(*arrayp)[2];
	int n;

	for (i = 1,mp=memo; i <= num; i++,mp++)
	{
		fgetc(fp);//换行符
		fscanf_s(fp,"+%d序号/");
		/*名字*/
		for (chp = mp->name; (ch = fgetc(fp)) >0; chp++)
		{
			*chp = ch;
		}
		fgetc(fp);
		/*蛇的信息*/
		fscanf_s(fp, "字/*%d模式$%d得分@%d关卡/地图>%d难度\n", &mp->mode, &mp->score, &mp->level, &mp->degree);
		fscanf_s(fp, "&snake:%d方向", &mp->direction);
		for (arrayp = mp->snake,n=1;fgetc(fp)!='\n'&&n<=100; arrayp++,n++)
		{
			fscanf_s(fp, "%d,%d", *arrayp, *arrayp + 1);
		}
		/*食物*/
		fscanf_s(fp, "&fruit:");//水果
		for (arrayp = mp->fruit,n=1; fgetc(fp) != '\n'&&n<=10; arrayp++,n++)
		{
			fscanf_s(fp, "%d,%d", *arrayp, *arrayp + 1);
		}

		fscanf_s(fp, "&bomb:");//炸弹
		for (arrayp = mp->bomb, n = 1; fgetc(fp) != '\n'&&n <= 10; arrayp++, n++)
		{
			fscanf_s(fp, "%d,%d", *arrayp, *arrayp + 1);
		}


		fscanf_s(fp, "&poison:");//毒草
		for (arrayp = mp->poison, n = 1; fgetc(fp) != '\n'&&n <= 10; arrayp++, n++)
		{
			fscanf_s(fp, "%d,%d", *arrayp, *arrayp + 1);
		}

		fscanf_s(fp, "&herb:");//智慧草
		for (arrayp = mp->fruit, n = 1; fgetc(fp) != '\n'&&n <= 10; arrayp++, n++)
		{
			fscanf_s(fp, "%d,%d", *arrayp, *arrayp + 1);
		}

		/*读取地图信息*/
		fscanf_s(fp, "-%fcommonT-%ldPoisonTimer-%ldHerbTimer-%dai-", 
			&mp->commonT, &mp->PoisonTimer, &mp->HerbTimer, &mp->ai);


	}
	fclose(fp);
	return num;//成功读取7则返回存档个数，否则返回0
}

/*显示与存档对应的文字信息*/
int _display_text(MEMORY* memo, int num, MOUSECLICK*events)
{
	MEMORY*mp = memo;
	RECT textr;
	LOGFONT default;
	gettextstyle(&default);

	settextstyle(20, 0, "方正兰亭超细黑简体",0,0,1000,false,false,false);
	int i=1;
	char string[50];
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	for (i = 1, mp = memo; i <= num; i++, mp++)
	{
		sprintf_s(string,50,"%s\n%s模式\n关卡%d\n%d分",mp->name,mp->mode==1?"战役":"生存",mp->level,mp->score);
		textr.left = events[i - 1].x1 + 25;
		textr.top = events[i - 1].y1 + 29;
		textr.right = events[i - 1].x2 - 25;
		textr.bottom = events[i - 1].y2 - 29;
		drawtext(string, &textr,DT_EDITCONTROL);
	}
	FlushBatchDraw();
	settextstyle(&default);
	return 1;
}

/*删除存档*/
int _delete_memory(MEMORY*memo,int select_memory,int num)
{

	MEMORY*mp = memo+select_memory - 1;
	if (mp->score == 0)
		return 0;
	*mp = { 0 };//直接对结构体赋值在C语言中是错误的，在c++中是正确的

	int i;
	for (i = select_memory - 1; i <= 3; i++,mp++)
		*mp = *(mp+1);

	FILE *fp;
	/*打开文件*/
	if (fopen_s(&fp, "dat/memory.dat", "w") != 0)//文件不存在时，会采用第二种方式，否则采用第一种方式
	{
		settextcolor(BLACK);
		outtextxy(600, 300, "打开文件失败");
		FlushBatchDraw();
		return 0;
	};

	/*改写存档个数*/
	if(num!=1)//num 为1，那么删除后存档数为0，即什么都没有，就不用写存档个数
		fprintf(fp, "%d", num-1);
	int(*arrayp)[2],n;
	/*输出*/
	for(mp=memo,i=1;i<=5&&mp->score!=0;mp++)
	{
		fprintf(fp, "\n+%d序号/%s名字/*%d模式$%d得分@%d关卡/地图>%d难度\n", i, mp->name, mp->mode, mp->score, mp->level, mp->degree);

		/*输出蛇的信息*/
		fprintf(fp, "&snake:%d方向", mp->direction);
		for (arrayp = mp->snake, n = 1; **arrayp!=0&&n <= 100; arrayp++, n++)
		{
			fprintf_s(fp, ",%d,%d", **arrayp,*(*arrayp + 1));
		}

		/*输出食物的信息*/
		fprintf(fp, "\n&fruit:");
		for (i = 1,arrayp=mp->fruit; **arrayp != 0 && i <= 10; arrayp++, i++)
		{
			fprintf(fp, ",%d,%d", **arrayp, *(*arrayp + 1));
		}

		fprintf(fp, "\n&bomb:");
		for (i = 1,arrayp=mp->bomb; **arrayp != 0 && i <= 10; arrayp++, i++)
		{
			fprintf(fp, ",%d,%d", **arrayp, *(*arrayp + 1));
		}

		fprintf(fp, "\n&poison:");
		for (i = 1, arrayp = mp->poison; **arrayp != 0 && i <= 10; arrayp++, i++)
		{
			fprintf(fp, ",%d,%d", **arrayp, *(*arrayp + 1));
		}

		fprintf(fp, "\n&herb:");
		for (i = 1, arrayp = mp->herb; **arrayp != 0 && i <= 10; arrayp++, i++)
		{
			fprintf(fp, ",%d,%d", **arrayp, *(*arrayp + 1));
		}

		fprintf(fp, "\n-%fcommonT-%ldPoisonTimer-%ldHerbTimer-%dai-",
			mp->commonT, mp->PoisonTimer, mp->HerbTimer, mp->ai);
	}
	
	
	fclose(fp);

	return 1;
}

/*把存档信息加载到全局变量中*/
int _load_memory(MEMORY *memo)
{
	mode = memo->mode;
	score = memo->score;
	level = memo->level;
	degree = memo->degree;
	direction = memo->direction;
	/*加载蛇*/
	snake_head = {memo->snake[0][0],memo->snake[0][1],1,0,0 };
	SNAKE*ps;
	int i,*p1=*(memo->snake+1),*p2 ;
	for (i=2;*p1!=0&&i<=200;i++)
	{
		ps = (SNAKE*)malloc(sizeof(SNAKE));
		ps->preview = tail;
		tail->next = ps;
		tail = ps;
		ps->x = *p1++;
		ps->y = *p1++;
		ps->order = i;
	}
	tail->next = 0;
	/*加载食物*/
	p1 = *memo->fruit;
	p2 = *fruit;
	for (i = 1; *p1 != 0 && i <= 20; i++)
	{
		*p2++ = *p1++;
	}
	p1 = *memo->bomb;
	p2 = *bomb;
	for (i = 1; *p1 != 0 && i <= 20; i++)
	{
		*p2++ = *p1++;
	}
	p1 = *memo->poison;
	p2 = *poison;
	for (i = 1; *p1 != 0 && i <= 20; i++)
	{
		*p2++ = *p1++;
	}
	p1 = *memo->herb;
	p2 = *herb;
	for (i = 1; *p1 != 0 && i <= 20; i++)
	{
		*p2++ = *p1++;
	}

	/*加载其他信息*/
	commonT = memo->commonT;
	PoisonTimer = memo->PoisonTimer;
	HerbTimer = memo->HerbTimer;
	ai = memo->ai;

	switch (memo->degree)
	{
	case 1: fruitNum = 5; bombNum = 1; poisonNum = 3; degree = 1; break;
	case 2: fruitNum = 6; bombNum = 5; poisonNum = 6; degree = 2; break;
	case 3: fruitNum = 10; bombNum = 10; poisonNum = 10; degree = 3; break;
	}
	load_map(memo->level);//加载地图

	set_speed(memo->degree);//设置难度


	return 1;
}