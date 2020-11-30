#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include"mytetris.h"
#include"myconsole.h"
#include"background.h"
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")

int Line = 0;//消除的行数 
int Level = 1;//等级
int Score = 0;//积分
int a[height + 2][width + 2] = { 0 };//俄罗斯方块数据数组
int Music=1;
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
        { { 0, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0 }, { 0, 1, 1, 1, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 1, 1, 1, 0 }, { 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 0, 0, 0 } }
    }, {
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 1, 1, 1, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 1, 1, 1, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } }
    }, {
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0 }, { 0, 1, 1, 1, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 1, 1, 1, 0 }, { 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } }
    }, {
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 1, 1, 1, 1 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 1, 1, 1, 1 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 } }
    }, {
        { { 0, 0, 0, 0, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } },
    }, {
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 0 } },
    }, {
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 } }
    } }
};
MyTetris *pt = &tetris;
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
        if (a[i][j])printf("■");
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
        printf("■");
    }
}
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
void JustForDebugging()
{
    int i = 0, j = 0;
    for (i = 0; i < height + 2; i++)
    {
        GotoXY(FrameX + 2 * width + 24, FrameY + i);
        for (j = 0; j < width + 2; j++)printf("%d", a[i][j]);
    }
    GotoXY(FrameX + 3 * width + 30, FrameY + 2);
    printf("X=%2d", pt->X);
    GotoXY(FrameX + 3 * width + 30, FrameY + 3);
    printf("Y=%2d", pt->Y);
    GotoXY(FrameX + 3 * width + 30, FrameY + 4);
    printf("Left=%d", pt->left);
    GotoXY(FrameX + 3 * width + 30, FrameY + 5);
    printf("Right=%d", pt->right);
    GotoXY(FrameX + 3 * width + 30, FrameY + 6);
    printf("Down=%d", pt->down);
    GotoXY(FrameX + 3 * width + 30, FrameY + 7);
    printf("Trans=%d", pt->trans);
}

/****************************************
* 打印下一个俄罗斯方块
****************************************/
void PrintNextTetris()
{
    int i = 0, j = 0;
    GotoXY(FrameX + 2 * width + 8, FrameY + 5);
    printf("下一个方块:%2d", pt->kind_next);
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
        {
            GotoXY(FrameX + 2 * width + 2 * j + 8, FrameY + 6 + i);
            if (pt->temp[pt->kind_next][pt->state_next][i][j])printf("■");
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
        for (j = 1; j <= width; j++)sum += a[i][j];
        if (sum == width)
        {
            Line++;
            for (k = i; k > 1; k--)
            for (j = 1; j <=width; j++)a[k][j] = a[k - 1][j];
            i++;
        }
    }
    Level = 1 + Line / 10;
    Score = Line * 100;
    GotoXY(FrameX + 2 * width + 8, FrameY - 1);
    printf("Level:%d", Level);
    GotoXY(FrameX + 2 * width + 8, FrameY + 1);
    printf("积分:%d", Score);
    GotoXY(FrameX + 2 * width + 8, FrameY + 3);
    printf("消去的行数:%d", Line);
}
/****************************************
* 自动下落函数
****************************************/
void AutoDown()
{
    int i = 0, j = 0;
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
    int i = 0, j = 0, ch = 0;
    if (_kbhit())
    {
        ch = _getch();
        Judge_MoveAndTansform();
        switch (ch)
        {
        case 72:if (pt->trans){ CleanOld(); Transform(); DrawNew(); }break;//变形
        case 75:if (pt->left){ CleanOld(); pt->X--; DrawNew(); }break;//向上
        case 77:if (pt->right){ CleanOld(); pt->X++; DrawNew(); }break;//->向右
        case 80:if (pt->down){ CleanOld(); pt->Y++; DrawNew(); }break;//向下
        case 32:_getch(); break;//空格键 暂停游戏
        case 9: Music = -Music;
            if (Music > 0)RestartMusic();
            else RestartMusic(); break;//tap键 暂停歌曲
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