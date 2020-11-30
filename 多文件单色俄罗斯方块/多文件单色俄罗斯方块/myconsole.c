#include<time.h>
#include<windows.h>
#include"myconsole.h"
long time1, time2;
/****************************************
* 确定屏幕光标位置
****************************************/
void GotoXY(int x, int y)
{
    COORD pos;
    pos.X = x;//横坐标
    pos.Y = y;//纵坐标
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
/****************************************
* 隐藏屏幕光标
****************************************/
void HideCursor()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
    CursorInfo.bVisible = 0; //隐藏控制台光标
    SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}
/****************************************
* 音乐打开并播放函数
****************************************/
void PlayMusic()
{
    mciSendString(TEXT("open D:\\Music\\甩葱歌.mp3 alias Song1"), NULL, 0, NULL);
    mciSendString(TEXT("play Song1 repeat"), NULL, 0, NULL);
}
/****************************************
* 音乐重新播放函数
****************************************/
void RestartMusic()
{
    mciSendString(TEXT("resume Song1"), NULL, 0, NULL);
}
/****************************************
* 音乐暂停播放函数
****************************************/
void PauseMusic()
{
    mciSendString(TEXT("pause Song1"), NULL, 0, NULL);
}