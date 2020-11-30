#ifndef TETRIS
#define TETRIS

#define FrameX  16    //游戏窗口左上角的X轴坐标
#define FrameY  4  //游戏窗口左上角的Y轴坐标
#define height  20 //游戏窗口的高度
#define width   20//游戏窗口的宽度
#define StartX  1+width/2//俄罗斯方块中心出现位置横坐标 
#define StartY  2//俄罗斯方块中心出现位置纵坐标

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

extern int Line;//消除的行数 
extern int Level;//等级
extern int Score;//积分
extern int a[height + 2][width + 2];//俄罗斯方块数据数组
extern int Music;

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