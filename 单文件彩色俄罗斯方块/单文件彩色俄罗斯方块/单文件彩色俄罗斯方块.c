#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define FrameX  16    //游戏窗口左上角的X轴坐标
#define FrameY  4  //游戏窗口左上角的Y轴坐标
#define height  20 //游戏窗口的高度
#define width   16//游戏窗口的宽度
#define StartX  1+width/2//俄罗斯方块中心出现位置横坐标 
#define StartY  2//俄罗斯方块中心出现位置纵坐标
extern time1, time2;
int Line = 0;//消除的行数 
int Level = 1;//等级
int Score = 0;//积分
/*
黑色=0     蓝色=1      绿色=2      浅绿色=3
红色=4     紫色=5      黄色=6      白色=7
灰色=8     淡蓝色=9    淡绿色=10   单浅绿色=11
淡红色=12  淡紫色=13   淡黄色=14   亮白色=15
*/
#define c1    2 //绿         L形                      
#define c2    8 //灰         T形                      
#define c3    15//白      长条形                     
#define c4    4 //红         Z形                       
#define c5    1 //蓝      方块形 
int a[height + 2][width + 2] = { 0 };//俄罗斯方块数据数组
int Music = 1;
typedef struct
{
    int kind_current;//当前方块种类
    int state_current;//当前方块状态
    int kind_next;//下一方块种类
    int state_next;//下一方块状态
    int left;//1为可左移，0为不可左移 
    int right;//1为可右移，0为不可右移
    int down;//1为可下移，0为不可下移
    int trans;//1为可旋转，0为不可旋转 
    int X;//中心方块横坐标
    int Y;//中心方块纵坐标
    int temp[7][4][5][5];//俄罗斯方块生成数组 
}MyTetris;
//■*********■*********■**************■■*******■■***■■
//■■■***■■■***■■■***■■■■*****■■***■■*****■■
MyTetris tetris =
{
    0, 0, 0, 0, 1, 1, 1, 1, StartX, StartY,
    { {
        { { 0, 0, 0, 0, 0 }, { 0, c1, 0, 0, 0 }, { 0, c1, c1, c1, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, c1, c1, 0 }, { 0, 0, c1, 0, 0 }, { 0, 0, c1, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, c1, c1, c1, 0 }, { 0, 0, 0, c1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, c1, 0, 0 }, { 0, 0, c1, 0, 0 }, { 0, c1, c1, 0, 0 }, { 0, 0, 0, 0, 0 } }
    }, {
        { { 0, 0, 0, 0, 0 }, { 0, 0, c2, 0, 0 }, { 0, c2, c2, c2, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, c2, 0, 0 }, { 0, 0, c2, c2, 0 }, { 0, 0, c2, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, c2, c2, c2, 0 }, { 0, 0, c2, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, c2, 0, 0 }, { 0, c2, c2, 0, 0 }, { 0, 0, c2, 0, 0 }, { 0, 0, 0, 0, 0 } }
    }, {
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, c1, 0 }, { 0, c1, c1, c1, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, c1, 0, 0 }, { 0, 0, c1, 0, 0 }, { 0, 0, c1, c1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, c1, c1, c1, 0 }, { 0, c1, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, c1, c1, 0, 0 }, { 0, 0, c1, 0, 0 }, { 0, 0, c1, 0, 0 }, { 0, 0, 0, 0, 0 } }
    }, {
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, c3, c3, c3, c3 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, c3, 0, 0 }, { 0, 0, c3, 0, 0 }, { 0, 0, c3, 0, 0 }, { 0, 0, c3, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, c3, c3, c3, c3 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, c3, 0, 0 }, { 0, 0, c3, 0, 0 }, { 0, 0, c3, 0, 0 }, { 0, 0, c3, 0, 0 } }
    }, {
        { { 0, 0, 0, 0, 0 }, { 0, c4, c4, 0, 0 }, { 0, 0, c4, c4, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, c4, 0 }, { 0, 0, c4, c4, 0 }, { 0, 0, c4, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, c4, c4, 0, 0 }, { 0, 0, c4, c4, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, c4, 0 }, { 0, 0, c4, c4, 0 }, { 0, 0, c4, 0, 0 }, { 0, 0, 0, 0, 0 } },
    }, {
        { { 0, 0, 0, 0, 0 }, { 0, 0, c4, c4, 0 }, { 0, c4, c4, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, c4, 0, 0 }, { 0, 0, c4, c4, 0 }, { 0, 0, 0, c4, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, c4, c4, 0 }, { 0, c4, c4, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, c4, 0, 0 }, { 0, 0, c4, c4, 0 }, { 0, 0, 0, c4, 0 }, { 0, 0, 0, 0, 0 } },
    }, {
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, c5, c5, 0 }, { 0, 0, c5, c5, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, c5, c5, 0 }, { 0, 0, c5, c5, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, c5, c5, 0 }, { 0, 0, c5, c5, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, c5, c5, 0 }, { 0, 0, c5, c5, 0 }, { 0, 0, 0, 0, 0 } }
    } }
};
MyTetris *pt = &tetris;
long time1, time2;
void GamePlay();
void Welcom();
/************************************************************************************************************************
*                                                   控制台函数设置部分
************************************************************************************************************************/
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
* 控制台颜色选择函数
****************************************/
void Color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);//更改文字颜色
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
/************************************************************************************************************************
*                                                   边框绘制函数设置部分
************************************************************************************************************************/
/****************************************
* 打印俄罗斯方块边框
****************************************/
void DrwaGameframe()
{
    int i = 0;
    Color(15);
    GotoXY(FrameX + width - 5, FrameY - 2);
    printf("      俄    罗    斯    方    块");
    Color(5);
    for (i = 1; i <= width+11; i++)
    {
        GotoXY(FrameX + 2 * i, FrameY);//打印上横框
        printf("■");
        GotoXY(FrameX + 2 * i, FrameY + height + 1);//打印下横框
        printf("■");
        a[height + 1][i] = 1;
    }
    for (i = 0; i <= height + 1; i++)
    {
        GotoXY(FrameX, FrameY + i);//打印左竖框
        printf("■");
        GotoXY(FrameX + 2 * width + 2, FrameY + i);//打印中竖框
        printf("■");
        GotoXY(FrameX + 2 * width + 24, FrameY + i);//打印右竖框
        printf("■");
        a[i][0] = 1;
        a[i][width + 1] = 1;
    }
    GotoXY(FrameX + 2 * width + 8, FrameY + 1);
    printf("Level:%d", Level);
    GotoXY(FrameX + 2 * width + 8, FrameY + 3);
    printf("积分:%d", Score);
    GotoXY(FrameX + 2 * width + 8, FrameY + 5);
    printf("消去的行数:%d", Line);
}
/****************************************
* 游戏开始界面
****************************************/
void FacePlate()
{
    Color(1);
    printf("\n\n\n");
    printf("                           俄  罗  斯  方  块             \n");
    Color(c2);
    GotoXY(18, 5);
    printf("■");
    GotoXY(18, 6);
    printf("■■");
    GotoXY(18, 7);
    printf("■");
    Color(c4);
    GotoXY(26, 6);
    printf("■■");
    GotoXY(28, 7);
    printf("■■");
    Color(c5);
    GotoXY(36, 6);
    printf("■■");
    GotoXY(36, 7);
    printf("■■");
    Color(c3);
    GotoXY(45, 5);
    printf("■");
    GotoXY(45, 6);
    printf("■");
    GotoXY(45, 7);
    printf("■");
    GotoXY(45, 8);
    printf("■");
    Color(c1);
    GotoXY(56, 6);
    printf("■");
    GotoXY(52, 7);
    printf("■■■");
    Color(1);
    GotoXY(0, 12);
    printf("                         1.开始游戏   2.按键说明          \n");
    printf("\n\n");
    printf("                         3.游戏规则   4.退出游戏          \n");
    printf("\n\n");
    printf("                           请选择[1 2 3 4]:");
    Color(15);
}
/****************************************
* 游戏结束界面
****************************************/
void GameOver()
{
    int n;
    system("cls");
    Color(1);
    printf("\n\n\n\n\n\n\n\n");
    printf("          ■■■      ■       ■    ■   ■■■■        ■■    ■      ■ ■■■■   ■■■  \n");
    printf("        ■           ■■     ■ ■■ ■  ■            ■    ■   ■    ■  ■         ■   ■ \n");
    printf("        ■   ■■   ■  ■   ■   ■   ■ ■■■       ■      ■   ■  ■   ■■■     ■■■  \n");
    printf("        ■     ■  ■■■■  ■   ■   ■ ■            ■    ■     ■■    ■         ■   ■ \n");
    printf("          ■■■  ■      ■ ■   ■   ■ ■■■■        ■■        ■     ■■■■   ■    ■\n");
    printf("\n\n\n\n\n");
    printf("                                       1:再玩一局          2:退出游戏                             ");
    printf("\n\n");
    printf("                                                 选择[1/2]:");
    Color(15);
    scanf("%d", &n);
    switch (n)
    {
    case 1:GamePlay(); break;
    case 2:exit(0); break;
    }
}
/****************************************
* 游戏按键介绍界面
****************************************/
void Explation()
{
    system("cls");
    Color(1);
    printf("\n\n\n");
    printf("                                    按键说明                \n\n\n");
    printf("                ************************************************\n");
    printf("                *   tip1: 玩家可以通过 ← →方向键来移动方块   *\n");
    printf("                *                                              *\n");
    printf("                *   tip2: 通过 ↑使方块旋转                    *\n");
    printf("                *                                              *\n");
    printf("                *   tip3: 通过 ↓加速方块下落                  *\n");
    printf("                *                                              *\n");
    printf("                *   tip4: 按空格键暂停游戏，再按空格键继续     *\n");
    printf("                *                                              *\n");
    printf("                *   tip5: 按ESC退出游戏，按tab键暂停/播放音乐  *\n");
    printf("                ************************************************\n");
    Color(15);
    getch();//按任意键返回主界面
    system("cls");
    Welcom();
}
/****************************************
* 游戏规则介绍界面
****************************************/
void Regulation()
{
    system("cls");
    Color(1);
    GotoXY(0, 3);
    printf("                                         按键说明                     \n\n\n");
    printf("                **********************************************************\n");
    printf("                *   tip1: 不同形状的小方块从屏幕上方落下，玩家通过调整   *\n");
    printf("                *         方块的位置和方向，使他们在屏幕底部拼出完整的   *\n");
    printf("                *         一条或几条                                     *\n");
    printf("                *                                                        *\n");
    printf("                *   tip2: 每消除一行，积分增加100                        *\n");
    printf("                *                                                        *\n");
    printf("                *   tip3: 每累计1000分，会提升一个等级                   *\n");
    printf("                *                                                        *\n");
    printf("                *   tip4: 提升等级会使方块下落速度加快，游戏难度加大     *\n");
    printf("                **********************************************************\n");
    Color(15);
    getch();//按任意键返回主界面
    system("cls");
    Welcom();
}
/****************************************
* 游戏欢迎界面
****************************************/
void Welcom()
{
    int n = 0;
    HideCursor();
    FacePlate();
    PlayMusic();
    scanf("%d", &n);//输入选项
    switch (n)
    {
    case 1:GamePlay(); break;//游戏开始 
    case 2:Explation(); break;//按键说明函数 
    case 3:Regulation(); break;//游戏规则 
    case 4:exit(0); break;//关闭游戏 
    }
}
/****************************************
* 游戏参数初始化
****************************************/
void Initialization()
{
    int i = 0, j = 0;
    pt->kind_current = rand() % 7;
    pt->kind_next = rand() % 7;
    pt->state_current = rand() % 4;
    pt->state_next = rand() % 4;
    pt->left = 1;
    pt->right = 1;
    pt->down = 1;
    pt->trans = 1;
    pt->X = StartX;
    pt->Y = StartY;
    Line = 0;
    Level = 1;
    Score = 0;
    for (i = 1; i <= height + 1; i++)
    for (j = 1; j <= width + 1; j++)a[i][j] = 0;
    for (i = 1; i <= width; i++)a[height + 1][i] = 1;
    for (i = 0; i <= height + 1; i++)
    {
        a[i][0] = 1;
        a[i][width + 1] = 1;
    }
}
/****************************************
* 生成俄罗斯方块
****************************************/
void MakeTetris()
{
    srand(time(NULL));
    pt->kind_current = pt->kind_next;
    pt->state_current = pt->state_next;
    pt->kind_next = rand() % 7;
    pt->state_next = rand() % 4;
}
/****************************************
* 打印出俄罗斯方块
****************************************/
void PrintTetris()
{
    int i = 0, j = 0;
    for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
        a[pt->Y - 2 + i][pt->X - 2 + j] += pt->temp[pt->kind_current][pt->state_current][i][j];
    for (i = 1; i <= height; i++)
    {
        GotoXY(FrameX + 2, FrameY + i);
        for (j = 1; j <= width; j++)
        if (a[i][j])
        {
            Color(a[i][j]);
            printf("■");
        }
        else printf("  ");
    }
}
/****************************************
* 清除旧的俄罗斯方块
****************************************/
void CleanOld()
{
    int i = 0, j = 0;
    for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
    if (pt->temp[pt->kind_current][pt->state_current][i][j])
    {
        a[pt->Y - 2 + i][pt->X - 2 + j] = 0;
        GotoXY(FrameX + 2 * pt->X - 4 + 2 * j, FrameY + pt->Y - 2 + i);
        printf("  ");
    }
}
/****************************************
* 打印新的俄罗斯方块
****************************************/
void DrawNew()
{
    int i = 0, j = 0;
    for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
    if (pt->temp[pt->kind_current][pt->state_current][i][j])
    {
        a[pt->Y + i - 2][pt->X + j - 2] = pt->temp[pt->kind_current][pt->state_current][i][j];
        GotoXY(FrameX + 2 * pt->X - 4 + 2 * j, FrameY + pt->Y - 2 + i);
        Color(pt->temp[pt->kind_current][pt->state_current][i][j]);
        printf("■");
    }
}
/************************************************************************************************************************
*                                                   俄罗斯方块游戏逻辑部分
************************************************************************************************************************/
/****************************************
* 旋转俄罗斯方块
****************************************/
void Transform()
{
    if (pt->state_current != 3)pt->state_current++;
    else pt->state_current = 0;
}
/****************************************
* 判断俄罗斯方块是否可移动和变形
****************************************/
void Judge_MoveAndTansform()
{
    int t;
    switch (pt->kind_current)
    {
    case 0:
    case 1:
    case 2:t = 4 * pt->kind_current + pt->state_current + 1; break;
    case 3:
    case 4:
    case 5:t = 2 * pt->kind_current + pt->state_current % 2 + 7; break;
    case 6:t = 19; break;
    }
    switch (t)
    {
    case 1:
        if (a[pt->Y - 1][pt->X - 2] == 0 && a[pt->Y][pt->X - 2] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X] == 0 && a[pt->Y][pt->X + 2] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X] == 0 && a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y + 1][pt->X] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 2:
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 2] == 0 && a[pt->Y][pt->X + 1] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 2][pt->X] == 0 && a[pt->Y][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y][pt->X - 1] == 0 && a[pt->Y][pt->X + 1] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 3:
        if (a[pt->Y][pt->X - 2] == 0 && a[pt->Y + 1][pt->X] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y][pt->X + 2] == 0 && a[pt->Y + 1][pt->X + 2] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 2][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X] == 0 && a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 4:
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X - 2] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X + 1] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 2][pt->X - 1] == 0 && a[pt->Y + 2][pt->X] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y][pt->X + 1] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 5:
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 2] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X + 2] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y + 1][pt->X] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 6:
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X + 2] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 2][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y][pt->X - 1] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 7:
        if (a[pt->Y][pt->X - 2] == 0 && a[pt->Y + 1][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y][pt->X + 2] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 2][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 8:
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 2] == 0 && a[pt->Y + 1][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X + 1] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 2][pt->X] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y][pt->X + 1] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 9:
        if (a[pt->Y][pt->X - 2] == 0 && a[pt->Y - 1][pt->X] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 2] == 0 && a[pt->Y][pt->X + 2] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 10:
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X + 1] == 0 && a[pt->Y + 1][pt->X + 2] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 2][pt->X] == 0 && a[pt->Y + 2][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y][pt->X + 1] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 11:
        if (a[pt->Y][pt->X - 2] == 0 && a[pt->Y + 1][pt->X - 2] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y][pt->X + 2] == 0 && a[pt->Y + 1][pt->X] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 2][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y - 1][pt->X] == 0 && a[pt->Y + 1][pt->X] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 12:
        if (a[pt->Y - 1][pt->X - 2] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X + 1] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 2][pt->X] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y][pt->X + 1] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 13:
        if (a[pt->Y][pt->X - 2] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y][pt->X + 3] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0 && a[pt->Y + 1][pt->X + 2] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 2][pt->X] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 14:
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 2][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X + 1] == 0 && a[pt->Y + 1][pt->X + 1] == 0 && a[pt->Y + 2][pt->X + 1] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 3][pt->X] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y][pt->X - 1] == 0 && a[pt->Y][pt->X + 1] == 0 && a[pt->Y][pt->X + 2] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 15:
        if (a[pt->Y - 1][pt->X - 2] == 0 && a[pt->Y][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X + 2] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y + 1][pt->X] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 16:
        if (a[pt->Y - 1][pt->X] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 2] == 0 && a[pt->Y][pt->X + 2] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 2][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y - 1][pt->X] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 17:
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 2] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 2] == 0 && a[pt->Y][pt->X + 1] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y][pt->X + 1] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 18:
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X + 2] == 0 && a[pt->Y + 1][pt->X + 2] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 2][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X - 1] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 19:
        if (a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y][pt->X + 2] == 0 && a[pt->Y + 1][pt->X + 2] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 2][pt->X] == 0 && a[pt->Y + 2][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        pt->trans = 0;
        break;
    default:break;
    }
}
/****************************************
* 关键参数显示函数(用于调试)
****************************************/
/*
void JustForDebugging()
{
Color(15);
int i = 0, j = 0;
for (i = 0; i < height + 2; i++)
{
GotoXY(FrameX + 2 * width + 24, FrameY + i);
for (j = 0; j < width + 2; j++)printf("%2d", a[i][j]);
}
GotoXY(FrameX + 4 * width + 30, FrameY + 2);
printf("X=%2d", pt->X);
GotoXY(FrameX + 4 * width + 30, FrameY + 3);
printf("Y=%2d", pt->Y);
GotoXY(FrameX + 4 * width + 30, FrameY + 4);
printf("Left=%d", pt->left);
GotoXY(FrameX + 4 * width + 30, FrameY + 5);
printf("Right=%d", pt->right);
GotoXY(FrameX + 4 * width + 30, FrameY + 6);
printf("Down=%d", pt->down);
GotoXY(FrameX + 4 * width + 30, FrameY + 7);
printf("Trans=%d", pt->trans);
}
*/
/****************************************
* 打印下一个俄罗斯方块
****************************************/
void PrintNextTetris()
{
    int i = 0, j = 0;
    Color(15);
    GotoXY(FrameX + 2 * width + 8, FrameY + 5);
    printf("下一个方块:%2d", pt->kind_next);
    for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
    {
        GotoXY(FrameX + 2 * width + 2 * j + 8, FrameY + 6 + i);
        if (pt->temp[pt->kind_next][pt->state_next][i][j])
        {
            Color(pt->temp[pt->kind_next][pt->state_next][i][j]);
            printf("■");
        }
        else printf("  ");
    }
}
/****************************************
* 清除满行
****************************************/
void CleanLine()
{
    int i = height, j = 1, k = 0, sum = 0;
    for (i = height; i > 0; i--)
    {
        sum = 0;
        for (j = 1; j <= width; j++)if (a[i][j])sum++;
        if (sum == width)
        {
            Line++;
            for (k = i; k > 1; k--)
            for (j = 1; j <= width; j++)a[k][j] = a[k - 1][j];
            i++;
        }
    }
    Level = 1 + Line / 10;
    Score = Line * 100;
    Color(1);
    GotoXY(FrameX + 2 * width + 8, FrameY + 1);
    printf("Level:%d", Level);
    GotoXY(FrameX + 2 * width + 8, FrameY + 3);
    printf("积分:%d", Score);
    GotoXY(FrameX + 2 * width + 8, FrameY + 5);
    printf("消去的行数:%d", Line);
}
/****************************************
* 自动下落函数
****************************************/
void AutoDown()
{
    time2 = clock();
    if (time2 - time1 > 1000 - 100 * Level)
    {
        Judge_MoveAndTansform();
        if (pt->down)
        {
            CleanOld();
            pt->Y++;
            DrawNew();
            //JustForDebugging();
        }
        if (!pt->down)
        {
            CleanLine();
            pt->X = StartX;
            pt->Y = StartY;
            MakeTetris();
            Judge_MoveAndTansform();
            if (!pt->down)
            {
                PrintTetris();
                Sleep(2000);//停顿两秒
                GameOver();
            }
            PrintTetris();
            PrintNextTetris();
        }
        //JustForDebugging();
        time1 = clock();
    }
}
/****************************************
* 键盘输入判定
****************************************/
void KeyControl()
{
    int ch = 0;
    if (_kbhit())
    {
        ch = getch();
        Judge_MoveAndTansform();
        switch (ch)
        {
        case 72:if (pt->trans){ CleanOld(); Transform(); DrawNew(); }break;//变形
        case 75:if (pt->left){ CleanOld(); pt->X--; DrawNew(); }break;//向上
        case 77:if (pt->right){ CleanOld(); pt->X++; DrawNew(); }break;//->向右
        case 80:if (pt->down){ CleanOld(); pt->Y++; DrawNew(); }break;//向下
        case 32:getch(); break;//空格键 暂停游戏
        case 9: Music = -Music;
            if (Music>0)RestartMusic();
            else PauseMusic(); break;//tab键 暂停歌曲
        case 27:system("cls"); exit(0); break;//ESC键 退出 
        default:break;
        }
    }
}
/****************************************
* 游戏开始函数
****************************************/
void GamePlay()
{
    system("cls");
    Initialization();
    DrwaGameframe();
    MakeTetris();
    DrawNew();
    PrintNextTetris();
    time1 = clock();
    while (1)
    {
        KeyControl();
        //JustForDebugging();
        AutoDown();
    }
}
int main()
{
    Welcom();
    return 0;
}