#pragma once

struct SNAKE
{
	int x;
	int y;
	int order;
	SNAKE* preview;
	SNAKE* next;

};
struct MOUSECLICK
{
	/*左上角坐标*/
	int x1;
	int y1;
	/*右下角坐标*/
	int x2;
	int y2;
	int value;
};
struct PAIHANG
{
	int mode;
	int score;
	char name[20];
	int level;
	int length;
};

struct MEMORY
{
	char name[20];
	int mode;
	int score;
	int level;
	int degree; 
	int direction;
	int snake[100][2];
	int fruit[10][2];
	int bomb[10][2];
	int herb[10][2];
	int poison[10][2] ;
	float commonT;
	int poisonR;
	long int PoisonTimer;
	long int HerbTimer;
	int ai;
};