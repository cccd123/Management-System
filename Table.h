#pragma once

#include"tools.h"
#include"Date.h"
#include"Person.h"

class Table
{
public:
	Table(int row = 0, int col = 0);
	void move(int x = 0, int y = 0);
	void setTable(int row, int col);
	void setHeader(const string& header);
	void drawData(vector<Person*> p);
	void drawTable(vector<Person*> p);
	

public:
	int m_x, m_y;//�������϶��������
	int m_row, m_col;
	int m_gw, m_gh;//���ӵĿ�Ⱥ͸߶�
	string m_header;

	friend class Management;
};

