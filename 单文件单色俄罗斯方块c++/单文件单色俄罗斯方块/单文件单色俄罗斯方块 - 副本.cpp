#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <Mmsystem.h>
using namespace std;
#pragma comment(lib,"winmm.lib")
#define FrameX  16    //游戏窗口左上角的X轴坐标
#define FrameY  4  //游戏窗口左上角的Y轴坐标
#define height  20 //游戏窗口的高度
#define width   10//游戏窗口的宽度
#define StartX  1+width/2//俄罗斯方块中心出现位置横坐标 
#define StartY  2//俄罗斯方块中心出现位置纵坐标

//俄罗斯方块生成数组 
//■*********■*********■**************■■*******■■***■■
//■■■***■■■***■■■***■■■■*****■■***■■*****■■
int tetris_data[7][4][5][5] = {
    {
        { { 0, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0 }, { 0, 1, 1, 1, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 1, 1, 1, 0 }, { 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 0, 0, 0 } }
    },
    {
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 1, 1, 1, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 1, 1, 1, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } }
    },
    {
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0 }, { 0, 1, 1, 1, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 1, 1, 1, 0 }, { 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } }
    },
    {
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 1, 1, 1, 1 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 1, 1, 1, 1 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 } }
    },
    {
        { { 0, 0, 0, 0, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } },
    },
    {
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 0 } },
    },
    {
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 } }
    }
};

class Tetris_Data
{
    friend class BackGround;
    friend class Env;
    friend class Logic;
    friend void Welcom(class Tetris_Data &data);
    friend void Welcom(class Tetris_Data &data);
    friend void GamePlay(class Tetris_Data &data);
public:
    Tetris_Data()
        :kind_current(0), state_current(0), kind_next(0), state_next(0)
        , left(1), right(1), down(1), trans(1), X(StartX), Y(StartY)
        , time1(0), time2(0), Line(0), Level(1), Score(0), Music(1)
    {
        int i = 0, j = 0;
        for (i = 0; i < height + 2; i++)
            for (j = 0; j < width + 2; j++)
                a[height + 2][width + 2] = 0;
    }
  
protected:
    //属性参数
    int kind_current = 0;//当前方块种类
    int state_current = 0;//当前方块状态
    int kind_next = 0;//下一方块种类
    int state_next = 0;//下一方块状态
    int left = 1;//1为可左移，0为不可左移 
    int right = 1;//1为可右移，0为不可右移
    int down = 1;//1为可下移，0为不可下移
    int trans = 1;//1为可旋转，0为不可旋转 
    int X = StartX;//中心方块横坐标
    int Y = StartY;//中心方块纵坐标
    //环境参数
    long time1 = 0;
    long time2 = 0;
    int Line = 0;//消除的行数 
    int Level = 1;//等级
    int Score = 0;//积分
    int Music = 1;
    int a[height + 2][width + 2];//俄罗斯方块数据数组
};

class Tetris_Method :public BackGround, public Env, public Logic
{};

class BackGround
{
    friend class Env;
    friend class Logic;
public:
    virtual void DrwaGameframe(class Tetris_Data &data);/*打印俄罗斯方块边框*/
    virtual void FacePlate();/*游戏开始界面*/
    virtual void GameOver(class Tetris_Data &data);/*游戏结束界面*/
    virtual void Explation(class Tetris_Data &data);/*游戏按键介绍界面*/
    virtual void Regulation(class Tetris_Data &data);/*游戏规则介绍界面*/
};

class Env
{
    friend class BackGround;
    friend class Logic;
public:
    virtual void GotoXY(int x, int y);/*确定屏幕光标位置*/
    virtual void HideCursor();/*隐藏屏幕光标*/
    virtual void KeyControl(class Tetris_Data &data);/*键盘输入判定*/
    virtual void PlayMusic();/*音乐打开并播放函数*/
    virtual void RestartMusic();/*音乐重新播放函数*/
    virtual void PauseMusic();/*音乐暂停播放函数*/
};

