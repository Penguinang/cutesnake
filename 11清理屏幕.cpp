#include"ͷ�ļ�.h"
#include"�궨��.h"
#include"�ṹ��.h"
#include"���к�������.h"
#include"ȫ�ֱ���������д��������Ҫ�ļ���.h"


int clear()
{
	
	SNAKE* p1;

	/*���ʺͱ߿���ɫ����Ϊ����ɫ���Ա������Ļ�ϵĸ���ͼ��*/


	setfillcolor(BKCOLOR);
	setlinecolor(BKCOLOR);

	/*������ͷ*/
	fillcircle(head->x, head->y, R);

	/*���������۾�*/
	fillcircle(head->x + R*sin(direction*DEGREE), head->y + 0.7*R*cos(direction*DEGREE), 2);
	fillcircle(head->x - R*sin(direction*DEGREE), head->y - 0.7*R*cos(direction*DEGREE), 2);

	/*��������*/
	p1 = head->next;
	for (; p1 != 0; p1 = p1->next) {
		fillcircle(p1->x, p1->y, R);
	}

	/*��������ʳ��*/
	paint_food(*fruit, FRUITR, BKCOLOR);//��ˮ��
	paint_food(*bomb, BOMBR, BKCOLOR);//��ը��
	paint_food(*herb, HERBR, BKCOLOR);//���ǻ۲�
	paint_food(*poison,POISONR, BKCOLOR);//������

	/*������Ϣ��*/
	setbkcolor(0xecb923);
	clearrectangle(820, 100, 1200, 250);
	clearrectangle(820, 400, 1000, 450);
	clearrectangle(800, 0, 820, 600);//��ԭ���ܹ�֮����ǽ�ϵ�ȱ��
	
	return 1;
}