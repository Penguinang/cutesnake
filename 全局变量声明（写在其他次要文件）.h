#pragma once


/*记录游戏的结果状态，值为0表示按ESC键退出；-1表示游戏失败；1表示游戏胜利*/
extern int gameRes;
/*记录游戏分数*/
extern int score;
/*记录游戏关卡*/
extern int level;
/*游戏模式   1-->战役      2-->生存*/
extern int mode;
/*小蛇此时在坐标系中的方向，是一个角度值*/
extern int direction;

//定义头部结构体
extern struct SNAKE snake_head;
//分别定义一个头指针和尾指针
extern struct SNAKE* head, *tail;

/*用数组定义各种食物,为了统一操作，使用相同的函数，我将他们的数组长度全部设为一样*/
extern int fruit[10][2];//水果，吃一个长一节
extern int bomb[10][2];//炸弹，吃一个身体炸一半
extern int herb[10][2];//智慧草,吃了后在一段时间内可以自己走
extern int poison[10][2];//毒草，吃了缩短一截
/*各种食物的大小，水果、智慧草、炸弹的大小是固定的，毒草的大小是可变的*/
extern int poison_color_h;//毒草大小随时间改变，实现闪烁的效果
extern int fruitNum;//水果数量
extern int poisonNum;//毒草数量
extern int bombNum;//炸弹数量
extern int ai;//ai的状态，1是开启，0关闭

extern int map[21][11][2];							//用来存放障碍物。障碍物用多边形描述，二维数组的第一个元素是多边形边数，
															//第一个二维数组存地图的各种属性，其他二维数组一共最多可以放20个多边形
															//多边形用10个一维数组表示，每个一维数组存储一个点。

extern long int HerbTimer, PoisonTimer;//两个定时器，分别计算智慧草的时间和毒草的时间

extern int degree;//难度等级


 /*屏幕暂停的时间，我通过改变 T 改变速度：
		 v = DX / T ,其中 DX 是一个宏，在程序运行时是不变的；
		 每一关都以较慢的速度开始，高难度的关卡会有较高的时间增量*/
extern float T0;         //每一关T的初始值
extern float DT;		  //每活一次T的增量
/*关于实际值与一般值：
			  一般情况下，实际值就会是一般值，但若按下加速键时，T不会是实际值，而是冲刺值，即RUSHT*/
extern float realT;      //T的实际操作值
extern float commonT;	  //T的一般值

extern int music;//控制音乐是否播放
extern int sound;//控制音效播放