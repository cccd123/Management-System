#include"Person.h"
#include"Table.h"

int Person::total = 0;
HWND Person::m_handle;

void add(Person*& L, Person*& ptr)//默认先按姓名排序(搜索插入)
{
	Button* choice;
	choice = new Button("添加", 200, 60, 150, 30);
	choice->drawButton();
	
	if (choice->isPushed())
	{//输入信息
		char s[20];
		InputBox(s, 20, "请输入要添加的联系人的名字:");
		ptr->name = s;

		int _year = 0, _month = 0, _day = 0;
		InputBox(s, 20, "请输入生日(**年):");
		for (int i = 0;i < strlen(s);i++)
		{
			_year = _year * 10 + int(s[i] - '0');
		}
		InputBox(s, 20, "请输入生日(**月):");
		for (int i = 0;i < strlen(s);i++)
		{
			_month = _month * 10 + int(s[i] - '0');
		}
		InputBox(s, 20, "请输入生日(**日):");
		for (int i = 0;i < strlen(s);i++)
		{
			_day = _day * 10 + int(s[i] - '0');
		}
		ptr->birthday = Date(_year, _month, _day);
		if (!ptr->birthday.date_correct())
		{
			MessageBox(Person::m_handle, "输入的时间错误!", "EEROR", MB_OK);
			return;
		}

		InputBox(s, 20, "请输入电话号码:");
		ptr->phone_num = s;
		InputBox(s, 20, "请输入邮箱:");
		ptr->email = s;
		if (ptr->relate == "朋友")
			InputBox(s, 20, "请输入认识地点:");
		if (ptr->relate == "同学")
			InputBox(s, 20, "请输入学校:");
		if (ptr->relate == "同事")
			InputBox(s, 20, "请输入共事单位:");
		if (ptr->relate == "亲戚")
			InputBox(s, 20, "请输入称呼:");
		ptr->more = s;

		ptr->next = NULL;
		Person* q, * p;
		for (q = L, p = L->next; p;q = p, p = p->next)
		{
			if (ptr->name < p->name)
			{
				ptr->next = p;
				q->next = ptr;
				outtextxy(480, 320, "已成功添加联系人的信息!");
				FlushBatchDraw();
				Sleep(3000);
				L->total++;
				ptr = 0;
				return;
			}
		}
		q->next = ptr;
		outtextxy(480, 320, "已成功添加联系人的信息!");
		FlushBatchDraw();
		Sleep(3000);
		ptr = 0;
		return;
	}
}

void display(Person* L)
{
	if (L->next == NULL)
	{
		outtextxy(200, 100, "联系人列表为空!");
		return;
	}
	Button* choice1;
	choice1 = new Button("显示全部列表", 0, 0, 150, 30);
	choice1->drawButton();
	Button* choice2;
	choice2 = new Button("显示朋友列表", 0, 40, 150, 30);
	choice2->drawButton();
	Button* choice3;
	choice3 = new Button("显示同学列表", 0, 80, 150, 30);
	choice3->drawButton();
	Button* choice4;
	choice4 = new Button("显示同事列表", 0, 120, 150, 30);
	choice4->drawButton();
	Button* choice5;
	choice5 = new Button("显示亲戚列表", 0, 160, 150, 30);
	choice5->drawButton();
	
	string str;int t = 0;
	if (choice1->isPushed())
	{
		t = 1;
	}
	if (choice2->isPushed())
	{
		str = "朋友";
	}
	if (choice3->isPushed())
	{
		str = "同学";
	}
	if (choice4->isPushed())
	{
		str = "同事";
	}
	if (choice5->isPushed())
	{
		str = "亲戚";
	}
	int count = 0;
	vector<Person*> contacts;Table m_table;
	Person* p = L->next;

	while (p)
	{
		if (t || p->relate == str)//条件变换
		{
			++count;
			contacts.push_back(p);
		}
		p = p->next;
	}
	if (count == 0)
		outtextxy(200, 100, "要找的联系人列表为空!");
	else
	{
		m_table.setTable(contacts.size(), 6);
		m_table.drawTable(contacts);
		outtextxy(200, 100, "联系人总数为:");
		TCHAR s[3];
		_stprintf(s, "%d", count);
		outtextxy(300, 100, s);
		FlushBatchDraw();
		Sleep(2500);
	}
	return;
}

