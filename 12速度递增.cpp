#include"ͷ�ļ�.h"
#include"�궨��.h"
#include"�ṹ��.h"
#include"���к�������.h"
#include"ȫ�ֱ���������д��������Ҫ�ļ���.h"

int addspeed()
{
	commonT -= DT*(commonT-40)*0.01;
	if (commonT <= 40)
		commonT = 40;
	realT = commonT;
	return 1;
}