#include"ͷ�ļ�.h"
#include"�궨��.h"
#include"�ṹ��.h"
#include"���к�������.h"
#include"ȫ�ֱ���������д��������Ҫ�ļ���.h"


/*��Ϸ�����ʼ��*/
int initgame()
{
	setbkcolor(BKCOLOR);
	cleardevice();
	
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);
	setfillcolor(0xecb923);
	solidrectangle(800, 0, 1200, 600);

	
	return 1;
}