void search(Person* L)
{
	Button* choice;
	choice = new Button("姓名查询", 0, 0, 150, 30);
	choice->drawButton();

	static char pname[20];
	if (choice->isPushed())
	{
		InputBox(pname, 20, "请输入要查找的联系人的名字:");
	}

	Person* p = L->next;
	while (p)
	{
		if (p->name == pname)
		{
			vector<Person*> contacts;
			contacts.push_back(p);

			Table m_table;
			m_table.setTable(contacts.size(), 6);
			m_table.drawTable(contacts);
			FlushBatchDraw();
			return;
		}
		p = p->next;
	}
	if (!p)
	{
		outtextxy(100, 100, "查无此人!");
	}
	return;
}
void del(Person*& L)
{
	Button* choice;
	choice = new Button("姓名查询", 0, 0, 150, 30);
	choice->drawButton();

	char pname[20];
	if (choice->isPushed())
	{
		InputBox(pname, 20, "请输入要删除的联系人的名字:");
	}

	Person* q, * p;
	for (q = L, p = L->next; p;q = p, p = p->next)
	{
		if (p->name == pname)
		{
			//搜索到该联系人，先显示一下信息
			vector<Person*> contacts;
			contacts.push_back(p);

			Table m_table;
			m_table.setTable(contacts.size(), 6);
			m_table.drawTable(contacts);

			FlushBatchDraw();

		//是否确认修改
			if (MessageBox(Person::m_handle, "是否确认删除", "已找到联系人", MB_YESNO) == IDYES)
			{
				q->next = p->next;
				delete p;
				p = NULL;
				L->total--;

				outtextxy(100, 100, "联系人已被删除");
				FlushBatchDraw();
				Sleep(3000);
			}
			else
			{
				outtextxy(100, 100, "联系人未被删除");
				FlushBatchDraw();
				Sleep(3000);
			}

			return;
		}
	}
	if (!p)
	{
		outtextxy(100, 100, "查无此人!");
	}
	return;
}
void revise(Person*& L)
{
	Button* choice;
	choice = new Button("姓名查询", 0, 0, 150, 30);
	choice->drawButton();

	char pname[20];
	if (choice->isPushed())
	{
		InputBox(pname, 20, "请输入要修改的联系人的名字:");
	}

	Person* p = L->next;
	while (p)
	{
		if (p->name == pname)
		{
			//搜索到该联系人，先显示一下信息
			vector<Person*> contacts;
			contacts.push_back(p);

			Table m_table;
			m_table.setTable(contacts.size(), 6);
			m_table.drawTable(contacts);

			FlushBatchDraw();

			char choice[2];
			if (p->relate == "朋友")
				InputBox(choice, 2, "选择更改电话,请输入1;\n选择更改邮箱,请输入2;\n选择修改认识地点，请输入3:\n");
			if (p->relate == "同学")
				InputBox(choice, 2, "选择更改电话,请输入1;\n选择更改邮箱,请输入2;\n选择修改学校，请输入3:\n");
			if (p->relate == "同事")
				InputBox(choice, 2, "选择更改电话,请输入1;\n选择更改邮箱,请输入2;\n选择修改共事单位，请输入3:\n");
			if (p->relate == "亲戚")
				InputBox(choice, 2, "选择更改电话,请输入1;\n选择更改邮箱,请输入2;\n选择修改称呼，请输入3:\n");

			char s[80];
			InputBox(s, 80, "请输入修改信息");

			switch (choice[0])
			{
			case'1':
				p->phone_num = s;
				break;
			case'2':
				p->email = s;
				break;
			case'3':
				p->more = s;
			}

			//是否确认修改
			if (MessageBox(Person::m_handle, "是否确认修改", "已找到联系人", MB_YESNO) == IDYES)
			{

				outtextxy(100, 100, "联系人已被修改");
				FlushBatchDraw();
				Sleep(3000);
			}
			else
			{
				outtextxy(100, 100, "联系人未被修改");
				FlushBatchDraw();
				Sleep(3000);
			}
			return;
		}
		p = p->next;
	}
	if (!p)
	{
		outtextxy(100, 100, "查无此人!");
	}
	return;
}
void clear(Person*& L)
{
	if (L->next == NULL)
	{
		outtextxy(100, 100, "通讯录已为空!");
		return;
	}

	Button* choice;
	choice = new Button("确认清空", 0, 0, 150, 30);
	choice->drawButton();

	if (choice->isPushed())
	{
		Person* p = L->next;
		p->next = NULL;
		while (p)
		{
			L->next = p->next;
			delete p;
			p = NULL;
			p = L->next;
		}
		outtextxy(100, 100, "已成功清空通讯录列表!");
		Sleep(2000);
	}
	
	return;
}


