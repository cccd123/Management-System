#include "Greeting_card.h"

#include<easyx.h>
#include<conio.h>//��ȡ������Ϣ
#include<ctime>//�������������
#include<cmath>//�������Ǻ���
#include<mmsystem.h>//windows��ý��ӿ�
#pragma comment(lib,"winmm.lib")//����ʵ�ֶ�ý�幦�ܵľ�̬��

#define PI 3.1415926535897932384624
#define MAXSTAR 1024//���ǵ������Ŀ
#define MAXMETEOR 180//���ǵ������Ŀ

IMAGE img1;//ͼƬ����Ϊȫ�ֱ������Ա��ں�����ʹ��
ExMessage msg;
bool running = true;

//�������ǣ��Ի��ƶ�������ĵ�����ʾ
struct Star
{
	int x, y;
	int speed;
	int color;
}star[MAXSTAR];

//�������ǣ��������İ���ͼ��ʾ
struct Meteor
{
	int x, y;
	int speed;
}meteor[MAXMETEOR];

void Greeting_card::initStar(int i)//��ʼ������
{
	//��Ϊ������С��1600*1000���������귶ΧӦ�����м�
	star[i].x = rand() % 1600;
	star[i].y = rand() % 1000;
	star[i].speed = rand() % 8;
	star[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
}

void Greeting_card::drawAndMoveStar(int i)//���Ʋ��ƶ�����
{
	putpixel(star[i].x, star[i].y, star[i].color);
	star[i].x += star[i].speed;//�����ƶ�
	if (star[i].x > 1600)//����������˾����´�������ʼ��������
	{
		initStar(i);
	}
}

void Greeting_card::initMeteor(int i)//��ʼ������
{
	meteor[i].x = rand() % 2200 - 1200;
	meteor[i].y = -400;
	meteor[i].speed = rand() % 40;
}

void Greeting_card::drawAndMoveMeteor(int i)//���Ʋ��ƶ�����
{
	putimage(meteor[i].x, meteor[i].y, &img1, SRCPAINT);
	//�����·��ƶ�
	meteor[i].x += meteor[i].speed;
	meteor[i].y += meteor[i].speed;
	//����������˾����´�������ʼ���ð�������
	if (meteor[i].x > 1600 || meteor[i].y > 1000)
	{
		initMeteor(i);
	}
}

void Greeting_card::textPrint(string name)//д�ı�
{
	for (int i = 0;i < 60;i++)//������60֡
	{
		//�ж��Ƿ���Ҫֹͣ���������
		while (peekmessage(&msg)) {
			if (msg.message == WM_KEYDOWN) {
				if (msg.vkcode == VK_ESCAPE) {
					running = false;
					return;
				}
			}
		}
		cleardevice();
		//������ɫ����Ϊ����������ɫƵ��Ч��
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		//������ת����Ч�����趨һ��Բ��Ϊ��600��300�����뾶Ϊ150��Բ����������Բ����
		int x = 600 + int(150 * cos(PI * 2 * i / 60));
		int y = 300 + int(150 * sin(PI * 2 * i / 60));
		settextstyle(i * 2, 0, "������κ");//����Խ��Խ��
		outtextxy(x - 50, y - 100, name.c_str());
		outtextxy(x, y, "���տ���");
		FlushBatchDraw();
		Sleep(180);
	}
	cleardevice();
	settextcolor(YELLOW);

	outtextxy(290, 250, "ף���彡������������!");Sleep(4000);
	cleardevice();

}

void Greeting_card::show(string name)
{
	loadimage(&img1, "1.jpg", 50, 50);//����ͼƬ
	srand((unsigned int)time(NULL));//�������������

	HWND hwnd;//���ô��ھ��
	hwnd = initgraph(1600, 1000);
	ShowWindow(hwnd, 3);

	mciSendString("open С����.mp3 alias MM", 0, 0, 0);//��������
	mciSendString("play MM repeat", 0, 0, 0);

	setbkmode(0);//����͸��������ʽ�������û��Ƶ����ݲ����豸����������Ӱ��
	textPrint(name);
	int i;
	for (i = 0;i < MAXSTAR;i++)
	{
		initStar(i);//��ʼ��1024������
	}
	for (i = 0;i < MAXMETEOR;i++)
	{
		initMeteor(i);//��ʼ��300�Ű�������
	}
	while (running)//���ϻ�ͼ���Ӷ����ɶ���
	{
		//�ж��Ƿ���Ҫֹͣ���������
		while (peekmessage(&msg)) {
			if (msg.message == WM_KEYDOWN) {
				if (msg.vkcode == VK_ESCAPE) {
					running = 0;
				}
			}
		}

		//����Ϊ����һ֡��ͼ
		BeginBatchDraw();//˫�����ͼ����ֹƵ������

		cleardevice();//������ٻ���
		for (i = 0;i < MAXSTAR;i++)
		{
			drawAndMoveStar(i);
		}
		for (i = 0; i < MAXMETEOR;i++)
		{
			drawAndMoveMeteor(i);
		}
		Sleep(100);//չʾһ��ʱ��

		EndBatchDraw();

	}
	mciSendString("close MM", 0, 0, 0);
	closegraph();//���ڹرմ���ʱ�Զ��ͷ�ͼ�����Դ
}