class Logic
{
    friend class BackGround;
    friend class Env;
public:
    virtual void MakeTetris(class Tetris_Data &data);/*生成俄罗斯方块*/
    virtual void PrintTetris(class Tetris_Data &data);/*打印出俄罗斯方块*/
    virtual void CleanOld(class Tetris_Data &data);/*清除旧的俄罗斯方块*/
    virtual void DrawNew(class Tetris_Data &data);/*打印新的俄罗斯方块*/
    virtual void Transform(class Tetris_Data &data);/*旋转俄罗斯方块*/
    virtual void Judge_MoveAndTansform(class Tetris_Data &data);/*判断俄罗斯方块是否可移动和变形*/
    virtual void PrintNextTetris(class Tetris_Data &data);/*打印下一个俄罗斯方块*/
    virtual void CleanLine(class Tetris_Data &data);/*清除满行*/
    virtual void AutoDown(class Tetris_Data &data);/*自动下落函数*/
};

/*****************************************父类BackGround*****************************************/
/****************************************
* 打印俄罗斯方块边框
****************************************/
void BackGround::DrwaGameframe(class Tetris_Data &data)
{
    int i = 0;
    GotoXY(FrameX + width - 5, FrameY - 2);
    cout << "俄 罗 斯 方 块";
    for (i = 1; i <= width; i++)
    {
        GotoXY(FrameX + 2 * i, FrameY);//打印上横框
        cout << "■";
        GotoXY(FrameX + 2 * i, FrameY + height + 1);//打印下横框
        cout << "■";
        data.a[height + 1][i] = 1;
    }
    for (i = 0; i <= height + 1; i++)
    {
        GotoXY(FrameX, FrameY + i);//打印左竖框
        cout << "■";
        GotoXY(FrameX + 2 * width + 2, FrameY + i);//打印右竖框
        cout << "■";
        data.a[i][0] = 1;
        data.a[i][width + 1] = 1;
    }
    GotoXY(FrameX + 2 * width + 8, FrameY - 1);
    cout << "Level:" << data.Level;
    GotoXY(FrameX + 2 * width + 8, FrameY + 1);
    cout << "积分:" << data.Score;
    GotoXY(FrameX + 2 * width + 8, FrameY + 3);
    cout << "消去的行数:%d", data.Line;
}
/****************************************
* 游戏开始界面
****************************************/
void BackGround::FacePlate()
{
    cout << "\n\n\n";
    cout << "                           俄  罗  斯  方  块             \n";
    cout << "\n\n";
    cout << "                  ■                         ■           \n";
    cout << "                  ■■   ■■       ■■     ■         ■\n";
    cout << "                  ■       ■■     ■■     ■     ■■■\n";
    cout << "                                             ■           \n";
    cout << "\n\n";
    cout << "                         1.开始游戏   2.按键说明          \n";
    cout << "\n\n";
    cout << "                         3.游戏规则   4.退出游戏          \n";
    cout << "\n\n";
    cout << "                           请选择[1 2 3 4]:";
}
/****************************************
* 游戏结束界面
****************************************/
void BackGround::GameOver(class Tetris_Data &data)
{
    int n;
    system("cls");
    cout << "\n\n\n\n\n\n\n\n";
    cout << "          ■■■      ■       ■    ■   ■■■■        ■■    ■      ■ ■■■■   ■■■  \n";
    cout << "        ■           ■■     ■ ■■ ■  ■            ■    ■   ■    ■  ■         ■   ■ \n";
    cout << "        ■   ■■   ■  ■   ■   ■   ■ ■■■       ■      ■   ■  ■   ■■■     ■■■  \n";
    cout << "        ■     ■  ■■■■  ■   ■   ■ ■            ■    ■     ■■    ■         ■   ■ \n";
    cout << "          ■■■  ■      ■ ■   ■   ■ ■■■■        ■■        ■     ■■■■   ■    ■\n";
    cout << "\n\n\n\n\n";
    cout << "                                       1:再玩一局          2:退出游戏                             ";
    cout << "\n\n";
    cout << "                                                 选择[1/2]:";
    scanf("%d", &n);
    switch (n)
    {
    case 1:GamePlay(data); break;
    case 2:exit(0); break;
    }
}
/****************************************
* 游戏按键介绍界面
****************************************/
void BackGround::Explation(class Tetris_Data &data)
{
    system("cls");
    cout << "\n\n\n";
    cout << "                                    按键说明                \n\n\n";
    cout << "                ************************************************\n";
    cout << "                *   tip1: 玩家可以通过 ← →方向键来移动方块   *\n";
    cout << "                *                                              *\n";
    cout << "                *   tip2: 通过 ↑使方块旋转                    *\n";
    cout << "                *                                              *\n";
    cout << "                *   tip3: 通过 ↓加速方块下落                  *\n";
    cout << "                *                                              *\n";
    cout << "                *   tip4: 按空格键暂停游戏，再按空格键继续     *\n";
    cout << "                *                                              *\n";
    cout << "                *   tip5: 按ESC退出游戏，按tab键暂停/播放音乐  *\n";
    cout << "                ************************************************\n";
    getch();//按任意键返回主界面
    system("cls");
    Welcom(data);
}
/****************************************
* 游戏规则介绍界面
****************************************/
void BackGround::Regulation(class Tetris_Data &data)
{
    system("cls");
    GotoXY(0, 3);
    cout << "                                         规则说明                     \n\n\n";
    cout << "                **********************************************************\n";
    cout << "                *   tip1: 不同形状的小方块从屏幕上方落下，玩家通过调整   *\n";
    cout << "                *         方块的位置和方向，使他们在屏幕底部拼出完整的   *\n";
    cout << "                *         一条或几条                                     *\n";
    cout << "                *                                                        *\n";
    cout << "                *   tip2: 每消除一行，积分增加100                        *\n";
    cout << "                *                                                        *\n";
    cout << "                *   tip3: 每累计1000分，会提升一个等级                   *\n";
    cout << "                *                                                        *\n";
    cout << "                *   tip4: 提升等级会使方块下落速度加快，游戏难度加大     *\n";
    cout << "                **********************************************************\n";
    getch();//按任意键返回主界面
    system("cls");
    Welcom(data);
}



