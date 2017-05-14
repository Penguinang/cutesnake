#include"头文件.h"
#include"宏定义.h"
#include"结构体.h"
#include"所有函数声明.h"
#include"全局变量声明（写在其他次要文件）.h"

/*食物判断：
		*/
int _food_judge()
{
	
	score += degree;
	PoisonTimer += realT;
	int *meet;
	if ((meet = _meet_circle(*fruit, head->x, head->y, FRUITR, R)) != 0) {
		_playsound("fruit");
		addsnake();
		score += 1000;//吃一个食物加1000分
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
		_herb();//和别的食物不同，智慧草被吃了之后并不会立即再生
		return 1;
	}
	if (PoisonTimer>=SAFETIME) {
		_poison();
		return 1;
	}

	return 1;
}

/*检测一个圆有没有与另一个圆碰撞，主要用来检测蛇吃食物，和食物再生的情况*/
int* _meet_circle(int *food, float x, float y, int food_r, int snake_r) {
														//检测x，y处半径为snake_r的圆是否与food数组里的半径为food_r的圆发生碰撞
	int*p = food;
	int i;

	/*p用作游标，每次循环开始时，p指向fruit[x][0],即某个fruit的横坐标，如果发现头节点与某个fruit的圆心距离小于一定值，即他们发生碰撞，
	那么将 p 重新指回该fruit的横坐标，并将p返回 
			循环终止的条件有两个，一是 *p 是0，即所有食物都已经检测了；二是 i ==10 ，即所有数组元素都检测了，防止指针读到随机地址*/
	for (i=1; *p != 0&&i<=10; p += 2,i++) {
		if (pow(*p - x, 2) + pow(*(p + 1) - y, 2) < pow(food_r + snake_r, 2))
			return p;
	}
	return 0;//return 0 代表没有碰撞
}

/*蛇长一节*/
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

/*蛇炸一半*/
int _half()
{
	SNAKE*p,*p2;

	if (tail->order == 1)
		gameRes = -1;
	else {
		for (p = tail->preview,p2 = p->preview; p->order > tail->order / 2; p2 = p2-> preview)//获得蛇的一半处的地址
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

/*再生食物*/
int _food_create(int * meet,int r) {

	srand(clock());
	int x , y;
	do {

		srand(rand());
		x = rand() % (800 - 2 * r) +r;
		srand(rand());
		y = rand() % (600 - 2 * r) + r;

	} while (_meet_circle(*fruit, x, y, FRUITR, r) || _meet_circle(*bomb, x, y, BOMBR, r) || 
		_meet_circle(*herb, x, y, HERBR, r) || _meet_circle(*poison, x, y, POISONR, r)|| wall_check(x, y, r));//与所有的食物都不碰撞

	*meet = x;
	*(meet + 1) = y;
	return 1;
}

/*开启ai觉醒模式*/
int _herb()
{
	ai = 1;
	HerbTimer = time(NULL);//记下此时时间
	return 1;
}

/*控制毒草的形状和有无*/
int _poison()
{
	int *p = *poison,i;
	SNAKE *ps=tail;
	int *meet;

	/*如果毒草时间结束*/
	if (PoisonTimer >= DANGERTIME)
	{
		PoisonTimer = 0;//重新计时，重复周期
		for (i = 1; i <= poisonNum; i++, p +=2)
			*p=0;

		return 1;
	}

	/*吃毒草，会减一节*/
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
			/*蛇减一节*/
			tail = ps->preview;
			tail->next = 0;
			free(ps);
			/*重新生成毒草*/
			_food_create(meet,POISONR);
		}
		
	}
	
	/*既没有吃毒草，又在毒草时间内*/
	if (**poison == 0)//如果没有毒草，就初始化毒草，产生毒草
	{
		for(i=1;i<=poisonNum;i++,p+=2)
			_food_create(p,POISONR);
	}
	return 1;
}