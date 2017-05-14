#pragma once


/*��¼��Ϸ�Ľ��״̬��ֵΪ0��ʾ��ESC���˳���-1��ʾ��Ϸʧ�ܣ�1��ʾ��Ϸʤ��*/
extern int gameRes;
/*��¼��Ϸ����*/
extern int score;
/*��¼��Ϸ�ؿ�*/
extern int level;
/*��Ϸģʽ   1-->ս��      2-->����*/
extern int mode;
/*С�ߴ�ʱ������ϵ�еķ�����һ���Ƕ�ֵ*/
extern int direction;

//����ͷ���ṹ��
extern struct SNAKE snake_head;
//�ֱ���һ��ͷָ���βָ��
extern struct SNAKE* head, *tail;

/*�����鶨�����ʳ��,Ϊ��ͳһ������ʹ����ͬ�ĺ������ҽ����ǵ����鳤��ȫ����Ϊһ��*/
extern int fruit[10][2];//ˮ������һ����һ��
extern int bomb[10][2];//ը������һ������ըһ��
extern int herb[10][2];//�ǻ۲�,���˺���һ��ʱ���ڿ����Լ���
extern int poison[10][2];//���ݣ���������һ��
/*����ʳ��Ĵ�С��ˮ�����ǻ۲ݡ�ը���Ĵ�С�ǹ̶��ģ����ݵĴ�С�ǿɱ��*/
extern int poison_color_h;//���ݴ�С��ʱ��ı䣬ʵ����˸��Ч��
extern int fruitNum;//ˮ������
extern int poisonNum;//��������
extern int bombNum;//ը������
extern int ai;//ai��״̬��1�ǿ�����0�ر�

extern int map[21][11][2];							//��������ϰ���ϰ����ö������������ά����ĵ�һ��Ԫ���Ƕ���α�����
															//��һ����ά������ͼ�ĸ������ԣ�������ά����һ�������Է�20�������
															//�������10��һά�����ʾ��ÿ��һά����洢һ���㡣

extern long int HerbTimer, PoisonTimer;//������ʱ�����ֱ�����ǻ۲ݵ�ʱ��Ͷ��ݵ�ʱ��

extern int degree;//�Ѷȵȼ�


 /*��Ļ��ͣ��ʱ�䣬��ͨ���ı� T �ı��ٶȣ�
		 v = DX / T ,���� DX ��һ���꣬�ڳ�������ʱ�ǲ���ģ�
		 ÿһ�ض��Խ������ٶȿ�ʼ�����ѶȵĹؿ����нϸߵ�ʱ������*/
extern float T0;         //ÿһ��T�ĳ�ʼֵ
extern float DT;		  //ÿ��һ��T������
/*����ʵ��ֵ��һ��ֵ��
			  һ������£�ʵ��ֵ�ͻ���һ��ֵ���������¼��ټ�ʱ��T������ʵ��ֵ�����ǳ��ֵ����RUSHT*/
extern float realT;      //T��ʵ�ʲ���ֵ
extern float commonT;	  //T��һ��ֵ

extern int music;//���������Ƿ񲥷�
extern int sound;//������Ч����