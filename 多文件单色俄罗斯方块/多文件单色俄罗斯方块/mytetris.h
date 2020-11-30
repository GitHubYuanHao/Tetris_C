#ifndef TETRIS
#define TETRIS

#define FrameX  16    //游戏窗口左上角的X轴坐标
#define FrameY  4  //游戏窗口左上角的Y轴坐标
#define height  20 //游戏窗口的高度
#define width   10//游戏窗口的宽度
#define StartX  1+width/2//俄罗斯方块中心出现位置横坐标 
#define StartY  2//俄罗斯方块中心出现位置纵坐标

extern int Level;
extern int Score;
extern int Line;
extern int a[height + 2][width + 2];//俄罗斯方块数据数组

void GameOver();
void Initialization();
void MakeTetris();
void PrintTetris();
void CleanOld();
void DrawNew();
void Transform();
void Judge_MoveAndTansform();
void JustForDebugging();
void PrintNextTetris();
void CleanLine();
void AutoDown();
void KeyControl();

#endif