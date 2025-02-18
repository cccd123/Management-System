#pragma once

#include"Friend.h"
#include"Classmate.h"
#include"Colleague.h"
#include"Relative.h"

#include"Button.h"
#include"Table.h"

class Management
{
public:
	Management(); //初始化链表L，readfile；加载背景和绘制按钮

	~Management(); //savefile

	int menu(); //显示菜单，并根据按钮反应返回选择的操作

	void run();

	void readfile(string filename); //读取文件，并将联系人信息读进链表L中
	void savefile(string filename, string filename1, string filename2, string filename3, string filename4); //存储文件，将链表L的联系人信息写进文件（一个总文件，四个分类型联系人文件）
	static HWND m_handle;

private:
	Person* L;

	enum Operator
	{
		Add, Display, Sort, Search, Revise, Erase, Clear, SearchBirthday, Exit, Menu
	};
	
	ExMessage m_msg;
	vector<Button*> menu_btns;//菜单按钮

};

