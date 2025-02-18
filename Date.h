#ifndef __DATE_H__
#define __DATE_H__

#include"tools.h"

class Date
{
private:
	int year, month, day;
	friend class Management;

public:
	Date(int y = 0, int m = 0, int d = 0);

	friend istream& operator>>(istream& input, Date& A);
	friend ostream& operator<<(ostream& output, const Date& A);

	int get_year();
	int get_month();
	int get_day();

	bool date_correct(); //判断输入日期是否合理
	friend int comp(Date A, Date B);//比较日期大小(A>B返回1,A<B返回-1，相等则返回0)
	void Caculate(); //计算今天是星期几
	Date increase(int days); //计算days天后的日期

	friend void Outtextxy(int x, int y, const Date& a);//相当于重载eaxyx中对Date对象的outtextxy函数
};

#endif
