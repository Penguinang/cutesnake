#include"ͷ�ļ�.h"
#include"�궨��.h"
#include"�ṹ��.h"
#include"���к�������.h"
#include"ȫ�ֱ���������д��������Ҫ�ļ���.h"

/*����BGM:
		�߼���		������ǰBGM��״̬�������ڲ��ţ������´�BGM������*/
int _playmusic(LPSTR wav)
{
	if (!music)//�������û�д򿪣��Ͳ��������֣�ֱ������
		return 0;
	/*����BGM*/
	if(wav=="BGM")
	{
		char buf[10];
		mciSendString(_T("status BGM mode"), buf, 10, 0);
		if (strcmp(buf, "playing"))
		{

			mciSendString(_T("close BGM"), 0, 0, 0);
			mciSendString(_T("open wav/bg.mp3 alias BGM"), 0, 0, 0);
			mciSendString(_T("play BGM"), 0, 0, 0);
		}
	}
	else
	{
		mciSendString(_T("close BGM"), 0, 0, 0);//�ȹص�BGM
		/*����ʤ��ʱ������*/
		if(wav=="win")
		{
			mciSendString(_T("close win"), 0, 0, 0);
			mciSendString(_T("open wav/ʤ��.wav alias win"), 0, 0, 0);
			mciSendString(_T("play win"), 0, 0, 0);
			return 1;
		}
		/*���Ź���ʱ������*/
		if (wav == "pass")
		{
			mciSendString(_T("close pass"), 0, 0, 0);
			mciSendString(_T("open wav/pass.wav alias pass"), 0, 0, 0);
			mciSendString(_T("play pass"), 0, 0, 0);
			return 1;
		}
		/*��������������*/
		if (wav == "end")
		{
			mciSendString(_T("close end"), 0, 0, 0);
			mciSendString(_T("open wav/����.wav alias end"), 0, 0, 0);
			mciSendString(_T("play end"), 0, 0, 0);
			return 1;
		}
	}
	

	return 1;
}

/*������Ч*/
int _playsound(LPSTR wav)
{
	if (!sound)//��Чû�п���ʱ����ֱ������
		return 0;
	if (wav == "fruit")
	{
		mciSendString(_T("close fruit"), 0, 0, 0);
		mciSendString(_T("open wav/fruit.wav alias fruit"), 0, 0, 0);
		mciSendString(_T("play fruit"), 0, 0, 0);
		return 1;
	}

	if (wav == "bomb")
	{
		mciSendString(_T("close bomb"), 0, 0, 0);
		mciSendString(_T("open wav/bomb.wav alias bomb"), 0, 0, 0);
		mciSendString(_T("play bomb"), 0, 0, 0);
		return 1;
	}

	if (wav == "herb")
	{
		mciSendString(_T("close herb"), 0, 0, 0);
		mciSendString(_T("open wav/herb.wav alias herb"), 0, 0, 0);
		mciSendString(_T("play herb"), 0, 0, 0);
		return 1;
	}

	if (wav == "poison")
	{
		mciSendString(_T("close poison"), 0, 0, 0);
		mciSendString(_T("open wav/poison.wav alias poison"), 0, 0, 0);
		mciSendString(_T("play poison"), 0, 0, 0);
		return 1;
	}
		

	return 1;
}