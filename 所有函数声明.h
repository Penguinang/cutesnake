#pragma once

/*ͼ�γ�ʼ��*/
int initwindow();

/*����BGM*/
int _playmusic(LPSTR music);
int _playsound(LPSTR wav);//������Ч

/*��ʼѡ��*/
int start();
int _change_picture(IMAGE* img/*ͼƬָ��*/, int x_start, int y_start, int x_end,
	int y_end/*�ֱ��ǿ�ʼ�����꣬�����ʱ������*/, int dir/*ͼƬ�ƶ��ķ���һ���Ƕ�ֵ*/);
int _get_mouse_msg(MOUSECLICK* eventarray/*һ���ṹ�����飬ÿ������Ԫ�ش���¼�����Ĳ�������������������*/, int length/*���鳤��*/);
int shezhi();//�޸���Ϸ����;
int paihangbang();//��ȡ���а��ļ�����ʾ;
int rule();//��ȡ����ͼƬ����ʾ
int zairucundang();//����浵
int _read_memory(MEMORY* memo);//��ȡ�浵
int _display_text(MEMORY* memo, int num,MOUSECLICK*events);//��ʾ��浵��Ӧ��������Ϣ
int _delete_memory(MEMORY*memo, int select_memory,int num);//ɾ���浵							   
int _load_memory(MEMORY*memo);//�Ѵ浵��Ϣ���ص�ȫ�ֱ�����

/*�ѶȺ͵�ͼѡ��*/
int _map_degree();
int mode1();//ս��ģʽ����
int mode2();//����ģʽ����
int load_map(int select_map);//��ָ���ĵ�ͼ���ݼ��ص���ͼ������
int set_speed(int select_degree);	         //�����ٶȴ�С
int initdata();											 //��Ϸ���ݳ�ʼ��

/*��Ϸ�����ʼ��*/
int initgame();

/*��Ļˢ��*/
int paint();
int paint_food(int *food,int food_r,int color);//��ʳ��

/*ʳ���ж�*/
int _food_judge();
int* _meet_circle(int *food, float x, float y, int food_r, int snake_r);
															//�ж�x��y���뾶Ϊsnake_r��Բ�Ƿ���food������İ뾶Ϊfood_r��Բ������ײ
int _food_create(int * meet,int r);//����ʳ�����meet�������������Ԫ����
int addsnake();		//�߳�һ��
int _half();		//��ըһ��
int _herb();		//����ai����ģʽ
int _poison();		//���ƶ��ݵ���״������

/*�����ж�*/
int _death_judge();
int _meet_line(int circlex, int circley, int r, int x1, int y1, int x2, int y2);//���һ��Բ�Ƿ���һ��ֱ���ཻ
int _duang(int *p, int circle_x, int circle_y, int r);							//���Բ�Ƿ���һ������η�����ײ
int wall_check(int circle_x, int circle_y, int r);								//���һ��Բ�Ƿ����ϰ��﷢����ײ

/*�ٶȵ���*/
int addspeed();



/*�ؿ��ж�*/
int _level();

/*������Ļ*/
int clear();

/*�ƶ�*/
int move();
int _up();//������
int _down();//������
int _left();//������
int _right();//������

/*��ͣ*/
int pause();
int _get_name(char*name, int *signal);//�õ�������ַ���
int _set_memory(char*name, int *signal);//��*signalΪ��,������Ϊname�Ĵ浵

/*��Ϸ����*/
int end();
int end_select();
int setrecord();
int loadpaihang();//�������а��ļ