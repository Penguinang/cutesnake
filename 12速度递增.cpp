#include"头文件.h"
#include"宏定义.h"
#include"结构体.h"
#include"所有函数声明.h"
#include"全局变量声明（写在其他次要文件）.h"

int addspeed()
{
	commonT -= DT*(commonT-40)*0.01;
	if (commonT <= 40)
		commonT = 40;
	realT = commonT;
	return 1;
}