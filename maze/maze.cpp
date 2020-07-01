#include<iostream>
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<stack>
#include <time.h>
#include <vector>
#include <cstdlib>
#include<graphics.h>
using namespace std;
HWND hWnd;
#define M 9
#define N 9
int q, w;
#define down 1
#define right 2
#define left 4
#define up 8

vector <int> block_row;
vector <int> block_column;
vector <int> block_direct;
int x_num = 1;
int y_num = 1;

int vis[M + 2][M + 2] =
{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

int mvp[M + 2][N + 2] =
{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

int maze[M + 2][N + 2] =
{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 3, 0, 1, 0, 0, 0, 1, 0, 1 },
	{ 1, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 1, 0, 0, 1 },
	{ 1, 0, 1, 1, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 0, 0, 1, 0, 0, 1 },
	{ 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 4, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};




class T //定义描述迷宫中当前位置的结构类型
{
public:
	int x; //x 代表当前位置的行坐标
	int y; //y 代表当前位置的列坐标
};

stack <T> path, te;

void init(){//将地图全部置1=wall
	for (int i = 0; i <= M + 1; i++){
		for (int j = 0; j <= N + 1; j++){
			maze[i][j] = 1;//wall
		}
	}
}

void push(int x, int y, int direct){//把一组数据存放进三个vector容器中
	block_row.push_back(x);
	block_column.push_back(y);
	block_direct.push_back(direct);
}

int count(){//计算当前位置周围 墙的个数
	int cnt = 0;
	if (x_num + 1 <= M){
		push(x_num + 1, y_num, down);
		cnt++;
	} //down
	if (y_num + 1 <= N){
		push(x_num, y_num + 1, right);
		cnt++;
	} //right
	if (x_num - 1 >= 1){
		push(x_num - 1, y_num, up);
		cnt++;
	} //up
	if (y_num - 1 >= 1){
		push(x_num, y_num - 1, left);
		cnt++;
	} //left
	return cnt;
}

void createmaze()                                    //随机产生迷宫
{
	int sui = 1;
	x_num = 1;
	y_num = 1;
	T start, end;
	start.x = 1;//定义起始点
	start.y = 1;
	end.x = M;
	end.y = N;
	init();
	srand((unsigned)time(NULL));//随机数种子
	count();

	maze[1][1] = 0;
	while (block_row.size())
	{                                                   //第一步压入两堵墙（起点右边和起点下面）进入循环
		int num = block_row.size();
		int randnum = rand() % num;                     //生成0-num-1之间的随机数，同时也是vector里的下标
		switch (block_direct[randnum]){//选择一个方向进行后续操作，起始点 邻块 目标块 三块区域在同一直线上 随后移动到目标块的位置
		case down:{
					  x_num = block_row[randnum] + 1;
					  y_num = block_column[randnum];
					  break;
		}
		case right:{
					   x_num = block_row[randnum];
					   y_num = block_column[randnum] + 1;
					   break;
		}
		case left:{
					  x_num = block_row[randnum];
					  y_num = block_column[randnum] - 1;
					  break;
		}
		case up:{
					x_num = block_row[randnum] - 1;
					y_num = block_column[randnum];
					break;
		}
		}
		if (maze[x_num][y_num] == 1)
		{                                                           //目标块如果是墙
			maze[block_row[randnum]][block_column[randnum]] = 0;    //打通墙
			maze[x_num][y_num] = 0;                                 //打通目标块
			count();                                                //再次计算当前位置周围的邻墙个数并保存进vector
		}
		block_row.erase(block_row.begin() + randnum);               //删除这堵墙(能跳出循环)
		block_column.erase(block_column.begin() + randnum);
		block_direct.erase(block_direct.begin() + randnum);
	}
	maze[1][1] = 3;
	maze[M][N] = 4;
	while (sui!=0)
	{
		int random1 = rand() % M + 1;
		int random2 = rand() % N + 1;
		if (maze[random1][random2] == 1)
		{
			maze[random1][random2] = 0;
			sui--;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////上面为随机生成迷宫的代码////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
void restore(int m, int n) //恢复迷宫
{
	int i, j;
	for (i = 0; i<m + 2; i++) //遍历指针
	for (j = 0; j<n + 2; j++)
	{
		if (maze[i][j] != 1) //恢复探索过位置，即把-1 恢复为 0
			maze[i][j] = 0;
	}
}

void printMaze(int m, int n)//显示地图
{
	IMAGE wall, mouse, nn, daan, road, desk;
	loadimage(&wall, L"wall.jpg", 50, 50);
	loadimage(&mouse, L"mouse.jpg", 50, 50);
	loadimage(&nn, L"nn.jpg", 50, 50);
	loadimage(&daan, L"daan.jpg", 50, 50);
	loadimage(&road, L"road.jpg", 50, 50);
	loadimage(&desk, L"desk.jpg", 250, 550);
	putimage(550, 0, &desk);
	for (int i = 0; i<m + 2; i++)
	{
		for (int j = 0; j < n + 2; j++)
			switch (maze[i][j])
		{
			case 0:
				putimage(j * 50, i * 50, &road);   //road
				break;
			case 1:
				putimage(j * 50, i * 50, &wall);   //wall
				break;
			case 8:
				putimage(j * 50, i * 50, &daan); //答案
				break;
			case 3:
				putimage(j * 50, i * 50, &mouse);  //人物
				break;
			case 4:
				putimage(j * 50, i * 50, &nn);  //出口
				break;
		}
		cout << endl;
	}
}

void find(int m, int n)   //3是本人
{

	int i = 0, j = 0;
	for (i = 1; i < m + 1; i++)
	{
		for (j = 1; j < n + 1; j++)
		{
			if (maze[i][j] == 3)
			{
				q = i;   //人物的坐标
				w = j;
				break;
			}
		}
	}
}

int Up()
{
	if (q != 1)
	{
		if (maze[q - 1][w] == 0)//可走
		{
			maze[q - 1][w] = 3;
			maze[q][w] = 0;
		}
		else if (maze[q - 1][w] == 4)
		{
			maze[q - 1][w] = 3;
			maze[q][w] = 0;
			return 1;
		}
	}
	return 0;
}

int Down()
{
	if (q != M)
	{
		if (maze[q + 1][w] == 0)//可走
		{
			maze[q + 1][w] = 3;
			maze[q][w] = 0;
		}
		else if (maze[q + 1][w] == 4)
		{
			maze[q + 1][w] = 3;
			maze[q][w] = 0;
			return 1;
		}
	}
	return 0;
}

int Right()
{
	if (w != N)
	{
		if (maze[q][w + 1] == 0)//可走
		{
			maze[q][w + 1] = 3;
			maze[q][w] = 0;
		}
		else if (maze[q][w + 1] == 4)
		{
			maze[q][w + 1] = 3;
			maze[q][w] = 0;
			return 1;
		}
	}
	return 0;
}

int Left()
{
	if (w != 1)
	{
		if (maze[q][w - 1] == 0)//可走
		{
			maze[q][w - 1] = 3;
			maze[q][w] = 0;
		}
		else if (maze[q][w - 1] == 4)
		{
			maze[q][w - 1] = 3;
			maze[q][w] = 0;
			return 1;
		}
	}
	return 0;
}

int move(char o)
{
	int flag = 0;

	find(M, N);
	switch (o)//接收按键输入
	{
	case 'w':flag = Up(); break;
	case 'a':flag = Left(); break;
	case 's':flag = Down(); break;
	case 'd':flag = Right(); break;
	case 27:return 0;
	}
	printMaze(M, N);
	if (flag == 1)
	{
		//通过了
		int result = MessageBox(hWnd, TEXT("恭喜你完成了关卡，是否挑战新关卡"), TEXT("恭喜"), MB_YESNO);
		switch (result)
		{
		case IDYES:
			return 3;
			break;
		case IDNO:
			return 1;
		}

	}

}

void dfs(int sx, int sy){
	int move[4][2] = { { 1, 0 }, { 0, -1 }, { -1, 0 }, { 0, 1 } }; //定义当前位置移动的 4 个方向
	if (sx == M  && sy == N)
	{//如果满足就开始输出 
		while (!path.empty())
		{                       //栈不为空 
			T p1 = path.top();//取栈顶元素 
			path.pop();//出栈 
			te.push(p1);//p1压到temp 
		}
		while (!te.empty()){//输出temp的元素 
			T p1 = te.top();
			te.pop();
			path.push(p1);
			mvp[p1.x][p1.y] = 8;
		}
		return;
	}
	if (sx<1 || sx >M || sy<1 || sy > N){//如果越界就return掉 
		return;
	}
	for (int i = 0; i<4; i++)
	{//对四个方向搜索 
		int ex = sx + move[i][0];//改变方向 
		int ey = sy + move[i][1];
		if (ex >= 1 && ex <= M && ey > 0 && ey <= N && maze[ex][ey] == 0 && vis[ex][ey] == 0)
		{//条件 
			vis[ex][ey] = 1;//设为访问过 
			T p;
			p.x = ex;
			p.y = ey;
			path.push(p);//当前点进栈 
			dfs(ex, ey);//继续搜索下一个点 
			vis[ex][ey] = 0; // 回溯 
			path.pop();//需要回溯，要将栈顶元素给弹出 
		}
	}
	return;

}

int main()
{
	createmaze();
	initgraph(800, 550);
	loadimage(NULL, L"playground.jpg", 700, 550);
	T p;
	p.x = 1;
	p.y = 1;
	path.push(p);
	int m = M, n = N, kb = 0; //定义迷宫的长和宽   //定义二维指针存取迷宫//调用 GetMaze(int &m,int &n)函数，得到迷宫
	int** array = new int*[M + 2];
	for (int i = 0; i < M + 2; i++)
	{
		array[i] = new int[N + 2];
	}
	for (int r = 0; r < m + 2; r++)
	for (int t = 0; t < n + 2; t++)
		array[r][t] = maze[r][t];
	printMaze(m, n);
	int h = 1, flag = 0;
	char o;
	while (h)
	{
		hWnd = GetHWnd();
		char o = _getch();
		switch (o)
		{
		case '1':
			h = 0;
			break;
		case '2':
			restore(m, n);
			dfs(1, 1);
			for (int r = 1; r < m + 1; r++)
			{
				for (int t = 1; t < n + 1; t++)
				{
					if (mvp[r][t] == 8)
					{
						maze[r][t] = 8;
						mvp[r][t] = 1;
					}
					if (maze[r][t] != 1)
						kb++;
				}
			}
			if (maze[2][1] == 8 && maze[3][1] != 8 && maze[2][2] != 8)
				maze[2][1] = 0;
			if (maze[1][2] == 8 && maze[1][3] != 8 && maze[2][2] != 8)
				maze[1][2] = 0;
			if (kb == 0)
			{
				MessageBox(hWnd, TEXT("没有路径"), TEXT("提示"), NULL);
				h = 0;
				break;
			}
			else
			{
				printMaze(m, n);
				flag = MessageBox(hWnd, TEXT("是否继续游戏"), TEXT("提示"), MB_YESNO);
				switch (flag)
				{
				case IDYES:
					for (int r = 0; r < m + 2; r++)
					for (int t = 0; t < n + 2; t++)
						maze[r][t] = array[r][t];
					printMaze(m, n);
					break;
				case IDNO:
					h = 0;
					break;
				}
				break;
			}
		case '3'://新关卡
			createmaze();
			for (int r = 0; r < m + 2; r++)
			for (int t = 0; t < n + 2; t++)
				array[r][t] = maze[r][t];
			printMaze(m, n);
			break;
		default:
			flag = move(o);
			for (int r = 0; r < m + 2; r++)
			for (int t = 0; t < n + 2; t++)
				array[r][t] = maze[r][t];
			if (flag == 1)
				h = 0;
			else if (flag == 3)
			{
				createmaze();
				for (int r = 0; r < m + 2; r++)
				for (int t = 0; t < n + 2; t++)
					array[r][t] = maze[r][t];
				printMaze(m, n);
			}
		}
	}

	return 0;
}