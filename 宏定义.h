#pragma once


#define R 10//�ߵ�ÿ���ڵ�뾶
#define PI 3.1415927
#define DEGREE PI/180//һ��
#define DX 15//DX-->��ÿ���ƶ��ľ���,Ҳ��ÿ�����ڵ�Բ�ĵľ��룻
#define B 30//����-->�ߵ���Сת�ǣ���λΪ�ȣ�
//���ƶ��������ٶ�Ϊ v =DX/realT; ת��뾶Ϊ r=(DX/2)/(tan(B/2))
//��ǰ��v=0.1����λ��r=13.0����λ
///////////////////////////////////
//		DX		R		B		v		r
//		15		10		30		0.1		13.0
//		10		8		20		0.1		13.7
//
//
//		  0.073        20.52

#define BKCOLOR RGB(233,236,243)
#define COLOR_1 RGB(0,159,232)
#define COLOR_2 WHITE
#define LINE_COLOR RGB(205, 208, 215)

/*����ʳ��Ĵ�С��ˮ�����ǻ۲ݡ�ը���Ĵ�С�ǹ̶��ģ����ݵĴ�С�ǿɱ��*/
#define FRUITR 5//һ��ʳ��İ뾶
#define HERBR 20//һ���ǻ۲ݵİ뾶
#define BOMBR 15//һ��ը���İ뾶
#define POISONR 5//���ݵ����뾶
#define SAFETIME 15000//��ȫʱ�䣬�ڰ�ȫʱ���ڲ����ж�ҩ��Ҳ���Ƕ�ҩÿ����ȫʱ�����һ��
#define DANGERTIME 30000//Σ���¼�����Σ��ʱ���ڣ���ȫʱ�������ֶ��ݣ�������������������DANGERTIME

#define LEFT  0x4B00
#define RIGHT 0x4D00
#define UP    0x4800
#define DOWN  0x5000
#define ESC   0x011B
#define ENTER 0x1C0D

#define WIDTH 800
#define HEIGHT 600

#define LENGTH tail->order

#define RUSHT 50