#include"ͷ�ļ�.h"
#include"�궨��.h"
#include"�ṹ��.h"
#include"���к�������.h"
#include"ȫ�ֱ���������д��������Ҫ�ļ���.h"

/*�����жϣ�
		*/
int _death_judge()
{

	SNAKE*p;
	p = head == tail ? head : head->next;
	/*���������û����ײ��ֻ�����ڻ�һ��ʱ������ײ*/
	if (head != tail&&head->next != tail)
		for (p = head->next->next; p != 0; p = p->next) 
		{
			if (pow(p->x - head->x, 2) + pow(p->y - head->y, 2) < pow(2 * R, 2))
			{
				gameRes = -1;
				return 1;
			}
		}

	/*��ǽ������*/
	if(***map==0)
	/*�����û����ǽ��ײ*/
	if (fabs(head->x-400) > 400-R || fabs(head->y-300) > 300-R)
	{
		gameRes = -1;
		return 1;
	}

	if (wall_check(head->x, head->y, R))
		gameRes = -1;
	//int(*p_poly)[11][2],*xy,i;//p_polyָ������

	//for (p_poly = map+1,i=1;***p_poly!=0&&i<=20;p_poly++,i++)//�����û�����ϰ���ײ��***p_poly�Ƕ���α���
	//{
	//	xy = *(*p_poly + 1);
	//				//xyָ��ǰ��ά����ĵڶ���һά����ĵ�һ��Ԫ�أ�����ǰ����εĵ�һ������ĺ�����
	//	if (_duang(xy, head->x, head->y, R) == 1)
	//	{
	//		
	//		gameRes = -1;
	//		return 1;
	//	}
	//		
	//	
	//}
	return 0;
}


/*���һ��Բ�Ƿ���һ��ֱ���ཻ��
			����Ĳ�����Բ�����ꡢֱ������������*/
int _meet_line(int circlex,int circley,int r,int x1,int y1,int x2,int y2)
{
	int d,a,b,c;
	a = y1 - y2;
	b = x2 - x1;
	c = y1*x2 - y2*x1;
	d = abs(a*circlex + b*circley + c) / sqrt(a*a + b*b);
	if (d < r)
		return 1;
	return 1;
}

/*���Բ�Ƿ���һ������η�����ײ��
			����Ĳ����Ǿ��ε�һ����ĺ������ַ����Բ�����ꡢ�뾶*/
int _duang(int *p,int circle_x,int circle_y,int r)
{
	/*x1,x2,y1,y2���ϰ���������ߵ�����*/
	int x1, x2, y1, y2;
	x1 = *p;
	y1 = *(++p);
	x2 = *(p = p + 3);
	y2 = *(++p);

	/*���Բ���ϰ�����뾶r���ڣ�����Ϊ��������ײ*/
	if (circle_x >= x1 - r&&circle_x <= x2 + r)
		if (circle_y >= y1 - r&&circle_y <= y2 + r)
			return 1;
	return 0;
}

/*���һ��Բ�Ƿ����ϰ��﷢����ײ*/
int wall_check(int circle_x,int circle_y,int r)
{
	int(*p_poly)[11][2], *xy,i;//p_polyָ������

	/*ÿ�������Ĺ��̱���� i ���������Ժ���ʹ��ָ�뷨ʱ��ע��*/
	for (p_poly = map+1,i=1; ***p_poly != 0&&i<=20; p_poly++,i++)//�����û�����ϰ���ײ��***p_poly�Ƕ���α���
	{
		xy = *(*p_poly + 1);
		//xyָ��ǰ��ά����ĵڶ���һά����ĵ�һ��Ԫ�أ�����ǰ����εĵ�һ������ĺ�����
		if (_duang(xy, circle_x, circle_y, r) == 1)
		{

			return 1;
		}


	}
	return 0;
}
