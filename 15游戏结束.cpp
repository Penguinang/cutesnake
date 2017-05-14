#include"ͷ�ļ�.h"
#include"�궨��.h"
#include"�ṹ��.h"
#include"���к�������.h"
#include"ȫ�ֱ���������д��������Ҫ�ļ���.h"

/*ʧ�ܣ�
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

	settextstyle(40, 20, _T("����"));
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

/*����������Ϣ*/
int setrecord(){    
	FILE*fp;
	if (fopen_s(&fp,"dat/paihang.dat", "r+") != 0)
	{
		outtextxy(600, 300, "���ļ�ʧ��");
		_getch();
		exit(0);
	};

	PAIHANG pai[10] = { 0 };
	PAIHANG*p = pai;
	char ch,c,*chp;
	int i;
	for (i = 1; !feof(fp) && i <= 10; i++, p++)
	{
		fscanf_s(fp, "%d");//������ź;��
		fgetc(fp);//���� *
		fscanf_s(fp, "%d", &p->mode);
		fgetc(fp);//�������
		for (chp=p->name;(ch = fgetc(fp)) != '$'&& (!feof(fp));chp++)
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

	if (fopen_s(&fp, "dat/paihang.dat", "w") != 0)
	{
		outtextxy(600, 300, "���ļ�ʧ��");
		_getch();
		exit(0);
	};

	int signal=1;
	char name[20];

	/*�ȽϾɼ�¼���¼�¼������������ֱ�����ʮ����
				signal ��¼�¼�¼�Ƿ��Ѿ�������ˣ�1����û��*/
	for (i = 1, p = pai; i <= 10&&!feof(fp)&&p->score!=0; i++, p++)
	{
		if (score >= p->score&&signal)
		{
			InputBox(name, 20, "����������");
			fprintf(fp, "%d*%d.%s$%d@%d#%d\n", i ,mode, name, score, level, LENGTH);
			signal = 0;
			p--;
		}
		else fprintf(fp, "%d*%d.%s$%d@%d#%d\n", i ,p->mode, p->name, p->score, p->level, p->length);
	}

	/*����¼�¼û����������������¼��������ʮ��*/
	if(i<=10&&signal)
	{
		InputBox(name, 20, "����������");
		fprintf(fp, "%d*%d.%s$%d@%d#%d\n", i ,mode, name, score, level, LENGTH);
		signal = 0;
	}
	fclose(fp);
	return 1;
}

/*�������а��ļ�*/
int loadpaihang()
{
	FILE*fp;
	if (fopen_s(&fp, "dat/paihang.dat", "r+") != 0)
	{
		outtextxy(600, 300, "���ļ�ʧ��");
		_getch();
		exit(0);
	};

	PAIHANG pai[10] = { 0 }, *p = pai;
	char ch, *chp;

	for (; !feof(fp); p++)
	{
		fgetc(fp);
		fgetc(fp);//������ź;��
		for (chp = p->name; (ch = fgetc(fp)) != '$'; chp++)
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
	return 1;
}

/*��Ϸʧ�ܺ��ѡ��*/
int end_select()
{

	IMAGE img1,img2;
	loadimage(&img1, "img/��Ϸ����.jpg");
	putimage(537, 75,&img1);
	loadimage(&img2, "img/����.jpg");
	putimage(573, 156,&img2 );
	loadimage(&img2, "img/�ؿ�.jpg");
	putimage(573, 263, &img2);

	LOGFONT default;

	gettextstyle(&default);


	settextstyle(26, 0, "Ĭ��");
	setfillcolor(RGB(105, 195, 108));
	solidcircle(600, 450, 40);
	settextcolor(RGB(105, 195, 108));
	outtextxy(574,507,"����");
	setfillcolor(RGB(255, 87, 87));
	solidcircle(395, 450, 40);
	settextcolor(RGB(255,87,87));
	outtextxy(370, 507, "��ҫ");
	setfillcolor(RGB(243, 209, 75));
	solidcircle(805, 450, 40);
	settextcolor(RGB(243,209,75));
	outtextxy(778,507,"����");

	settextstyle(&default);

	IMAGE icon;
	loadimage(&icon, "img/����.jpg");
	putimage(782, 433, &icon);
	loadimage(&icon,"img/��ҫ.jpg");
	putimage(376, 432, &icon);
	loadimage(&icon, "img/����.jpg");
	putimage(577, 428, &icon);
	FlushBatchDraw();

	/*���õ���¼�������Ϣ*/
	MOUSECLICK events[3] =
	{ { 355,410,435,490, 1 },/*��ҫ*/
	{ 560,410,640,490, 2 },/*����*/
	{ 765,410,845,490,3 },/*����*/
	};

	IMAGE savemessage;
	loadimage(&savemessage, "img/�ѱ���.jpg");
	while (true)
	{

		/*ִ�е���¼����Խ�����з���*/
		switch (_get_mouse_msg(events, 3))
		{

		case 1: saveimage("����.bmp", 0); putimage(535, 355, &savemessage); FlushBatchDraw(); break;
		case 2:return 0; break;
		case 3:if (mode == 1)
				load_map(1);
			set_speed(degree);
			initdata();
			return 1; break;
		}

	}

}