#include"ͷ�ļ�.h"
#include"�궨��.h"
#include"�ṹ��.h"
#include"���к�������.h"
#include"ȫ�ֱ���������д��������Ҫ�ļ���.h"

/*��ʼѡ�
		*/
int start()
{

		/*����Ļ�ұ߽���ʼ�˵�ѡ�����*/
		IMAGE menu;
		loadimage(&menu, "img/1��ʼ.jpg");
		_change_picture(&menu/*ͼƬָ��*/, 1200, 0, 0, 0/*�ֱ��ǿ�ʼ�����꣬�����ʱ������*/,180/*ͼƬ�ƶ��ķ���һ���Ƕ�ֵ*/);
		putimage(0,0,&menu);
		FlushBatchDraw();


		/*���õ���¼�������Ϣ*/
		MOUSECLICK events[7] =
		{	{ 225,40,474,300 , 1 },/*ս��ģʽ*/
			{ 696,40,946,300 , 2 },/*����ģʽ*/
			{ 313,337,391,414 ,3 },/*����*/
			{ 562,337,639,414 ,4 },/*���а�*/
			{ 776,337,853,414,5 },/*����*/
			{ 449,466,529,542,6 },/*����浵*/
			{ 674,465,752,542 ,7 }/*�˳�*/
		};


		while (true)
		{

			/*ִ�е���¼����Խ�����з���*/
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



/*ͼƬ�ƶ�������
			������ʼ���꣬�������꣬�˶�����*/

int _change_picture(IMAGE* img/*ͼƬָ��*/, int x_start, int y_start, int x_end,
	int y_end/*�ֱ��ǿ�ʼ�����꣬�����ʱ������*/, int dir/*ͼƬ�ƶ��ķ���һ���Ƕ�ֵ*/)
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


/*���õ���¼���Ч����
			����һ���ṹ�����飬ÿһ���ṹ����һ���¼�������һ���ṹ�����鳤��*/

int _get_mouse_msg(MOUSECLICK* eventarray/*һ���ṹ�����飬ÿ������Ԫ�ش���¼�����Ĳ�������������������*/,int length/*���鳤��*/)
{

	MOUSEMSG mouse;//p����������������α꣬
	MOUSECLICK*p; //mouse�����洢�¼�����ʱ����Ϣ
	int i;
	while (true)
	{
		mouse = GetMouseMsg();//�õ���ǰ������Ϣ
		if (mouse.uMsg != WM_LBUTTONDOWN)//û�е���Ļ���������
			continue;
		for (p = eventarray,i=1; i <= length; i++, p++)//�о����μ������ҵ����ϵ������ֵ����
		{
			if (mouse.x >= p->x1&&mouse.x <= p->x2)
				if (mouse.y >= p->y1&&mouse.y <= p->y2)
					return p->value;
		}
	}

	return 1;
}

int shezhi()//�޸���Ϸ����
{
	/*��ʾ����ҳ��*/
	IMAGE setting;
	loadimage(&setting, "img/2����.jpg");
	IMAGE select;
	loadimage(&select,"img/10ѡ��.jpg");
	
	/*���õ���¼�������Ϣ*/
	MOUSECLICK events[3] =
	{	{ 1031,74,1069,112, 1 },//�ر�
		{ 232,288,323,382, 2 },//����
		{ 677,288,770,382,3 }//��Ч
	};

	int OK=0;
	/*ִ�е���¼����Խ�����з���*/
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

int paihangbang()//��ȡ���а��ļ�����ʾ
{
	LOGFONT default;
	gettextstyle(&default);
	settextstyle(0, 0, "������ͤ��ϸ�ڼ���");
	/*��ʾ���а�ҳ��*/
	IMAGE image;
	loadimage(&image, "img/4���а�ս�۵÷�.jpg");
	putimage(0, 0, &image);
	FlushBatchDraw();
	/*��ȡ���а���Ϣ*/
	FILE*fp;
	if (fopen_s(&fp, "dat/paihang.dat", "r+") != 0)
	{
		outtextxy(600, 300, "���ļ�ʧ��");
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
		fscanf_s(fp, "%d",&c);//������ź;��, ��дc �޷�ͨ��
		fgetc(fp);//���� *
		fscanf_s(fp, "%d", &p->mode);
		fgetc(fp);//�������
		for (chp = p->name; (ch = fgetc(fp)) != '$' && (!feof(fp)); chp++)
		{
			*chp = ch;
		}
		fscanf_s(fp, "%d", &p->score);
		fgetc(fp);
		fscanf_s(fp, "%d", &p->level);
		fgetc(fp);
		fscanf_s(fp, "%d", &p->length);
		fgetc(fp);//��������
	}

	fclose(fp);//�ر��ļ�����д�ķ�ʽ���´��ļ�,�Ը��ǵ���ǰ�ļ�¼
	char string[50];
	RECT textr_1 = { 348,159,637,179 }, textr_2 = { 714, 159, 954, 179 };

	settextcolor(RGB(135,135,135));
	/*��ʾ���а�*/
	for (i = 1,p=pai; i <= 10 && p->score != 0; i++,p++)
	{

		sprintf_s(string, 50, "%s",p->name);
		drawtext(string, &textr_1, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		//outtextxy(210, 170+35*(i-1),string);
		//sprintf_s(string, 50, "%s", p->mode==1?"ս��ģʽ":"����ģʽ");
		//outtextxy(450, 170 + 35 * (i - 1), string);
		sprintf_s(string, 50, "%d", p->score);
		drawtext(string,&textr_2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//outtextxy(630, 170 + 35 * (i - 1), string);
		//sprintf_s(string, 50, mode==1?"��%d��":"��ͼ%d", p->level);
		//outtextxy(810, 170 + 35 * (i - 1), string);
		//sprintf_s(string, 50, "%d��", p->length);
		//outtextxy(960, 170 + 35 * (i - 1), string);
		textr_1.bottom += 43;
		textr_1.top += 43;
		textr_2.top += 43;
		textr_2.bottom += 43;
	}
	FlushBatchDraw();

	/*���õ���¼�������Ϣ*/
	MOUSECLICK events[1] =
	{ { 1092,494,1161,564, 1 }//�ر�
	};

	/*ִ�е���¼����Խ�����з���*/
	switch (_get_mouse_msg(events, 1))
	{

	case 1:return 1;
	}

	settextstyle(&default);
}

int rule()//��ȡ����ͼƬ����ʾ
{
	/*��ʾ����ҳ��*/
	IMAGE image_1,image_2,image_3;
	loadimage(&image_1, "img/����-1.jpg");
	loadimage(&image_2, "img/����-2.jpg");
	loadimage(&image_3, "img/����-3.jpg");
	putimage(0, 0, &image_1);
	FlushBatchDraw();

	/*���õ���¼�������Ϣ*/
	MOUSECLICK events[4] =
	{
		{ 487,534,515,563 ,1},
		{ 587,534,615,563 ,2},
		{ 687,534,715,563 ,3},
		{ 1092,494,1161,564, 4 }//�ر�
	};

	/*ִ�е���¼����Խ�����з���*/
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

/*����ֵΪ1������ѡ��һ���浵���룬����0����û��ѡ�У�������һ��*/
int zairucundang()//����浵
{
	/*��ʾ�浵ҳ��*/
	IMAGE image;
	loadimage(&image, "img/5����浵.jpg");
	putimage(0, 0, &image);
	FlushBatchDraw();
	
	MEMORY memo[8] = { 0 },*mp;
	int num=_read_memory(memo);//����ȡ�����������ݴ���memo[5]�У���ȡ���Ĵ浵������num��
	
	/*���õ���¼�������Ϣ*/
	MOUSECLICK events[11] =
	{ { 61,124,223,286 ,1},//1�Ŵ浵
	{ 306,124,471,286 ,2},//2�Ŵ浵
	{ 553,124,720,286 ,3},//3�Ŵ浵
	{ 798,124,960,286 ,4},//4�Ŵ浵
	{ 798,330,960,492 ,5},//5�Ŵ浵
	{ 553,330,720,492, 6 },//6�Ŵ浵
	{ 306,330,471,492 ,7},//7�Ŵ浵
	{ 61,330,223,492 ,8},//8�Ŵ浵
	{1143,24,1182,61,9},//�ر�
	{ 986,476,1055,545 ,10},//ɾ��
	{ 1084,476,1153,545 ,11}//��ʼ
	};

	_display_text(memo,num,events);

	IMAGE select;
	loadimage(&select, "img/10ѡ��.jpg",32,30);
	int select_memory=0,OK=0;
	/*ִ�е���¼����Խ�����з���*/
	while (!OK)
	{
		switch (_get_mouse_msg(events, 11))
		{

		case 1:select_memory = 1; break;//�浵һ
		case 2:select_memory = 2; break;//�浵��
		case 3:select_memory = 3; break;//�浵��
		case 4:select_memory = 4; break;//�浵��
		case 5:select_memory = 5; break;//�浵��
		case 6:select_memory = 6; break;//�浵��
		case 7:select_memory = 7; break;//�浵��
		case 8:select_memory = 8; break;//�浵��
		case 9:return 0;//����
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

	/*�Ѵ浵��Ϣ���ص�ȫ�ֱ�����*/
	_load_memory(&memo[select_memory-1]);

	gameRes = 2;
	return 1;
}

/*��ȡ�浵*/
int _read_memory(MEMORY* memo)
{


	FILE *fp;
	/*���ļ�*/
	if (fopen_s(&fp, "dat/memory.dat", "r") != 0)//�ļ�������ʱ
	{
		settextcolor(BLACK);
		outtextxy(600, 300, "�浵Ϊ��");
		FlushBatchDraw();
		return 0;
	};

	MEMORY*mp;
	int num,i;//��¼�浵����
	fscanf_s(fp, "%d", &num);
	char ch,*chp;
	int(*arrayp)[2];
	int n;

	for (i = 1,mp=memo; i <= num; i++,mp++)
	{
		fgetc(fp);//���з�
		fscanf_s(fp,"+%d���/");
		/*����*/
		for (chp = mp->name; (ch = fgetc(fp)) >0; chp++)
		{
			*chp = ch;
		}
		fgetc(fp);
		/*�ߵ���Ϣ*/
		fscanf_s(fp, "��/*%dģʽ$%d�÷�@%d�ؿ�/��ͼ>%d�Ѷ�\n", &mp->mode, &mp->score, &mp->level, &mp->degree);
		fscanf_s(fp, "&snake:%d����", &mp->direction);
		for (arrayp = mp->snake,n=1;fgetc(fp)!='\n'&&n<=100; arrayp++,n++)
		{
			fscanf_s(fp, "%d,%d", *arrayp, *arrayp + 1);
		}
		/*ʳ��*/
		fscanf_s(fp, "&fruit:");//ˮ��
		for (arrayp = mp->fruit,n=1; fgetc(fp) != '\n'&&n<=10; arrayp++,n++)
		{
			fscanf_s(fp, "%d,%d", *arrayp, *arrayp + 1);
		}

		fscanf_s(fp, "&bomb:");//ը��
		for (arrayp = mp->bomb, n = 1; fgetc(fp) != '\n'&&n <= 10; arrayp++, n++)
		{
			fscanf_s(fp, "%d,%d", *arrayp, *arrayp + 1);
		}


		fscanf_s(fp, "&poison:");//����
		for (arrayp = mp->poison, n = 1; fgetc(fp) != '\n'&&n <= 10; arrayp++, n++)
		{
			fscanf_s(fp, "%d,%d", *arrayp, *arrayp + 1);
		}

		fscanf_s(fp, "&herb:");//�ǻ۲�
		for (arrayp = mp->fruit, n = 1; fgetc(fp) != '\n'&&n <= 10; arrayp++, n++)
		{
			fscanf_s(fp, "%d,%d", *arrayp, *arrayp + 1);
		}

		/*��ȡ��ͼ��Ϣ*/
		fscanf_s(fp, "-%fcommonT-%ldPoisonTimer-%ldHerbTimer-%dai-", 
			&mp->commonT, &mp->PoisonTimer, &mp->HerbTimer, &mp->ai);


	}
	fclose(fp);
	return num;//�ɹ���ȡ7�򷵻ش浵���������򷵻�0
}

/*��ʾ��浵��Ӧ��������Ϣ*/
int _display_text(MEMORY* memo, int num, MOUSECLICK*events)
{
	MEMORY*mp = memo;
	RECT textr;
	LOGFONT default;
	gettextstyle(&default);

	settextstyle(20, 0, "������ͤ��ϸ�ڼ���",0,0,1000,false,false,false);
	int i=1;
	char string[50];
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	for (i = 1, mp = memo; i <= num; i++, mp++)
	{
		sprintf_s(string,50,"%s\n%sģʽ\n�ؿ�%d\n%d��",mp->name,mp->mode==1?"ս��":"����",mp->level,mp->score);
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

/*ɾ���浵*/
int _delete_memory(MEMORY*memo,int select_memory,int num)
{

	MEMORY*mp = memo+select_memory - 1;
	if (mp->score == 0)
		return 0;
	*mp = { 0 };//ֱ�ӶԽṹ�帳ֵ��C�������Ǵ���ģ���c++������ȷ��

	int i;
	for (i = select_memory - 1; i <= 3; i++,mp++)
		*mp = *(mp+1);

	FILE *fp;
	/*���ļ�*/
	if (fopen_s(&fp, "dat/memory.dat", "w") != 0)//�ļ�������ʱ������õڶ��ַ�ʽ��������õ�һ�ַ�ʽ
	{
		settextcolor(BLACK);
		outtextxy(600, 300, "���ļ�ʧ��");
		FlushBatchDraw();
		return 0;
	};

	/*��д�浵����*/
	if(num!=1)//num Ϊ1����ôɾ����浵��Ϊ0����ʲô��û�У��Ͳ���д�浵����
		fprintf(fp, "%d", num-1);
	int(*arrayp)[2],n;
	/*���*/
	for(mp=memo,i=1;i<=5&&mp->score!=0;mp++)
	{
		fprintf(fp, "\n+%d���/%s����/*%dģʽ$%d�÷�@%d�ؿ�/��ͼ>%d�Ѷ�\n", i, mp->name, mp->mode, mp->score, mp->level, mp->degree);

		/*����ߵ���Ϣ*/
		fprintf(fp, "&snake:%d����", mp->direction);
		for (arrayp = mp->snake, n = 1; **arrayp!=0&&n <= 100; arrayp++, n++)
		{
			fprintf_s(fp, ",%d,%d", **arrayp,*(*arrayp + 1));
		}

		/*���ʳ�����Ϣ*/
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

/*�Ѵ浵��Ϣ���ص�ȫ�ֱ�����*/
int _load_memory(MEMORY *memo)
{
	mode = memo->mode;
	score = memo->score;
	level = memo->level;
	degree = memo->degree;
	direction = memo->direction;
	/*������*/
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
	/*����ʳ��*/
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

	/*����������Ϣ*/
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
	load_map(memo->level);//���ص�ͼ

	set_speed(memo->degree);//�����Ѷ�


	return 1;
}