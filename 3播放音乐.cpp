#include"头文件.h"
#include"宏定义.h"
#include"结构体.h"
#include"所有函数声明.h"
#include"全局变量声明（写在其他次要文件）.h"

/*播放BGM:
		逻辑是		若果当前BGM的状态不是正在播放，就重新打开BGM，播放*/
int _playmusic(LPSTR wav)
{
	if (!music)//如果音乐没有打开，就不播放音乐，直接跳过
		return 0;
	/*播放BGM*/
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
		mciSendString(_T("close BGM"), 0, 0, 0);//先关掉BGM
		/*播放胜利时的音乐*/
		if(wav=="win")
		{
			mciSendString(_T("close win"), 0, 0, 0);
			mciSendString(_T("open wav/胜利.wav alias win"), 0, 0, 0);
			mciSendString(_T("play win"), 0, 0, 0);
			return 1;
		}
		/*播放过关时的音乐*/
		if (wav == "pass")
		{
			mciSendString(_T("close pass"), 0, 0, 0);
			mciSendString(_T("open wav/pass.wav alias pass"), 0, 0, 0);
			mciSendString(_T("play pass"), 0, 0, 0);
			return 1;
		}
		/*播放死亡的音乐*/
		if (wav == "end")
		{
			mciSendString(_T("close end"), 0, 0, 0);
			mciSendString(_T("open wav/死了.wav alias end"), 0, 0, 0);
			mciSendString(_T("play end"), 0, 0, 0);
			return 1;
		}
	}
	

	return 1;
}

/*播放音效*/
int _playsound(LPSTR wav)
{
	if (!sound)//音效没有开启时，就直接跳过
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