/*****************************************父类Env*****************************************/
/****************************************
* 确定屏幕光标位置
****************************************/
void Env::GotoXY(int x, int y)
{
    COORD pos;
    pos.X = x;//横坐标
    pos.Y = y;//纵坐标
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
/****************************************
* 隐藏屏幕光标
****************************************/
void Env::HideCursor()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
    CursorInfo.bVisible = 0; //隐藏控制台光标
    SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}
/****************************************
* 键盘输入判定
****************************************/
void Env::KeyControl(class Tetris_Data &data)
{
    int i = 0, j = 0, ch = 0;
    if (_kbhit())
    {
        ch = getch();
        Judge_MoveAndTansform(data);
        switch (ch)
        {
        case 72:if (data.trans){ CleanOld(data); Transform(data); DrawNew(data); }break;//变形
        case 75:if (data.left){ CleanOld(data); data.X--; DrawNew(data); }break;//向上
        case 77:if (data.right){ CleanOld(data); data.X++; DrawNew(data); }break;//->向右
        case 80:if (data.down){ CleanOld(data); data.Y++; DrawNew(data); }break;//向下
        case 32:getch(); break;//空格键 暂停游戏
        case 9: data.Music = -data.Music;
            if (data.Music > 0)RestartMusic();
            else RestartMusic(); break;//tap键 暂停歌曲
        case 27:system("cls"); exit(0); break;//ESC键 退出 
        default:break;
        }
    }
}
/****************************************
* 音乐打开并播放函数
****************************************/
void Env::PlayMusic()
{
    mciSendString(TEXT("open D:\\Music\\甩葱歌.mp3 alias Song1"), NULL, 0, NULL);
    mciSendString(TEXT("play Song1 repeat"), NULL, 0, NULL);
}
/****************************************
* 音乐重新播放函数
****************************************/
void Env::RestartMusic()
{
    mciSendString(TEXT("resume Song1"), NULL, 0, NULL);
}
/****************************************
* 音乐暂停播放函数
****************************************/
void Env::PauseMusic()
{
    mciSendString(TEXT("pause Song1"), NULL, 0, NULL);
}
/*****************************************父类Logic*****************************************/
/****************************************
* 生成俄罗斯方块
****************************************/
void Logic::MakeTetris(class Tetris_Data &data)
{
    srand(time(NULL));
    data.kind_current = data.kind_next;
    data.state_current = data.state_next;
    data.kind_next = rand() % 7;
    data.state_next = rand() % 4;
}
/****************************************
* 打印出俄罗斯方块
****************************************/
void Logic::PrintTetris(class Tetris_Data &data)
{
    int i = 0, j = 0;
    for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
        data.a[data.Y - 2 + i][data.X - 2 + j] += tetris_data[data.kind_current][data.state_current][i][j];
    for (i = 1; i <= height; i++)
    {
        GotoXY(FrameX + 2, FrameY + i);
        for (j = 1; j <= width; j++)
        if (data.a[i][j])cout << "■";
        else cout << "  ";
    }
}
/****************************************
* 清除旧的俄罗斯方块
****************************************/
void Logic::CleanOld(class Tetris_Data &data)
{
    int i = 0, j = 0;
    for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
    if (tetris_data[data.kind_current][data.state_current][i][j])
    {
        data.a[data.Y - 2 + i][data.X - 2 + j] = 0;
        GotoXY(FrameX + 2 * data.X - 4 + 2 * j, FrameY + data.Y - 2 + i);
        cout << "  ";
    }
}
/****************************************
* 打印新的俄罗斯方块
****************************************/
void Logic::DrawNew(class Tetris_Data &data)
{
    int i = 0, j = 0;
    for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
    if (tetris_data[data.kind_current][data.state_current][i][j])
    {
        data.a[data.Y + i - 2][data.X + j - 2] = tetris_data[data.kind_current][data.state_current][i][j];
        GotoXY(FrameX + 2 * data.X - 4 + 2 * j, FrameY + data.Y - 2 + i);
        cout << "■";
    }
}
/****************************************
* 旋转俄罗斯方块
****************************************/
void Logic::Transform(class Tetris_Data &data)
{
    if (data.state_current != 3)data.state_current++;
    else data.state_current = 0;
}
/****************************************
* 判断俄罗斯方块是否可移动和变形
****************************************/
void Logic::Judge_MoveAndTansform(class Tetris_Data &data)
{
    int t;
    switch (data.kind_current)
    {
    case 0:
    case 1:
    case 2:t = 4 * data.kind_current + data.state_current + 1; break;
    case 3:
    case 4:
    case 5:t = 2 * data.kind_current + data.state_current % 2 + 7; break;
    case 6:t = 19; break;
    }
    switch (t)
    {
    case 1:
        if (data.a[data.Y - 1][data.X - 2] == 0 && data.a[data.Y][data.X - 2] == 0)data.left = 1; else data.left = 0;
        if (data.a[data.Y - 1][data.X] == 0 && data.a[data.Y][data.X + 2] == 0)data.right = 1; else data.right = 0;
        if (data.a[data.Y + 1][data.X - 1] == 0 && data.a[data.Y + 1][data.X] == 0 && data.a[data.Y + 1][data.X + 1] == 0)data.down = 1; else data.down = 0;
        if (data.a[data.Y - 1][data.X] == 0 && data.a[data.Y - 1][data.X + 1] == 0 && data.a[data.Y + 1][data.X] == 0)data.trans = 1; else data.trans = 0;
        break;
    case 2:
        if (data.a[data.Y - 1][data.X - 1] == 0 && data.a[data.Y][data.X - 1] == 0 && data.a[data.Y + 1][data.X - 1] == 0)data.left = 1; else data.left = 0;
        if (data.a[data.Y - 1][data.X + 2] == 0 && data.a[data.Y][data.X + 1] == 0 && data.a[data.Y + 1][data.X + 1] == 0)data.right = 1; else data.right = 0;
        if (data.a[data.Y + 2][data.X] == 0 && data.a[data.Y][data.X + 1] == 0)data.down = 1; else data.down = 0;
        if (data.a[data.Y][data.X - 1] == 0 && data.a[data.Y][data.X + 1] == 0 && data.a[data.Y + 1][data.X + 1] == 0)data.trans = 1; else data.trans = 0;
        break;
    case 3:
        if (data.a[data.Y][data.X - 2] == 0 && data.a[data.Y + 1][data.X] == 0)data.left = 1; else data.left = 0;
        if (data.a[data.Y][data.X + 2] == 0 && data.a[data.Y + 1][data.X + 2] == 0)data.right = 1; else data.right = 0;
        if (data.a[data.Y + 1][data.X - 1] == 0 && data.a[data.Y + 1][data.X] == 0 && data.a[data.Y + 2][data.X + 1] == 0)data.down = 1; else data.down = 0;
        if (data.a[data.Y - 1][data.X] == 0 && data.a[data.Y + 1][data.X - 1] == 0 && data.a[data.Y + 1][data.X] == 0)data.trans = 1; else data.trans = 0;
        break;
    case 4:
        if (data.a[data.Y - 1][data.X - 1] == 0 && data.a[data.Y][data.X - 1] == 0 && data.a[data.Y + 1][data.X - 2] == 0)data.left = 1; else data.left = 0;
        if (data.a[data.Y - 1][data.X + 1] == 0 && data.a[data.Y][data.X + 1] == 0 && data.a[data.Y + 1][data.X + 1] == 0)data.right = 1; else data.right = 0;
        if (data.a[data.Y + 2][data.X - 1] == 0 && data.a[data.Y + 2][data.X] == 0)data.down = 1; else data.down = 0;
        if (data.a[data.Y - 1][data.X - 1] == 0 && data.a[data.Y][data.X - 1] == 0 && data.a[data.Y][data.X + 1] == 0)data.trans = 1; else data.trans = 0;
        break;
    case 5:
        if (data.a[data.Y - 1][data.X - 1] == 0 && data.a[data.Y][data.X - 2] == 0)data.left = 1; else data.left = 0;
        if (data.a[data.Y - 1][data.X + 1] == 0 && data.a[data.Y][data.X + 2] == 0)data.right = 1; else data.right = 0;
        if (data.a[data.Y + 1][data.X - 1] == 0 && data.a[data.Y + 1][data.X] == 0 && data.a[data.Y + 1][data.X + 1] == 0)data.down = 1; else data.down = 0;
        if (data.a[data.Y + 1][data.X] == 0)data.trans = 1; else data.trans = 0;
        break;
    case 6:
        if (data.a[data.Y - 1][data.X - 1] == 0 && data.a[data.Y][data.X - 1] == 0 && data.a[data.Y + 1][data.X - 1] == 0)data.left = 1; else data.left = 0;
        if (data.a[data.Y - 1][data.X + 1] == 0 && data.a[data.Y][data.X + 2] == 0 && data.a[data.Y + 1][data.X + 1] == 0)data.right = 1; else data.right = 0;
        if (data.a[data.Y + 2][data.X] == 0 && data.a[data.Y + 1][data.X + 1] == 0)data.down = 1; else data.down = 0;
        if (data.a[data.Y][data.X - 1] == 0)data.trans = 1; else data.trans = 0;
        break;
    case 7:
        if (data.a[data.Y][data.X - 2] == 0 && data.a[data.Y + 1][data.X - 1] == 0)data.left = 1; else data.left = 0;
        if (data.a[data.Y][data.X + 2] == 0 && data.a[data.Y + 1][data.X + 1] == 0)data.right = 1; else data.right = 0;
        if (data.a[data.Y + 1][data.X - 1] == 0 && data.a[data.Y + 2][data.X] == 0 && data.a[data.Y + 1][data.X + 1] == 0)data.down = 1; else data.down = 0;
        if (data.a[data.Y - 1][data.X] == 0)data.trans = 1; else data.trans = 0;
        break;
    case 8:
        if (data.a[data.Y - 1][data.X - 1] == 0 && data.a[data.Y][data.X - 2] == 0 && data.a[data.Y + 1][data.X - 1] == 0)data.left = 1; else data.left = 0;
        if (data.a[data.Y - 1][data.X + 1] == 0 && data.a[data.Y][data.X + 1] == 0 && data.a[data.Y + 1][data.X + 1] == 0)data.right = 1; else data.right = 0;
        if (data.a[data.Y + 1][data.X - 1] == 0 && data.a[data.Y + 2][data.X] == 0)data.down = 1; else data.down = 0;
        if (data.a[data.Y][data.X + 1] == 0)data.trans = 1; else data.trans = 0;
        break;
    case 9:
        if (data.a[data.Y][data.X - 2] == 0 && data.a[data.Y - 1][data.X] == 0)data.left = 1; else data.left = 0;
        if (data.a[data.Y - 1][data.X + 2] == 0 && data.a[data.Y][data.X + 2] == 0)data.right = 1; else data.right = 0;
        if (data.a[data.Y + 1][data.X - 1] == 0 && data.a[data.Y + 1][data.X] == 0 && data.a[data.Y + 1][data.X + 1] == 0)data.down = 1; else data.down = 0;
        if (data.a[data.Y - 1][data.X] == 0 && data.a[data.Y + 1][data.X] == 0 && data.a[data.Y + 1][data.X + 1] == 0)data.trans = 1; else data.trans = 0;
        break;
    case 10:
        if (data.a[data.Y - 1][data.X - 1] == 0 && data.a[data.Y][data.X - 1] == 0 && data.a[data.Y + 1][data.X - 1] == 0)data.left = 1; else data.left = 0;
        if (data.a[data.Y - 1][data.X + 1] == 0 && data.a[data.Y][data.X + 1] == 0 && data.a[data.Y + 1][data.X + 2] == 0)data.right = 1; else data.right = 0;
        if (data.a[data.Y + 2][data.X] == 0 && data.a[data.Y + 2][data.X + 1] == 0)data.down = 1; else data.down = 0;
        if (data.a[data.Y][data.X - 1] == 0 && data.a[data.Y + 1][data.X - 1] == 0 && data.a[data.Y][data.X + 1] == 0)data.trans = 1; else data.trans = 0;
        break;
    case 11:
        if (data.a[data.Y][data.X - 2] == 0 && data.a[data.Y + 1][data.X - 2] == 0)data.left = 1; else data.left = 0;
        if (data.a[data.Y][data.X + 2] == 0 && data.a[data.Y + 1][data.X] == 0)data.right = 1; else data.right = 0;
        if (data.a[data.Y + 2][data.X - 1] == 0 && data.a[data.Y + 1][data.X] == 0 && data.a[data.Y + 1][data.X + 1] == 0)data.down = 1; else data.down = 0;
        if (data.a[data.Y - 1][data.X - 1] == 0 && data.a[data.Y - 1][data.X] == 0 && data.a[data.Y + 1][data.X] == 0)data.trans = 1; else data.trans = 0;
        break;
    case 12:
        if (data.a[data.Y - 1][data.X - 2] == 0 && data.a[data.Y][data.X - 1] == 0 && data.a[data.Y + 1][data.X - 1] == 0)data.left = 1; else data.left = 0;
        if (data.a[data.Y - 1][data.X + 1] == 0 && data.a[data.Y][data.X + 1] == 0 && data.a[data.Y + 1][data.X + 1] == 0)data.right = 1; else data.right = 0;
        if (data.a[data.Y][data.X - 1] == 0 && data.a[data.Y + 2][data.X] == 0)data.down = 1; else data.down = 0;
        if (data.a[data.Y - 1][data.X + 1] == 0 && data.a[data.Y][data.X - 1] == 0 && data.a[data.Y][data.X + 1] == 0)data.trans = 1; else data.trans = 0;
        break;
    case 13:
        if (data.a[data.Y][data.X - 2] == 0)data.left = 1; else data.left = 0;
        if (data.a[data.Y][data.X + 3] == 0)data.right = 1; else data.right = 0;
        if (data.a[data.Y + 1][data.X - 1] == 0 && data.a[data.Y + 1][data.X] == 0 && data.a[data.Y + 1][data.X + 1] == 0 && data.a[data.Y + 1][data.X + 2] == 0)data.down = 1; else data.down = 0;
        if (data.a[data.Y - 1][data.X] == 0 && data.a[data.Y + 1][data.X] == 0 && data.a[data.Y + 2][data.X] == 0)data.trans = 1; else data.trans = 0;
        break;
    case 14:
        if (data.a[data.Y - 1][data.X - 1] == 0 && data.a[data.Y][data.X - 1] == 0 && data.a[data.Y + 1][data.X - 1] == 0 && data.a[data.Y + 2][data.X - 1] == 0)data.left = 1; else data.left = 0;
        if (data.a[data.Y - 1][data.X + 1] == 0 && data.a[data.Y][data.X + 1] == 0 && data.a[data.Y + 1][data.X + 1] == 0 && data.a[data.Y + 2][data.X + 1] == 0)data.right = 1; else data.right = 0;
        if (data.a[data.Y + 3][data.X] == 0)data.down = 1; else data.down = 0;
        if (data.a[data.Y][data.X - 1] == 0 && data.a[data.Y][data.X + 1] == 0 && data.a[data.Y][data.X + 2] == 0)data.trans = 1; else data.trans = 0;
        break;
    case 15:
        if (data.a[data.Y - 1][data.X - 2] == 0 && data.a[data.Y][data.X - 1] == 0)data.left = 1; else data.left = 0;
        if (data.a[data.Y - 1][data.X + 1] == 0 && data.a[data.Y][data.X + 2] == 0)data.right = 1; else data.right = 0;
        if (data.a[data.Y][data.X - 1] == 0 && data.a[data.Y + 1][data.X] == 0 && data.a[data.Y + 1][data.X + 1] == 0)data.down = 1; else data.down = 0;
        if (data.a[data.Y - 1][data.X + 1] == 0 && data.a[data.Y + 1][data.X] == 0)data.trans = 1; else data.trans = 0;
        break;
    case 16:
        if (data.a[data.Y - 1][data.X] == 0 && data.a[data.Y][data.X - 1] == 0 && data.a[data.Y + 1][data.X - 1] == 0)data.left = 1; else data.left = 0;
        if (data.a[data.Y - 1][data.X + 2] == 0 && data.a[data.Y][data.X + 2] == 0 && data.a[data.Y + 1][data.X + 1] == 0)data.right = 1; else data.right = 0;
        if (data.a[data.Y + 2][data.X] == 0 && data.a[data.Y + 1][data.X + 1] == 0)data.down = 1; else data.down = 0;
        if (data.a[data.Y - 1][data.X - 1] == 0 && data.a[data.Y - 1][data.X] == 0)data.trans = 1; else data.trans = 0;
        break;
    case 17:
        if (data.a[data.Y - 1][data.X - 1] == 0 && data.a[data.Y][data.X - 2] == 0)data.left = 1; else data.left = 0;
        if (data.a[data.Y - 1][data.X + 2] == 0 && data.a[data.Y][data.X + 1] == 0)data.right = 1; else data.right = 0;
        if (data.a[data.Y + 1][data.X - 1] == 0 && data.a[data.Y + 1][data.X] == 0 && data.a[data.Y][data.X + 1] == 0)data.down = 1; else data.down = 0;
        if (data.a[data.Y][data.X + 1] == 0 && data.a[data.Y + 1][data.X + 1] == 0)data.trans = 1; else data.trans = 0;
        break;
    case 18:
        if (data.a[data.Y - 1][data.X - 1] == 0 && data.a[data.Y][data.X - 1] == 0 && data.a[data.Y + 1][data.X] == 0)data.left = 1; else data.left = 0;
        if (data.a[data.Y - 1][data.X + 1] == 0 && data.a[data.Y][data.X + 2] == 0 && data.a[data.Y + 1][data.X + 2] == 0)data.right = 1; else data.right = 0;
        if (data.a[data.Y + 1][data.X] == 0 && data.a[data.Y + 2][data.X + 1] == 0)data.down = 1; else data.down = 0;
        if (data.a[data.Y - 1][data.X + 1] == 0 && data.a[data.Y][data.X - 1] == 0)data.trans = 1; else data.trans = 0;
        break;
    case 19:
        if (data.a[data.Y][data.X - 1] == 0 && data.a[data.Y + 1][data.X - 1] == 0)data.left = 1; else data.left = 0;
        if (data.a[data.Y][data.X + 2] == 0 && data.a[data.Y + 1][data.X + 2] == 0)data.right = 1; else data.right = 0;
        if (data.a[data.Y + 2][data.X] == 0 && data.a[data.Y + 2][data.X + 1] == 0)data.down = 1; else data.down = 0;
        data.trans = 0;
        break;
    default:break;
    }
}


