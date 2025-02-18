#pragma once
#include"tools.h"

class Greeting_card
{
public:
	void initStar(int i);//初始化星星
	void drawAndMoveStar(int i);//绘制并移动星星
	void initMeteor(int i);//初始化流星
	void drawAndMoveMeteor(int i);//绘制并移动流星
	void textPrint(string name);//写文本
	void show(string name);
};