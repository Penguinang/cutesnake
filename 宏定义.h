#pragma once


#define R 10//蛇的每个节点半径
#define PI 3.1415927
#define DEGREE PI/180//一度
#define DX 15//DX-->蛇每次移动的距离,也是每两个节点圆心的距离；
#define B 30//贝塔-->蛇的最小转角，单位为度；
//蛇移动的切向速度为 v =DX/realT; 转弯半径为 r=(DX/2)/(tan(B/2))
//当前是v=0.1个单位，r=13.0个单位
///////////////////////////////////
//		DX		R		B		v		r
//		15		10		30		0.1		13.0
//		10		8		20		0.1		13.7
//
//
//		  0.073        20.52

#define BKCOLOR RGB(233,236,243)
#define COLOR_1 RGB(0,159,232)
#define COLOR_2 WHITE
#define LINE_COLOR RGB(205, 208, 215)

/*各种食物的大小，水果、智慧草、炸弹的大小是固定的，毒草的大小是可变的*/
#define FRUITR 5//一个食物的半径
#define HERBR 20//一个智慧草的半径
#define BOMBR 15//一个炸弹的半径
#define POISONR 5//毒草的最大半径
#define SAFETIME 15000//安全时间，在安全时间内不会有毒药，也就是毒药每隔安全时间出现一次
#define DANGERTIME 30000//危险事件，在危险时间内，安全时间外会出现毒草，所以整个到的周期是DANGERTIME

#define LEFT  0x4B00
#define RIGHT 0x4D00
#define UP    0x4800
#define DOWN  0x5000
#define ESC   0x011B
#define ENTER 0x1C0D

#define WIDTH 800
#define HEIGHT 600

#define LENGTH tail->order

#define RUSHT 50