/****************************************
* 打印下一个俄罗斯方块
****************************************/
void Logic::PrintNextTetris(class Tetris_Data &data)
{
    int i = 0, j = 0;
    GotoXY(FrameX + 2 * width + 8, FrameY + 5);
    cout << "下一个方块:%2d" << data.kind_next;
    for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
    {
        GotoXY(FrameX + 2 * width + 2 * j + 8, FrameY + 6 + i);
        if (tetris_data[data.kind_next][data.state_next][i][j])printf("■");
        else printf("  ");
    }
}
/****************************************
* 清除满行
****************************************/
void Logic::CleanLine(class Tetris_Data &data)
{
    int i = height, j = 1, k = 0, sum = 0;
    for (i = height; i > 0; i--)
    {
        sum = 0;
        for (j = 1; j <= width; j++)sum += data.a[i][j];
        if (sum == width)
        {
            data.Line++;
            for (k = i; k > 1; k--)
            for (j = 1; j <= width; j++)data.a[k][j] = data.a[k - 1][j];
            i++;
        }
    }
    data.Level = 1 + data.Line / 10;
    data.Score = data.Line * 100;
    GotoXY(FrameX + 2 * width + 8, FrameY - 1);
    cout << "Level:%d", data.Level;
    GotoXY(FrameX + 2 * width + 8, FrameY + 1);
    cout << "积分:%d", data.Score;
    GotoXY(FrameX + 2 * width + 8, FrameY + 3);
    cout << "消去的行数:%d", data.Line;
}
/****************************************
* 自动下落函数
****************************************/
void Logic::AutoDown(class Tetris_Data &data)
{
    int i = 0, j = 0;
    data.time2 = clock();
    if (data.time2 - data.time1 > 1000 - 100 * data.Level)
    {
        Judge_MoveAndTansform(data);
        if (data.down)
        {
            CleanOld(data);
            data.Y++;
            DrawNew(data);
            //JustForDebugging();
        }
        if (!data.down)
        {
            CleanLine();
            data.X = StartX;
            data.Y = StartY;
            MakeTetris(data);
            Judge_MoveAndTansform(data);
            if (!data.down)
            {
                PrintTetris(data);
                Sleep(2000);//停顿两秒
                GameOver(data);
            }
            PrintTetris(data);
            PrintNextTetris(data);
        }
        //JustForDebugging();
        data.time1 = clock();
    }
}

