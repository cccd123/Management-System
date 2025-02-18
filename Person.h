#ifndef __PERSON_H__
#define __PERSON_H__

#include"date.h"
#include"Greeting_card.h"
#include"Button.h""

class Person
{
protected:
	string name;
	Date birthday;
	string phone_num;
	string email;
	string relate;//联系人类型
	string more;//更多信息，这里以more来统领朋友的认识地点、同学的学校、同事的单位以及亲戚的称呼，使功能代码易于书写，同时不影响对各派生类more信息的区分
	static int total;//统计联系人总数

	friend class Management;
	static HWND m_handle;//窗口句柄，在messagebox中要用到，这里从management类中取值过来
	friend class Table;

public:
	Person* next;

	Person(string name=" ", Date birthday = (0, 0, 0), string phone_num=" ", string email=" ", string relate=" ", string more=" ");

	friend void add(Person*& L, Person*& ptr); //添加联系人
	friend void display(Person* L);            //显示联系人
	friend void search(Person* L);             //搜索联系人
	friend void del(Person*& L);               //删除联系人
	friend void revise(Person*& L);            //修改联系人
	friend void clear(Person*& L);             //清空联系人
	friend void sort(Person* L);               //排序（姓名排序、生日排序）
	friend void Birthday_search(Person* L);    //查找寿星
};

#endif
