#include"Date.h"

Date::Date(int y, int m, int d)
	:year(y), month(m), day(d)
{
}

istream& operator>>(istream& input, Date& A)
{
	if (!dynamic_cast<std::ifstream*>(&input))
		cout << "年:";
	input >> A.year;
	if (!dynamic_cast<std::ifstream*>(&input))
		cout << "月:";
	input >> A.month;
	if (!dynamic_cast<std::ifstream*>(&input))
		cout << "日:";
	input >> A.day;
	return input;
}

ostream& operator<<(ostream& output, const Date& A)
{
	if (dynamic_cast<std::ofstream*>(&output))
	{
		output << A.year << A.month << A.day;
	}
	else
	{
		output << A.year << "年" << A.month << "月" << A.day << "日";
	}
	return output;
}

int Date::get_month()
{
	return month;
}

int Date::get_day()
{
	return day;
}

int Date::get_year()
{
	return year;
}

void Date::Caculate()
{
	int y = year, m = month, d = day;
	if (m == 1 || m == 2)
	{
		m += 12;
		y--;
	}
	int weektime = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
	switch (weektime)
	{
	case 0:
		cout << "星期一";
		break;
	case 1:
		cout << "星期二";
		break;
	case 2:
		cout << "星期三";
		break;
	case 3:
		cout << "星期四";
		break;
	case 4:
		cout << "星期五";
		break;
	case 5:
		cout << "星期六";
		break;
	case 6:
		cout << "星期日";
		break;
	}
}
// 检查是否为闰年
bool isLeapYear(int y)
{
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// 获取每个月的天数
int daysInMonth(int y, int m)
{
	static const int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (m == 2 && isLeapYear(y)) return 29;
	return days[m - 1];
}

bool Date::date_correct() //判断月或者日是否合理
{
	if (month < 1 || month>12)
		return 0;
	if (month == 2)
	{
		if (isLeapYear(year))
		{
			if (day < 1 || day>29)
				return 0;
		}
		else
		{
			if (day < 1 || day>28)
				return 0;
		}
	}
	else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		if (day < 1 || day>31)
			return 0;
	}
	else
	{
		if (day < 1 || day>30)
			return 0;
	}
	return 1;
}

Date Date::increase(int days)
{
	// 计算n天后的日期
	int y = year, m = month, d = day;
	d += days;
	while (d > daysInMonth(y, m)) {
		d -= daysInMonth(y, m);
		m++;
		if (m > 12) {
			m = 1;
			y++;
		}
	}
	return Date(y, m, d);
}

int comp(Date A, Date B)
{
	if (A.year > B.year)
	{
		return 1;
	}
	else if (A.year < B.year)
	{
		return -1;
	}
	else
	{
		if (A.month > B.month)
		{
			return 1;
		}
		else if (A.month < B.month)
		{
			return -1;
		}
		else
		{
			if (A.day > B.day)
			{
				return 1;
			}
			else if (A.day < B.day)
			{
				return -1;
			}
			else return 0;
		}
	}
}

void Outtextxy(int x, int y, const Date& a)
{
	string s, ay, am, ad;
	ay = to_string(a.year);
	am = to_string(a.month);
	ad = to_string(a.day);
	s = ay + "年" + am + "月" + ad + "日";
	outtextxy(x, y, s.c_str());
}