void sort(Person* L)
{
	Button* choice1;
	choice1 = new Button("按姓名排序", 200, 0, 150, 30);
	choice1->drawButton();

	Button* choice2;
	choice2 = new Button("按生日排序", 400, 0, 150, 30);
	choice2->drawButton();

	Person* prep, * curp, * nextp, * end = NULL;
	int t = 0;
	if (choice1->isPushed())
	{
		t = 1;
	}
	if (choice2->isPushed())
	{
		t = 2;
	}
	if (t)
	{
		while (L->next != end) //冒泡排序
		{
			int work = 1;
			for (prep = L, curp = L->next, nextp = L->next->next;nextp != end;prep = prep->next, curp = curp->next, nextp = nextp->next)
			{
				if (t == 1 ? curp->name > nextp->name:comp(curp->birthday, nextp->birthday) == 1)//条件变换
				{
					prep->next = nextp;
					curp->next = nextp->next;
					nextp->next = curp;
					Person* temp = curp;
					curp = nextp;
					nextp = temp;
					work = 0;
				}
			}
			if (work)
				break;
			end = curp;
		}
		FlushBatchDraw();
	}
}

void Birthday_search(Person* L)
{
	Button* choice1;
	choice1 = new Button("按月份查找", 0, 0, 150, 30);
	choice1->drawButton();

	Button* choice2;
	choice2 = new Button("按五天之内查找", 200, 0, 150, 30);
	choice2->drawButton();
	Person* q, * p;

	int _year = 0, _month = 0, _day = 0;
	int count = 0;//在该段时间内生日的人数
	vector<Person*> contacts; Table m_table;

	if (choice1->isPushed())
	{
		char choice[3];
		InputBox(choice, 3, "请输入月份:");
		for (int i = 0;i < strlen(choice);i++)
		{
			_month = _month * 10 + int(choice[i] - '0');
		}
		for (q = L, p = L->next; p;q = p, p = p->next)
		{
			if (p->birthday.get_month() == _month)
			{
				contacts.push_back(p);
				count++;
			}
		}
		m_table.setTable(contacts.size(), 6);
		m_table.drawTable(contacts);
		outtextxy(100, 160, "在该月生日的总人数有:");
		TCHAR s[3];
		_stprintf(s, "%d", count);
		outtextxy(280, 160, s);
		FlushBatchDraw();
		Sleep(3000);
	}
	if (choice2->isPushed())
	{
		char choice[5];
		InputBox(choice, 5, "请输入今天的日期(**年):");
		for (int i = 0;i < strlen(choice);i++)
		{
			_year = _year * 10 + int(choice[i] - '0');
		}
		InputBox(choice, 5, "请输入今天的日期(**月):");
		for (int i = 0;i < strlen(choice);i++)
		{
			_month = _month * 10 + int(choice[i] - '0');
		}
		InputBox(choice, 5, "请输入今天的日期(**日):");
		for (int i = 0;i < strlen(choice);i++)
		{
			_day = _day * 10 + int(choice[i] - '0');
		}
		Date today(_year, _month, _day);
		if (!today.date_correct())
		{
			MessageBox(Person::m_handle, "输入的时间错误!", "EEROR", MB_OK);
			return;
		}

		for (q = L, p = L->next; p;q = p, p = p->next)
		{
			Date p1_equal = Date(today.increase(5).get_year(), p->birthday.get_month(), p->birthday.get_day());
			int t1 = !(comp(p1_equal, today) == -1);
			int q1 = !(comp(p1_equal, today.increase(5)) == 1);

			Date p2_equal = Date(today.get_year(), p->birthday.get_month(), p->birthday.get_day());
			int t2 = !(comp(p2_equal, today) == -1);
			int q2 = !(comp(p2_equal, today.increase(5)) == 1);
			if (t1 && q1 || t2 && q2)//在给定日期五日之内
			{
				contacts.push_back(p);
				count++;
			}
		}
		m_table.setTable(contacts.size(), 6);
		m_table.drawTable(contacts);
		outtextxy(100, 160, "在五天之内生日的总人数有:");
		TCHAR s[3];
		_stprintf(s, "%d", count);
		outtextxy(300, 160, s);
		FlushBatchDraw();
		Sleep(5000);
	}

	if (count)
	{
		//发送贺卡
		char choice[3];	int n = 0;
		InputBox(choice, 3, "请输入想要发送贺卡的人数:");
		for (int i = 0;i < strlen(choice);i++)
		{
			n = n * 10 + int(choice[i] - '0');
		}
		while (n--)
		{
			char name[20];
			InputBox(name, 20, "请输入想要发送贺卡的人名:");
			Greeting_card card;
			card.show(string(name));
		}
	}
}

Person::Person(string name, Date birthday, string phone_num, string email, string relate, string more)
	:name(name), birthday(birthday), phone_num(phone_num), email(email), relate(relate), more(more)
{
}
