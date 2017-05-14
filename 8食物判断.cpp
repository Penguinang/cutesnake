#include"ͷ�ļ�.h"
#include"�궨��.h"
#include"�ṹ��.h"
#include"���к�������.h"
#include"ȫ�ֱ���������д��������Ҫ�ļ���.h"

/*ʳ���жϣ�
		*/
int _food_judge()
{
	
	score += degree;
	PoisonTimer += realT;
	int *meet;
	if ((meet = _meet_circle(*fruit, head->x, head->y, FRUITR, R)) != 0) {
		_playsound("fruit");
		addsnake();
		score += 1000;//��һ��ʳ���1000��
		commonT -= 50*DT;
		_food_create(meet,FRUITR);
		return 1;
	}
	if ((meet = _meet_circle(*bomb, head->x, head->y, FRUITR, R)) != 0) {
		_playsound("bomb");
		_half();
		_food_create(meet,BOMBR);
		return 1;
	}
	if (_meet_circle(*herb, head->x, head->y, FRUITR, R)) {
		_playsound("herb");
		_herb();//�ͱ��ʳ�ﲻͬ���ǻ۲ݱ�����֮�󲢲�����������
		return 1;
	}
	if (PoisonTimer>=SAFETIME) {
		_poison();
		return 1;
	}

	return 1;
}

/*���һ��Բ��û������һ��Բ��ײ����Ҫ��������߳�ʳ���ʳ�����������*/
int* _meet_circle(int *food, float x, float y, int food_r, int snake_r) {
														//���x��y���뾶Ϊsnake_r��Բ�Ƿ���food������İ뾶Ϊfood_r��Բ������ײ
	int*p = food;
	int i;

	/*p�����α꣬ÿ��ѭ����ʼʱ��pָ��fruit[x][0],��ĳ��fruit�ĺ����꣬�������ͷ�ڵ���ĳ��fruit��Բ�ľ���С��һ��ֵ�������Ƿ�����ײ��
	��ô�� p ����ָ�ظ�fruit�ĺ����꣬����p���� 
			ѭ����ֹ��������������һ�� *p ��0��������ʳ�ﶼ�Ѿ�����ˣ����� i ==10 ������������Ԫ�ض�����ˣ���ָֹ����������ַ*/
	for (i=1; *p != 0&&i<=10; p += 2,i++) {
		if (pow(*p - x, 2) + pow(*(p + 1) - y, 2) < pow(food_r + snake_r, 2))
			return p;
	}
	return 0;//return 0 ����û����ײ
}

/*�߳�һ��*/
int addsnake()
{

	SNAKE*p2;
	p2 = (SNAKE*)malloc(sizeof(SNAKE));

	p2->preview = tail;
	p2->next = 0;
	tail->next = p2;
	p2->order = tail->order + 1;
	tail = p2;

	return 1;
}

/*��ըһ��*/
int _half()
{
	SNAKE*p,*p2;

	if (tail->order == 1)
		gameRes = -1;
	else {
		for (p = tail->preview,p2 = p->preview; p->order > tail->order / 2; p2 = p2-> preview)//����ߵ�һ�봦�ĵ�ַ
		{
			free(p);
			p = p2;
		}
		free(tail);
		tail = p;
		tail->next = 0;
	}

	return 1;
}

/*����ʳ��*/
int _food_create(int * meet,int r) {

	srand(clock());
	int x , y;
	do {

		srand(rand());
		x = rand() % (800 - 2 * r) +r;
		srand(rand());
		y = rand() % (600 - 2 * r) + r;

	} while (_meet_circle(*fruit, x, y, FRUITR, r) || _meet_circle(*bomb, x, y, BOMBR, r) || 
		_meet_circle(*herb, x, y, HERBR, r) || _meet_circle(*poison, x, y, POISONR, r)|| wall_check(x, y, r));//�����е�ʳ�ﶼ����ײ

	*meet = x;
	*(meet + 1) = y;
	return 1;
}

/*����ai����ģʽ*/
int _herb()
{
	ai = 1;
	HerbTimer = time(NULL);//���´�ʱʱ��
	return 1;
}

/*���ƶ��ݵ���״������*/
int _poison()
{
	int *p = *poison,i;
	SNAKE *ps=tail;
	int *meet;

	/*�������ʱ�����*/
	if (PoisonTimer >= DANGERTIME)
	{
		PoisonTimer = 0;//���¼�ʱ���ظ�����
		for (i = 1; i <= poisonNum; i++, p +=2)
			*p=0;

		return 1;
	}

	/*�Զ��ݣ����һ��*/
	if (meet=_meet_circle(*poison, head->x, head->y, FRUITR, POISONR)) 
	{
		_playsound("poison");
		if (LENGTH == 1)
		{
			gameRes = -1;
			return 1;
		}
			
		else 
		{
			/*�߼�һ��*/
			tail = ps->preview;
			tail->next = 0;
			free(ps);
			/*�������ɶ���*/
			_food_create(meet,POISONR);
		}
		
	}
	
	/*��û�гԶ��ݣ����ڶ���ʱ����*/
	if (**poison == 0)//���û�ж��ݣ��ͳ�ʼ�����ݣ���������
	{
		for(i=1;i<=poisonNum;i++,p+=2)
			_food_create(p,POISONR);
	}
	return 1;
}