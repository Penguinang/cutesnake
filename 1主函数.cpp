//////////////////////////////
////   cutesnake
//////////////////////////////

#include"ͷ�ļ�.h"
#include"�궨��.h"
#include"�ṹ��.h"
#include"ȫ�ֱ������壨д���������ļ���.h"
#include"���к�������.h"
#pragma comment(lib, "Winmm.lib")



void main()
{

	initwindow();//ͼ�ν����ʼ��
	do
	{

		if (music)
			_playmusic("BGM");//����BGM�Ĳ���
		start();//������Ϸ
		if (score == 0)//��0��ʼ������������浵
			_map_degree();//�ѶȺ͵�ͼѡ�� 


		do
		{
			initgame();//��Ϸ�����ʼ��

			while (gameRes == 2)
			{
				if (music)
					_playmusic("BGM");//����BGM
				paint();//������Ļ
				Sleep((int)realT);//��Ļ�Ӿ���ʱ���� T ����
				_death_judge();//�����û�з���ײǽ֮��ĵ�������������
				if (mode == 1)
					_level();
				addspeed();
				clear();
				_food_judge();//�����û�гԵ�ʲô����
				move();//���߽����ƶ�
			}
		} while (end());
			
	} while (1);
}