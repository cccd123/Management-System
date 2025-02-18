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

	bool date_correct(); //�ж����������Ƿ����
	friend int comp(Date A, Date B);//�Ƚ����ڴ�С(A>B����1,A<B����-1������򷵻�0)
	void Caculate(); //������������ڼ�
	Date increase(int days); //����days��������

	friend void Outtextxy(int x, int y, const Date& a);//�൱������eaxyx�ж�Date�����outtextxy����
};

#endif
