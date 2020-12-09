// ConsoleApplication1++.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<stdio.h>
#include<windows.h>					//将用户从键盘获得的输入进行输出
#include<conio.h>	//获得用户键盘的输入
#include <graphics.h>
#pragma comment(lib,"Winmm.lib")
//定义全局变量
int high, width;						//定义边界
int position_x, position_y;			//飞机位置
int bullet_x, bullet_y;				//子弹位置
int enemy_x, enemy_y;				//敌军飞机
int enemy2_x, enemy2_y;
int score;							//获得分数
int flag;
IMAGE bg;
 int speed;
 int speed2;
void gotoxy(int x, int y);
void welcometogame();
int color(int c);
void explation();
void scoreandtips();
void show();
void endgame();
void setColor();

int color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    return 0;
}

enum Color
{
    black, blue, green, lakeBlue, red, purple, yellow, white, gray,
    lightBlue, lightGreen, lightSimpleGreen, lightRed, lightPurple, lightYellow, brightWhite
};

void setColor(unsigned short textColor = 0, unsigned short backColor = 7)
{
    char command[9] = "color 07";
    command[6] = '0' + backColor;
    command[7] = '0' + textColor;
    system(command);
}

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

inline void welcometogame()
{
	mciSendString("open D:\\Background\\Sounds\\game_music.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);
    setColor(1, 3);
    int n;
    //	color(15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 17 | 10 | 70 | 64);
    gotoxy(43, 10);
    printf("飞 机 大 战");
    //	color(11);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 | 8 | 128 | 64);
    gotoxy(25, 22);
    printf("1.开始游戏");
    gotoxy(45, 22);
    printf("2.游戏说明");
    gotoxy(65, 22);
    printf("3.退出游戏");
    gotoxy(40, 27);
    //	color(3);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10 | 5 | 40 | 64);
    printf("请选择 1 2 3:");
    color(14);
    scanf_s("%d", &n);
    switch (n)
    {
    case 1:
        system("cls");
		mciSendString("stop bkmusic", NULL, 0, NULL);
        show();
        break;
    case 2:
		mciSendString("open, D:\\Background\\Sounds\\get_explation.mp3 alias expmusic", NULL, 0, NULL);
		mciSendString("play expmusic repeat", NULL, 0, NULL);
        explation();
        break;
    case 3:
        exit(0);
        break;
    default:
        color(12);
        gotoxy(40, 28);
        printf("请输入1-3之间的数!");
        _getch();
        system("cls");
        welcometogame();
    }
}

void bkgd()
{
    int i, j = 1;
    system("cls");
    
    gotoxy(44, 1);
    printf("故事背景");
    
    for (i = 3; i <= 28; i++)
    {
        for (j = 6; j <= 80; j++)
        {
            gotoxy(j, i);
            if (i == 3 || i == 28) printf("=");
            else if (j == 6 || j == 80) printf("||");
        }
    }
    
    
    gotoxy(10, 5);
    printf("公元2050年，人类科技艺日新月异。在向宇宙进发的征途中");
    
    gotoxy(10, 8);
    printf("被另一个文明——外星虫族发现了,面对蛮横的虫群，人类军队与之展开战争");
    
    gotoxy(10, 11);
    printf("你将扮演地球军上校，深入从群内部歼灭敌人");
    
    gotoxy(10, 14);
    printf("加油,我们期盼着你的凯旋！");
    
    gotoxy(10, 20);
    printf("/*****按任意键返回主页面*****/");
    _getch();
    mciSendString("stop expmusic", NULL, 0, NULL);
    system("cls");
}
void explation()
{
    int i, j = 1;
    system("cls");
    color(10);
    gotoxy(44, 1);
    printf("游戏说明");
    color(2);
    for (i = 3; i <= 28; i++)
    {
        for (j = 6; j <= 80; j++)
        {
            gotoxy(j, i);
            if (i == 3 || i == 28) printf("=");
            else if (j == 6 || j == 80) printf("||");
        }
    }
   // setColor(1, 6);
    color(3);
    gotoxy(20, 5);
    printf("1. W,A,S,D 分别控制飞机的上下左右移动");
    color(10);
    gotoxy(20, 8);
    printf("2. 按空格发射子弹，打中敌机即可得到一分");
    color(14);
    gotoxy(20, 11);
    printf("3.碰到敌机子弹死亡");
    color(11);
    gotoxy(20, 14);
    printf("4. ESC ：退出游戏");
    color(7);
    gotoxy(20, 20);
    printf("/*****按任意键返回主页面*****/");
    _getch();
	mciSendString("stop expmusic", NULL, 0, NULL);
    system("cls");
    welcometogame();
}

void scoreandtips()
{
    gotoxy(50, 8);
    color(14);
    printf("游戏得分：%d ", score);
    gotoxy(50, 10);
    printf("用W A S D 分别控制飞机的移动");
    gotoxy(50, 12);
    printf("按下空格键即为发射炮弹");
    gotoxy(50, 14);
    printf(" @ # 的样子就是敌人的飞机");
}

void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup()
{
    high = 20;
    width = 40;
    position_x = high - 3;
    position_y = width / 2;
    bullet_x = 0;
    bullet_y = position_y;
    enemy_x = 0;
    enemy_y = position_y;
    enemy2_x = 0;
    enemy2_y = position_y+5;
    score = 0;
    flag = 0;
    HideCursor();
}

void show(){
	int i,j;
	mciSendString("open D:\\Background\\raw\\bgm_zhandou2.mp3 alias battlemusic", NULL, 0, NULL);
	mciSendString("play battlemusic repeat", NULL, 0, NULL);
	for(i=0;i<high;i++){
		for(j=0;j<width;j++){
			if(flag)
				break;
			else if((i==position_x)&&(j==position_y)){
				printf("▲\b");
			}
			else if((i==enemy_x)&&(j==enemy_y))				
				printf("@");
            else if ((i == enemy2_x) && (j == enemy2_y))
                printf("#");
			else if((i==bullet_x)&&(j==bullet_y))
				printf("!!");
			else if ((j==width-1)||(i==high-1)||(j==0)||(i==0))				
				printf("-");
			else
				printf(" ");
		}
		printf("\n"); 
	}
	printf("\n");
	if(((position_x+1==enemy_x)||(position_x==enemy_x))&&(position_y==enemy_y))
    {
		flag=1;					
		system("cls");
		printf("游戏结束!!!\n");
		
	}
    else if (((position_x+1==enemy2_x)||(position_x==enemy2_x)) && (position_y == enemy2_y))
    {
        flag = 1;
        system("cls");
        printf("游戏结束!!!\n");

    }
 	else
    {
 			printf("分数 %d",score);
    }   
 
}
	
void endgame()
{
    int k;
	mciSendString("stop endmusic", NULL, 0, NULL);
    system("cls");
    printf("输入1再玩一次，输入2返回主菜单，输入3退出游戏");
    scanf_s("%d", &k);
    system("cls");
    switch (k)
    {
    case 1:
        printf("重新玩游戏");
        system("cls");
        startup();					// 数据初始化
        show();
        break;
    case 2:
        printf("返回主菜单");
        system("cls");
        welcometogame();
        startup();
        break;
    case 3:
        printf("退出成功");
        exit(0);
        break;
    default:
        color(12);
        gotoxy(40, 28);
        system("cls");
        printf("输入错误,输入任意键回到主菜单");
        _getch();			//输入任意键
        welcometogame();
        startup();
        system("cls");   //清屏
    }
}

void withoutInpute()						//与用户输入无关
{
    if (bullet_x > 0)							//子弹上升效果
        bullet_x--;
    if ((bullet_x == enemy_x) && (bullet_y == enemy_y || bullet_y == enemy_y + 1))		//子弹命中敌机
    {

        score++;
        bullet_x = -1;
        enemy_x = 1;
        enemy_y = 2 + rand() % width - 2;
    }
    if ((bullet_x == enemy2_x) && (bullet_y == enemy2_y || bullet_y == enemy2_y + 1))		//子弹命中敌机
    {

        score++;
        bullet_x = -1;
        enemy2_x = 1;
        enemy2_y = 2 + rand() % width - 1;
    }


    if (speed < 5)					//减慢敌机速度，不影响飞机和子弹速度
        speed++;
    if (speed == 5)
    {
        if (enemy_x < high)
            enemy_x++;
        else
        {
            enemy_x = 0;
            enemy_y = 2 + rand() % width - 2;
        }
        speed = 0;
    }


    if (speed < 3)					//减慢敌机速度，不影响飞机和子弹速度
        speed++;
    if (speed == 3)
    {
        if (enemy2_x < high)
            enemy2_x++;
        else
        {
            enemy2_x = 0;
            enemy2_y = 2 + rand() % width - 2;
        }
        speed2 = 0;
    }
}

void withInpute()
{
    char input;
    if (_kbhit())
    {
        input = _getch();
        if ((input == 'w') && position_x > 1)
            position_x--;
        if ((input == 's') && position_x < high - 2)
            position_x++;
        if ((input == 'a') && position_y > 1)
            position_y--;
        if ((input == 'd') && position_y < width - 2)
            position_y++;
        if (input == ' ')
        {
            bullet_x = position_x+1;
            bullet_y = position_y;
		}	
    }
}

int main()
{
    printf_s("loading... please wait.");
	mciSendString("open D:\\Background\\Sounds\\game_music.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);
    initgraph(900, 500);
    loadimage(&bg, _T("D:\\Background\\gg.jpg"),800, 500);
    putimage(50, 0, &bg);
    _getch();
    closegraph();
    system("mode con cols=100 lines=30");
    bkgd();
	welcometogame();
    startup();
    while (1)
    {
        gotoxy(0, 0);
        show();
        scoreandtips();
        if (flag == 1)
        {
            endgame();
        }
        withoutInpute();
        withInpute();
    }
    return 0;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单