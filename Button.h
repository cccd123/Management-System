#pragma once

#include"tools.h"

class Button
{
public:
	Button(const string& text = "Button", int x = 0, int y = 0, int w = 100, int h = 30);

	int get_x();
	int get_y();
	int get_width();
	int get_height();

	void move(int x, int y);//移动按钮
	void setSize(int w, int y);//设置按钮大小

	void drawButton();

	static bool hasMsg();
	static ExMessage& getMsg();

	bool isPushed();

private:
	int m_x, m_y, m_w, m_h;
	string m_text;
	COLORREF cur_c = RGB(232, 232, 236), normol_c = RGB(232, 232, 236), change_c = RED;
	static ExMessage m_msg;//消息
};

