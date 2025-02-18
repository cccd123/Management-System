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
	Management(); //��ʼ������L��readfile�����ر����ͻ��ư�ť

	~Management(); //savefile

	int menu(); //��ʾ�˵��������ݰ�ť��Ӧ����ѡ��Ĳ���

	void run();

	void readfile(string filename); //��ȡ�ļ���������ϵ����Ϣ��������L��
	void savefile(string filename, string filename1, string filename2, string filename3, string filename4); //�洢�ļ���������L����ϵ����Ϣд���ļ���һ�����ļ����ĸ���������ϵ���ļ���
	static HWND m_handle;

private:
	Person* L;

	enum Operator
	{
		Add, Display, Sort, Search, Revise, Erase, Clear, SearchBirthday, Exit, Menu
	};
	
	ExMessage m_msg;
	vector<Button*> menu_btns;//�˵���ť

};

