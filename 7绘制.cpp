#include"ͷ�ļ�.h"
#include"�궨��.h"
#include"�ṹ��.h"
#include"���к�������.h"
#include"ȫ�ֱ���������д��������Ҫ�ļ���.h"

/*������Ļ��
		*/
int paint()
{

	SNAKE* p1;
	

	/*�ָ�������ɫ*/
	setlinecolor(BLACK);

	/*���ο���*/
	int i;
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);
	setlinecolor(LINE_COLOR);
	for (i = 0; i <= 800; i += 20)
		line(i, 0, i, 600);
	for (i = 0; i <= 600; i += 20)
		line(0, i, 800, i);

	/*�����*/
	
	if (***map == 0)//��ǽ������ʱ
	{

		setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 5);
		setlinecolor(BLACK);
		rectangle(0, 0, 800, 600);
	}


	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);
	setlinecolor(LINE_COLOR);
	/*���ϰ���*/
	int(*p)[11][2], *xy;//pָ��㣨һά���飩��xyָ��������꣨���ͱ�����
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);
	setfillcolor(RED);
	for (p = map+1, xy = *(*p + 1),i=1; ***p != 0&&i<=20;i++)
	{
		fillpoly(***p, xy);
		p++;
		xy = *(*p + 1);
	}


	/*����ͷ*/
	setfillcolor(COLOR_1);
	setlinecolor(RGB(172, 177, 189));
	fillcircle(head->x, head->y, R);
	setfillcolor(0x000000);

	/*�������۾�*/
	fillcircle(head->x + R*sin(direction*DEGREE), head->y + 0.7*R*cos(direction*DEGREE), 2);
	fillcircle(head->x - R*sin(direction*DEGREE), head->y - 0.7*R*cos(direction*DEGREE), 2);

	/*������*/
	setfillcolor(COLOR_2);
	p1 = head->next;
	for (; p1 != 0; p1 = p1->next) {
		fillcircle(p1->x, p1->y, R);
		if (getfillcolor() == COLOR_2)
			setfillcolor(COLOR_1);
		else setfillcolor(COLOR_2);
	}

	/*������ʳ��*/
	paint_food(*fruit,FRUITR, 0x24c097);//��ˮ��
	paint_food(*bomb,FRUITR, 0x000000);//��ը��
	paint_food(*herb, FRUITR, 0x16e1ea);//���ǻ۲�
	paint_food(*poison,POISONR, HSLtoRGB((poison_color_h+=7)%360,(poison_color_h%4+3)/10.0, (poison_color_h % 4 + 3) / 10.0));//������


	/*����Ϣ��*/
	char information[40];
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	sprintf_s(information, "������%d", score);//������
	outtextxy(820, 100,information); 
	sprintf_s(information, "���ȣ�%d", LENGTH);//������
	outtextxy(820, 150, information);
	sprintf_s(information, "�ؿ���%d", level);//�ؿ���
	outtextxy(820, 200, information);

	/*���Ի���*/
	char conversation[50];
	sprintf_s(conversation, "���ݻ���%d�뵽��", 15-PoisonTimer/1000>0? 15 - PoisonTimer / 1000:0);
	outtextxy(820, 400, conversation);
	FlushBatchDraw();
	return 1;
}

/*��ʳ��:
		��ȡ����ָ���������ݣ�����һ�黭һ��ָ����С����ɫ��Բ��ֱ������0Ϊֹ*/
int paint_food(int *food,int food_r,int color)
{
	int *p=food,i=1;
	setfillcolor(color);
	while (*p != 0&&i<=10)
	{
		solidcircle(*p, *(p+1), food_r);
		p+=2;
		i++;
	}
	
	return 1;
}

