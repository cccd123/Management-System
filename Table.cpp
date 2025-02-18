#include "Table.h"
#include"Person.h"

Table::Table(int row, int col)
	:m_row(row), m_col(col)
{}

void Table::move(int x, int y)
{
	m_x = x;
	m_y = y;
}

void Table::setTable(int row, int col)
{
	m_row = row;
	m_col = col;
	//settextstyle(20, 0, "楷体");
	m_gw = textwidth("计算机类一班");
	m_gh = textheight("计算机类一班");
	int x = (getwidth() - m_col * m_gw) / 2;
	int y = (getheight() - m_row * m_gh) / 2;
	move(x, y);
}

void Table::setHeader(const string& header)
{
	m_header = header;
	//统计表头中的'\t’数目，从而确定列数
	m_col = count(m_header.begin(), m_header.end(), '\t') + 1;
	//cout << m_col << endl;
	//文字的高度和高度
	m_gw = textwidth("计算机2023级");
	m_gh = textheight(m_header.c_str());
}

 void Table::drawData(vector<Person*> p)
{
	//绘制表头
	outtextxy(m_x, m_y, "姓名");
	outtextxy(m_x + m_gw, m_y, "生日");
	outtextxy(m_x + 2 * m_gw, m_y, "电话号码");
	outtextxy(m_x + 3 * m_gw, m_y, "邮箱");
	outtextxy(m_x + 4 * m_gw, m_y, "关系");
	outtextxy(m_x + 5 * m_gw, m_y, "更多信息");

	//绘制数据
	for (int i = 0;i < p.size();i++)
	{
		int x = m_x;
		int y = m_y + (i + 1) * m_gh;
		int w = m_gw;
		outtextxy(x, y, (p[i]->name).c_str());
		Outtextxy(x + w, y, p[i]->birthday);
		outtextxy(x + 2 * w, y, (p[i]->phone_num).c_str());
		outtextxy(x + 3 * w, y, (p[i]->email).c_str());
		outtextxy(x + 4 * w, y, (p[i]->relate).c_str());
		outtextxy(x + 5 * w, y, (p[i]->more).c_str());
	}
}


void Table::drawTable(vector<Person*> p)
{
	//画横线
	setlinecolor(BLUE);
	for (int i = 0;i < m_row + 1 + 1;i++)
	{
		line(m_x, m_y + i * m_gh, m_x + m_col * m_gw, m_y + i * m_gh);
	}
	//画竖线
	for (int i = 0;i < m_col + 1;i++)
	{
		line(m_x + i * m_gw, m_y, m_x + i * m_gw, m_y + (m_row + 1) * m_gh);
	}
	drawData(p);
}
