#include"ͷ�ļ�.h"
#include"�궨��.h"
#include"�ṹ��.h"
#include"���к�������.h"
#include"ȫ�ֱ���������д��������Ҫ�ļ���.h"

/*�ؿ��ж�*/
int _level()
{
	if (LENGTH >= 10) 
	{

		
		if (++level >= 10)
		{
			_playmusic("win");
			gameRes = 1;
			IMAGE img;
			loadimage(&img, "img/ʤ��.jpg");
			setfillcolor(WHITE);
			solidrectangle(0, 200, 1200, 600);
			_change_picture(&img/*ͼƬָ��*/, -30, 200, 0,
				200/*�ֱ��ǿ�ʼ�����꣬�����ʱ������*/, 0/*ͼƬ�ƶ��ķ���һ���Ƕ�ֵ*/);
			gameRes = 1;
			Sleep(1000);
			_getch();

			return 1;
		}
		else
		{
			_playmusic("pass");
			load_map(level);
			IMAGE img;
			loadimage(&img, "img/8������һ��.jpg");
			setfillcolor(WHITE);
			solidrectangle(0, 200, 1200, 600);
			_change_picture(&img/*ͼƬָ��*/, 0, 200, 300,
				200/*�ֱ��ǿ�ʼ�����꣬�����ʱ������*/, 0/*ͼƬ�ƶ��ķ���һ���Ƕ�ֵ*/);
			Sleep(1000);
			tail = head;
			head->next = 0;
			initdata();
			initgame();
			
			/*�����ûس��ͼ�����Ϸ������ȴ����������Ϸ*/
			int wait=0;
			while (wait<=2000)
			{
				Sleep(300);
				wait += 300;
				if (_kbhit())
					if (_getch() == 13)
						break;
			}
		}
	}
	return 1;
}