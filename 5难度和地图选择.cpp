#include"ͷ�ļ�.h"
#include"�궨��.h"
#include"�ṹ��.h"
#include"���к�������.h"
#include"ȫ�ֱ���������д��������Ҫ�ļ���.h"


/*�ѶȺ͵�ͼѡ��
			*/
int _map_degree()
{
	if (mode == 1)
		mode1();
	else mode2();
	return 1;
}
/*ս��ģʽ����*/
int mode1()
{

	/*����ѡ��ҳ��*/
	IMAGE menu, select;
	loadimage(&menu, "img/mode1.jpg");
	loadimage(&select, "img/10ѡ��.jpg");
	putimage(0, 0, &menu);
	FlushBatchDraw();

	/*���õ���¼�������Ϣ*/
	MOUSECLICK events[4] =
	{ { 373,241,465,489,1 },//С��ģʽ
	{ 517,241,609,489,2 },//ר��ģʽ
	{ 658,241,750,489 ,3 },//����ģʽ
	{ 856,420,925,489,4 },//ȷ��
	};

	int select_degree = 0, OK = 0;//ѡ�е��Ѷȣ���ѡ�����
	while (!OK|| select_degree == 0)
	{

		/*ִ�е���¼����Խ�����з���*/
		switch (_get_mouse_msg(events, 4))
		{
			/*1~3 ���Ѷȵ�ѡ��*/
		case 1:select_degree = 1; fruitNum = 5; bombNum = 1; poisonNum = 3; degree = 1; break;
		case 2:select_degree = 2; fruitNum = 6; bombNum = 5; poisonNum = 6; degree = 2; break;
		case 3:select_degree = 3; fruitNum = 10; bombNum = 10; poisonNum = 10; degree = 3; break;
			/*OK Ϊ1ʱ��ѭ�������*/
		case 4:
			if (select_degree != 0)
				OK = 1; 
		}
		putimage(0, 0, &menu);
		if (select_degree != 0)
			putimage(events[select_degree-1].x1,397, &select);//�Ѷ�ѡ��ͼ��       //��Щ�Ǿ��������ֵ
		//����㷨���ã�����ʵ���Ҳ������õ���

		FlushBatchDraw();
	}
	
	load_map(1);//���ص�ͼ

	set_speed(select_degree);//�����Ѷ�

	initdata();//��Ϸ���ݳ�ʼ��

	return 1;
}

/*����ģʽ����*/
int mode2()
{

	/*����ѡ��ҳ��*/
	IMAGE menu, select;
	loadimage(&menu, "img/mode2.jpg");
	loadimage(&select, "img/10ѡ��.jpg",32,30);
	putimage(0,0, &menu);
	FlushBatchDraw();

	/*���õ���¼�������Ϣ*/
	MOUSECLICK events[13] =
	{ { 137,174,302,208,1 },//С��ģʽ
	{ 137,249,302,285,2 },//ר��ģʽ
	{ 137,325,302,360 ,3 },//����ģʽ
	{ 397,118,561,238, 4 },//��ͼһ
	{ 606,118,773,237 ,5 },//��ͼ��
	{ 810,118,977,237,6 },//��ͼ��
	{ 397,272,562,387,7 },//��ͼ��
	{ 602,272,723,387,8 },//��ͼ��
	{ 810,272,977,387,9 },//��ͼ��
	{ 397,423,562,543,10 },//��ͼ��
	{ 602,429,773,543,11 },//��ͼ��
	{ 810,429,977,543,12 },//��ͼ��
	{ 127,489,196,558,13 },//ȷ��
	};

	int select_map = 0, select_degree = 0, OK = 0;//ѡ�еĵ�ͼ��ѡ�е��Ѷȣ���ѡ�����
	while (!OK || select_map == 0 || select_degree == 0)
	{

		/*ִ�е���¼����Խ�����з���*/
		switch (_get_mouse_msg(events, 13))
		{
			/*1~3 ���Ѷȵ�ѡ��*/
		case 1:select_degree = 1; fruitNum = 5; bombNum = 1; poisonNum = 3; degree = 1; break;
		case 2:select_degree = 2; fruitNum = 6; bombNum = 5; poisonNum = 6; degree = 2; break;
		case 3:select_degree = 3; fruitNum = 10; bombNum = 10; poisonNum = 10; degree = 3; break;
			/*4~9 �ǵ�ͼ��ѡ��*/
		case 4:select_map = 1; break;
		case 5:select_map = 2; break;
		case 6:select_map = 3; break;
		case 7:select_map = 4; break;
		case 8:select_map = 5; break;
		case 9:select_map = 6; break;
		case 10:select_map = 7; break;
		case 11:select_map = 8; break;
		case 12:select_map = 9; break;
			/*OK Ϊ1ʱ��ѭ�������*/
		case 13:
			if (select_map == 0 || select_degree == 0)
				continue;
			else OK = 1;
		}
		putimage(0, 0, &menu);
		if (select_degree != 0)
			putimage(274, 4+events[select_degree-1].y1, &select);//�Ѷ�ѡ��ͼ��       //��Щ�Ǿ��������ֵ
		if (select_map != 0)
			putimage(events[select_map+2].x1-33, events[select_map+2].y1, &select);
		//��ͼѡ��ͼ��     //����㷨���ã�����ʵ���Ҳ������õ���

		FlushBatchDraw();
	}

	level = select_map;

	load_map(select_map);//���ص�ͼ

	set_speed(select_degree);//�����Ѷ�

	initdata();//��Ϸ���ݳ�ʼ��
	return 1;
}


