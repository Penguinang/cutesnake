#include"ͷ�ļ�.h"
#include"�궨��.h"
#include"�ṹ��.h"
#include"���к�������.h"
#include"ȫ�ֱ���������д��������Ҫ�ļ���.h"

/*�浵��
		*/
int pause()
{

	setfillcolor(RGB(255, 87, 88));
	solidroundrect(247, 117, 902, 200, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(247, 450 , 902, 499, 10, 10);

	IMAGE img,tittle;
	loadimage(&img, "img/��ͣͼƬ.jpg");
	putimage(247, 147, &img);
	loadimage(&tittle,"img/��ͣ����.jpg");
	putimage(293, 120, &tittle);
	FlushBatchDraw();

	
	/*���õ���¼�������Ϣ*/
	MOUSECLICK events[4] =
	{ { 415,236,777,264,1 },//����
	{ 818,214,870,264,2 },//ȷ��
	{ 415,375,458,421 ,3 },//����
	{ 730,375,777,421,4 }//�˳�
	};

	int conti=0;//continue �ļ�д������������������״̬
	int signal=0;//����״̬�ı�־��0����δ���룬1����������
	char name[20] = {0};//�浵����
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
	

	/*�ָ�ͼ��*/
	setbkcolor(BKCOLOR);
	cleardevice();

	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);
	setfillcolor(0xecb923);
	solidrectangle(800, 0, 1200, 600);

	return 1;
}

/*�õ�������ַ���*/
int _get_name(char*name,int *signal)
{
	/*����������*/
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
		outtextxy(415+textwidth('��')*(i-1), 236, ch);
		FlushBatchDraw();
	}
	*signal = 1;

	return 1;

}

/*�����浵*/
int _set_memory(char*name,int *signal)
{
	if (*signal == 0)
	{
		settextcolor(BLACK);
		outtextxy(600, 100, "������");
		FlushBatchDraw();
		return 0;
	}

	FILE *fp;
	/*���ļ�*/
	if (fopen_s(&fp, "dat/memory.dat", "r+") != 0)//�ļ�������ʱ������õڶ��ַ�ʽ��������õ�һ�ַ�ʽ
	{
		if (fopen_s(&fp, "dat/memory.dat", "w") != 0)
		{
			settextcolor(BLACK);
			outtextxy(600, 300, "���ļ�ʧ��");
			FlushBatchDraw();
			_getch();
			exit(0);
		}
	};

	/*�жϴ浵�Ƿ��Ѿ�����*/
	int memory_number;

	if (fscanf_s(fp, "%d", &memory_number) == -1)//fscanf()����ֵ�ǳɹ���ȡ�����ĸ�����û�гɹ���ȡ����-1
		memory_number = 0;
	if (memory_number >= 8)
	{
		settextcolor(BLACK);
		outtextxy(600, 100, "�浵����");
		FlushBatchDraw();
		return 1;
	}

	/*��ָ���ƶ����ļ���ͷ*/
	fseek(fp, 0, 0);
	/*��д�浵����*/
	fprintf(fp, "%d", ++memory_number);

	/*��ָ���ƶ����ļ�ĩβ*/
	fseek(fp, 0, 2);
	/*���*/
	fprintf(fp, "\n+%d���/%s����/*%dģʽ$%d�÷�@%d�ؿ�/��ͼ>%d�Ѷ�\n", memory_number,name,mode, score,level, degree);

	/*����ߵ���Ϣ*/
	fprintf(fp, "&snake:%d����", direction);
	SNAKE*ps = head;
	for (; ps != 0;ps=ps->next)
	{
		fprintf(fp, ",%d,%d", ps->x, ps->y);
	}

	/*���ʳ�����Ϣ*/
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

	loadimage(&success, "img/�洢�ɹ�.jpg");
	putimage(486, 265, &success);
	signal = 0;
	return 1;
}