/*****************************************全局函数*****************************************/
/****************************************
* 游戏欢迎界面
****************************************/
void Welcom(class Tetris_Data &data)
{
    int n = 0;
    class Env::HideCursor(data);
    class Env::FacePlate(data);
    class Env::PlayMusic(data);
    scanf("%d", &n);//输入选项
    switch (n)
    {
    case 1:class BackGround::GamePlay(data); break;//游戏开始 
    case 2:class BackGround::Explation(data); break;//按键说明函数 
    case 3:class BackGround::Regulation(data); break;//游戏规则 
    case 4:exit(0); break;//关闭游戏 
    }
}


/****************************************
* 游戏参数初始化
****************************************/
void Welcom(class Tetris_Data &data)
{
    int i = 0, j = 0;
    data.kind_current = rand() % 7;
    data.kind_next = rand() % 7;
    data.state_current = rand() % 4;
    data.state_next = rand() % 4;
    data.left = 1;
    data.right = 1;
    data.down = 1;
    data.trans = 1;
    data.X = StartX;
    data.Y = StartY;
    data.Line = 0;
    data.Level = 1;
    data.Score = 0;
    for (i = 1; i <= height + 1; i++)
    for (j = 1; j <= width + 1; j++)data.a[i][j] = 0;
    for (i = 1; i <= width; i++)data.a[height + 1][i] = 1;
    for (i = 0; i <= height + 1; i++)
    {
        data.a[i][0] = 1;
        data.a[i][width + 1] = 1;
    }
}
/****************************************
* 游戏开始函数
****************************************/
void GamePlay(class Tetris_Data &data)
{
    system("cls");
    Initialization(data);
    DrwaGameframe(data);
    MakeTetris(data);
    DrawNew(data);
    PrintNextTetris(data);
    data.time1 = clock();
    while (1)
    {
        KeyControl(data);
        //JustForDebugging();
        AutoDown(data);
    }
}
int main()
{
    Tetris_Data mytetris;
    Tetris_Data *pt = &mytetris;
    BackGround mybackdround;
    Welcom();
    return 0;
}