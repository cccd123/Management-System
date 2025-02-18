#include "Greeting_card.h"

#include<easyx.h>
#include<conio.h>//获取键盘信息
#include<ctime>//可以生成随机数
#include<cmath>//包含三角函数
#include<mmsystem.h>//windows多媒体接口
#pragma comment(lib,"winmm.lib")//连接实现多媒体功能的静态库

#define PI 3.1415926535897932384624
#define MAXSTAR 1024//星星的最大数目
#define MAXMETEOR 180//流星的最大数目

IMAGE img1;//图片定义为全局变量，以便在函数中使用
ExMessage msg;
bool running = true;

//定义星星，以会移动的闪光的点来表示
struct Star
{
	int x, y;
	int speed;
	int color;
}star[MAXSTAR];

//定义流星，用流动的爱心图表示
struct Meteor
{
	int x, y;
	int speed;
}meteor[MAXMETEOR];

void Greeting_card::initStar(int i)//初始化星星
{
	//因为画幅大小是1600*1000，所以坐标范围应在这中间
	star[i].x = rand() % 1600;
	star[i].y = rand() % 1000;
	star[i].speed = rand() % 8;
	star[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
}

void Greeting_card::drawAndMoveStar(int i)//绘制并移动星星
{
	putpixel(star[i].x, star[i].y, star[i].color);
	star[i].x += star[i].speed;//横向移动
	if (star[i].x > 1600)//如果超出框了就重新创建并初始化该星星
	{
		initStar(i);
	}
}

void Greeting_card::initMeteor(int i)//初始化流星
{
	meteor[i].x = rand() % 2200 - 1200;
	meteor[i].y = -400;
	meteor[i].speed = rand() % 40;
}

void Greeting_card::drawAndMoveMeteor(int i)//绘制并移动流星
{
	putimage(meteor[i].x, meteor[i].y, &img1, SRCPAINT);
	//向右下方移动
	meteor[i].x += meteor[i].speed;
	meteor[i].y += meteor[i].speed;
	//如果超出框了就重新创建并初始化该爱心流星
	if (meteor[i].x > 1600 || meteor[i].y > 1000)
	{
		initMeteor(i);
	}
}

void Greeting_card::textPrint(string name)//写文本
{
	for (int i = 0;i < 60;i++)//共闪动60帧
	{
		//判断是否想要停止程序的运行
		while (peekmessage(&msg)) {
			if (msg.message == WM_KEYDOWN) {
				if (msg.vkcode == VK_ESCAPE) {
					running = false;
					return;
				}
			}
		}
		cleardevice();
		//字体颜色设置为随机，创造彩色频闪效果
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		//字体旋转出场效果，设定一个圆心为（600，300），半径为150的圆，文字绕着圆出场
		int x = 600 + int(150 * cos(PI * 2 * i / 60));
		int y = 300 + int(150 * sin(PI * 2 * i / 60));
		settextstyle(i * 2, 0, "华文新魏");//文字越来越大
		outtextxy(x - 50, y - 100, name.c_str());
		outtextxy(x, y, "生日快乐");
		FlushBatchDraw();
		Sleep(180);
	}
	cleardevice();
	settextcolor(YELLOW);

	outtextxy(290, 250, "祝身体健康，万事如意!");Sleep(4000);
	cleardevice();

}

void Greeting_card::show(string name)
{
	loadimage(&img1, "1.jpg", 50, 50);//加载图片
	srand((unsigned int)time(NULL));//设置随机数种子

	HWND hwnd;//设置窗口句柄
	hwnd = initgraph(1600, 1000);
	ShowWindow(hwnd, 3);

	mciSendString("open 小幸运.mp3 alias MM", 0, 0, 0);//播放音乐
	mciSendString("play MM repeat", 0, 0, 0);

	setbkmode(0);//设置透明背景格式，可以让绘制的内容不受设备环境背景的影响
	textPrint(name);
	int i;
	for (i = 0;i < MAXSTAR;i++)
	{
		initStar(i);//初始化1024颗星星
	}
	for (i = 0;i < MAXMETEOR;i++)
	{
		initMeteor(i);//初始化300颗爱心流星
	}
	while (running)//不断绘图，从而连成动画
	{
		//判断是否想要停止程序的运行
		while (peekmessage(&msg)) {
			if (msg.message == WM_KEYDOWN) {
				if (msg.vkcode == VK_ESCAPE) {
					running = 0;
				}
			}
		}

		//以下为绘制一帧的图
		BeginBatchDraw();//双缓冲绘图，防止频闪现象

		cleardevice();//先清空再绘制
		for (i = 0;i < MAXSTAR;i++)
		{
			drawAndMoveStar(i);
		}
		for (i = 0; i < MAXMETEOR;i++)
		{
			drawAndMoveMeteor(i);
		}
		Sleep(100);//展示一段时间

		EndBatchDraw();

	}
	mciSendString("close MM", 0, 0, 0);
	closegraph();//可在关闭窗口时自动释放图像等资源
}