/*���ص�ͼ��
		���ļ��е�����д����������*/
int load_map(int select_map)
{

	/*�Ƚ���һ�ѵ�ͼ���ˣ��ټ�����һ�ѵ�ͼ*/
	int(*p)[11][2] = map + 1, i;
	for (i = 1; i <= 20; i++, p++)
		***p = 0;//ÿ������εĵ�һ��Ԫ�������ı�������Ϊ0��ˢ��ʱ����������������

	FILE *fp;

	if(mode==1)//ս��ģʽ
	{
		if (fopen_s(&fp, "dat/mode1.dat", "r") != NULL)//�������ַ����м�\��ֻ�ðѵ�ͼ�ļ�������Դ�ļ�ͬ��
		{
			outtextxy(600, 300, "�޷��򿪵�ͼ");
			settextcolor(BLACK);
			FlushBatchDraw();
			_getch();
			exit(0);
		}
	}
	else {
		if (fopen_s(&fp, "dat/mode2.dat", "r") != NULL)//�������ַ����м�\��ֻ�ðѵ�ͼ�ļ�������Դ�ļ�ͬ��
		{
			outtextxy(600, 300, "�޷��򿪵�ͼ");
			settextcolor(BLACK);
			FlushBatchDraw();
			_getch();
			exit(0);
		}
	}
	

	while (!feof(fp))
	{
		/*�ڵ�ͼ�ļ��еĸ�ʽ��$1.1@400,290,150@3��4��5��5��$2.1@34��56��23��3���������ȵ�:
				$1.   �����һ����ͼ
				�����   1   ����õ�ͼ����ǽ
				���� @ �������ߵ�����ͷ���
				������ÿ������ε�����ֵ
			����������ֵ�ķֽ磬�ֺ��Ƕ���εĻ���,ÿ������κ������дһ���ֺţ�$ ��Ԫ�����ǵ�ͼ�Ļ���*/
		if (fgetc(fp) != '$')
			continue;
		if (fgetc(fp) == select_map + 48)
			break;
	}
	fgetc(fp);//����ź���ľ������

	/*��ȡ�õ�ͼ�Է�ǽ�����*/
	***map = fgetc(fp) - 48;//����ɴ����ͼ��һ������ε�һ��һά����ĵڶ���Ԫ����
	fgetc(fp);//�Ѻ���� @ ����


	int (*poly)[11][2]=map+1;//poly ָ���ά���飬��Ϊÿһ���������һ����ά�����ڵĵ���ɣ�
	int *polypointxy=&map[0][1][0];//polypoint ָ��һ���㣬Ҳ��һ��һά���飬
	int xy=0;//xy��ʱ�洢���ļ���ȡ��������
	char ch;//ch��ʱ�洢���ļ���ȡ�����ַ�

	/*���ع����ߵ���Ϣ:
				�ߵ���Ϣ���ڰ���һ����ά�����еڶ�������һά����*/
	for (; (ch = fgetc(fp)) != '@';)
	{
		if (ch == ',')
		{
			*polypointxy++ = xy;
			xy = 0;
			continue;
		}
		xy = xy * 10 + ch - 48;
	}
	*polypointxy++ = xy;
	xy = 0;


	/*��ȡ��ͼ����Ϣ*/
	polypointxy = &map[1][1][0];
	for (i=0;(ch=fgetc(fp)) != '$';)//�ٴζ���$ʱ�����ͼ�������
	{
		if (ch == '\n')
			continue;
		if (ch == ',')//��������ʱ��xy�ݴ�����ָ��� polypointxy �������
		{
			*polypointxy++ = xy;
			i++;//��ȡһ�����꣬��һ��
			xy = 0;
			continue;
		}
		if (ch == ';')//�����ֺ�ָ��ָ����һ�������
		{
			*polypointxy++ = xy;
			i++;//��ȡһ�����꣬��һ��
			i = i / 2;//��������ת��Ϊ����
			***poly = i;//�Ѷ���α������ڶ���ε�һ��Ԫ����
			i = 0;
			xy = 0;
			polypointxy = **(++poly)+2;//polypoint��ָ����һ������εĵ�һ���������
			continue;
		}
		xy = xy * 10 + ch - 48;
	}

	return 1;
}

/*�����ٶȴ�С*/
int set_speed(int select_degree)
{
	switch (select_degree)
	{
	case 1:T0 = 180; DT = 0.030; break;
	case 2:T0 = 170; DT = 0.050; break;
	case 3:T0 = 150; DT = 0.070; break;
	}

	
	return 1;
}

/*��Ϸ���ݳ�ʼ��*/
int  initdata()
{
	snake_head = { map[0][1][0],map[0][1][1],1,0,0 };
	direction = map[0][2][0];
	//��һ��ģʽ��һ�ػ�ڶ���ģʽ����Ҫ��score����
	if (mode == 2 || level == 1)
		score = 0;
	commonT = T0;

	/*��������*/
	int *p = *poison, i;
	for (i = 1; i <= 20; i++, p++)
		*p = 0;
	for (p = *fruit, i = 1; i <= 20; i++, p++)
		*p = 0;
	for (p = *bomb, i = 1; i <= 20; i++, p++)
		*p = 0;

	for (p = *fruit, i = 1; i <= fruitNum; i++, p += 2)
	{
		_food_create(p, FRUITR);
	}

	for (p = *bomb, i = 1; i <= bombNum; i++, p += 2)
	{
		_food_create(p, BOMBR);
	}

	PoisonTimer = 10000;
	gameRes = 2;
	return 1;
}