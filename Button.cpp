#include "Button.h"

ExMessage Button::m_msg;

Button::Button(const string& text, int x, int y, int w, int h)
	:m_x(x), m_y(y), m_w(w), m_h(h), m_text(text)
{}

int Button::get_x()
{
	return m_x;
}

int Button::get_y()
{
	return m_y;
}

int Button::get_width()
{
	return m_w;
}

int Button::get_height()
{
	return m_h;
}

void Button::move(int x, int y)
{
	m_x = x;
	m_y = y;
}

void Button::setSize(int w, int h)
{
	m_w = w;
	m_h = h;
}

void Button::drawButton()
{
	setfillcolor(cur_c);
	fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	settextcolor(BLACK);
	//文字居中
	int tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	outtextxy(tx, ty, m_text.c_str());
}

bool Button::hasMsg()
{
	return peekmessage(&m_msg, EX_MOUSE | EX_KEY);//若有鼠标或者键盘消息，返回给m_msg
}

ExMessage& Button::getMsg()
{
	return m_msg;
}

bool Button::isPushed()
{
	//先判断在不在按钮上
	bool isIn = false;
	if (m_msg.x >= m_x && m_msg.x <= m_x + m_w && m_msg.y >= m_y && m_msg.y <= m_y + m_h)
	{
		isIn = true;
	}

	cur_c = normol_c;
	//再判断有没有按下左键
	if (isIn)
	{
		cur_c = change_c;
		drawButton();
		if (m_msg.message == WM_LBUTTONDOWN)
		{
			return true;
		}
	}
	return false;
}
