#include"ͷ�ļ�.h"
#include"�궨��.h"
#include"�ṹ��.h"
#include"���к�������.h"
#include"ȫ�ֱ���������д��������Ҫ�ļ���.h"

/*ͼ�γ�ʼ����
		��ͼ��ģʽ�����ñ���ɫ�ʹ��ڴ�С*/

int initwindow()
{
	SetWindowText(initgraph(WIDTH + 400, HEIGHT), "Penguinang��Mario̰����");//��ʼ��ͼ��ģʽ//���ô��ںͱ���
	HWND hwnd = GetHWnd();

	/*���д���*/
	// ��ȡ���ڱ߿���
	int cx = GetSystemMetrics(SM_CXFIXEDFRAME)+4;
	int cy = GetSystemMetrics(SM_CYFIXEDFRAME) + GetSystemMetrics(SM_CYCAPTION)+4;
	HRGN clip = CreateRectRgn(cx, cy, WIDTH + 400+cx+2, HEIGHT+cy+2);
	SetWindowRgn(hwnd, clip, true);

	setbkcolor(WHITE);//���ñ�����ɫ
	cleardevice();

	BeginBatchDraw();
	return 1;
}