#include"Person.h"
#include"Table.h"

int Person::total = 0;
HWND Person::m_handle;

void add(Person*& L, Person*& ptr)//Ĭ���Ȱ���������(��������)
{
	Button* choice;
	choice = new Button("���", 200, 60, 150, 30);
	choice->drawButton();
	
	if (choice->isPushed())
	{//������Ϣ
		char s[20];
		InputBox(s, 20, "������Ҫ��ӵ���ϵ�˵�����:");
		ptr->name = s;

		int _year = 0, _month = 0, _day = 0;
		InputBox(s, 20, "����������(**��):");
		for (int i = 0;i < strlen(s);i++)
		{
			_year = _year * 10 + int(s[i] - '0');
		}
		InputBox(s, 20, "����������(**��):");
		for (int i = 0;i < strlen(s);i++)
		{
			_month = _month * 10 + int(s[i] - '0');
		}
		InputBox(s, 20, "����������(**��):");
		for (int i = 0;i < strlen(s);i++)
		{
			_day = _day * 10 + int(s[i] - '0');
		}
		ptr->birthday = Date(_year, _month, _day);
		if (!ptr->birthday.date_correct())
		{
			MessageBox(Person::m_handle, "�����ʱ�����!", "EEROR", MB_OK);
			return;
		}

		InputBox(s, 20, "������绰����:");
		ptr->phone_num = s;
		InputBox(s, 20, "����������:");
		ptr->email = s;
		if (ptr->relate == "����")
			InputBox(s, 20, "��������ʶ�ص�:");
		if (ptr->relate == "ͬѧ")
			InputBox(s, 20, "������ѧУ:");
		if (ptr->relate == "ͬ��")
			InputBox(s, 20, "�����빲�µ�λ:");
		if (ptr->relate == "����")
			InputBox(s, 20, "������ƺ�:");
		ptr->more = s;

		ptr->next = NULL;
		Person* q, * p;
		for (q = L, p = L->next; p;q = p, p = p->next)
		{
			if (ptr->name < p->name)
			{
				ptr->next = p;
				q->next = ptr;
				outtextxy(480, 320, "�ѳɹ������ϵ�˵���Ϣ!");
				FlushBatchDraw();
				Sleep(3000);
				L->total++;
				ptr = 0;
				return;
			}
		}
		q->next = ptr;
		outtextxy(480, 320, "�ѳɹ������ϵ�˵���Ϣ!");
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
		outtextxy(200, 100, "��ϵ���б�Ϊ��!");
		return;
	}
	Button* choice1;
	choice1 = new Button("��ʾȫ���б�", 0, 0, 150, 30);
	choice1->drawButton();
	Button* choice2;
	choice2 = new Button("��ʾ�����б�", 0, 40, 150, 30);
	choice2->drawButton();
	Button* choice3;
	choice3 = new Button("��ʾͬѧ�б�", 0, 80, 150, 30);
	choice3->drawButton();
	Button* choice4;
	choice4 = new Button("��ʾͬ���б�", 0, 120, 150, 30);
	choice4->drawButton();
	Button* choice5;
	choice5 = new Button("��ʾ�����б�", 0, 160, 150, 30);
	choice5->drawButton();
	
	string str;int t = 0;
	if (choice1->isPushed())
	{
		t = 1;
	}
	if (choice2->isPushed())
	{
		str = "����";
	}
	if (choice3->isPushed())
	{
		str = "ͬѧ";
	}
	if (choice4->isPushed())
	{
		str = "ͬ��";
	}
	if (choice5->isPushed())
	{
		str = "����";
	}
	int count = 0;
	vector<Person*> contacts;Table m_table;
	Person* p = L->next;

	while (p)
	{
		if (t || p->relate == str)//�����任
		{
			++count;
			contacts.push_back(p);
		}
		p = p->next;
	}
	if (count == 0)
		outtextxy(200, 100, "Ҫ�ҵ���ϵ���б�Ϊ��!");
	else
	{
		m_table.setTable(contacts.size(), 6);
		m_table.drawTable(contacts);
		outtextxy(200, 100, "��ϵ������Ϊ:");
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
	choice = new Button("������ѯ", 0, 0, 150, 30);
	choice->drawButton();

	static char pname[20];
	if (choice->isPushed())
	{
		InputBox(pname, 20, "������Ҫ���ҵ���ϵ�˵�����:");
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
		outtextxy(100, 100, "���޴���!");
	}
	return;
}
void del(Person*& L)
{
	Button* choice;
	choice = new Button("������ѯ", 0, 0, 150, 30);
	choice->drawButton();

	char pname[20];
	if (choice->isPushed())
	{
		InputBox(pname, 20, "������Ҫɾ������ϵ�˵�����:");
	}

	Person* q, * p;
	for (q = L, p = L->next; p;q = p, p = p->next)
	{
		if (p->name == pname)
		{
			//����������ϵ�ˣ�����ʾһ����Ϣ
			vector<Person*> contacts;
			contacts.push_back(p);

			Table m_table;
			m_table.setTable(contacts.size(), 6);
			m_table.drawTable(contacts);

			FlushBatchDraw();

		//�Ƿ�ȷ���޸�
			if (MessageBox(Person::m_handle, "�Ƿ�ȷ��ɾ��", "���ҵ���ϵ��", MB_YESNO) == IDYES)
			{
				q->next = p->next;
				delete p;
				p = NULL;
				L->total--;

				outtextxy(100, 100, "��ϵ���ѱ�ɾ��");
				FlushBatchDraw();
				Sleep(3000);
			}
			else
			{
				outtextxy(100, 100, "��ϵ��δ��ɾ��");
				FlushBatchDraw();
				Sleep(3000);
			}

			return;
		}
	}
	if (!p)
	{
		outtextxy(100, 100, "���޴���!");
	}
	return;
}
void revise(Person*& L)
{
	Button* choice;
	choice = new Button("������ѯ", 0, 0, 150, 30);
	choice->drawButton();

	char pname[20];
	if (choice->isPushed())
	{
		InputBox(pname, 20, "������Ҫ�޸ĵ���ϵ�˵�����:");
	}

	Person* p = L->next;
	while (p)
	{
		if (p->name == pname)
		{
			//����������ϵ�ˣ�����ʾһ����Ϣ
			vector<Person*> contacts;
			contacts.push_back(p);

			Table m_table;
			m_table.setTable(contacts.size(), 6);
			m_table.drawTable(contacts);

			FlushBatchDraw();

			char choice[2];
			if (p->relate == "����")
				InputBox(choice, 2, "ѡ����ĵ绰,������1;\nѡ���������,������2;\nѡ���޸���ʶ�ص㣬������3:\n");
			if (p->relate == "ͬѧ")
				InputBox(choice, 2, "ѡ����ĵ绰,������1;\nѡ���������,������2;\nѡ���޸�ѧУ��������3:\n");
			if (p->relate == "ͬ��")
				InputBox(choice, 2, "ѡ����ĵ绰,������1;\nѡ���������,������2;\nѡ���޸Ĺ��µ�λ��������3:\n");
			if (p->relate == "����")
				InputBox(choice, 2, "ѡ����ĵ绰,������1;\nѡ���������,������2;\nѡ���޸ĳƺ���������3:\n");

			char s[80];
			InputBox(s, 80, "�������޸���Ϣ");

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

			//�Ƿ�ȷ���޸�
			if (MessageBox(Person::m_handle, "�Ƿ�ȷ���޸�", "���ҵ���ϵ��", MB_YESNO) == IDYES)
			{

				outtextxy(100, 100, "��ϵ���ѱ��޸�");
				FlushBatchDraw();
				Sleep(3000);
			}
			else
			{
				outtextxy(100, 100, "��ϵ��δ���޸�");
				FlushBatchDraw();
				Sleep(3000);
			}
			return;
		}
		p = p->next;
	}
	if (!p)
	{
		outtextxy(100, 100, "���޴���!");
	}
	return;
}
void clear(Person*& L)
{
	if (L->next == NULL)
	{
		outtextxy(100, 100, "ͨѶ¼��Ϊ��!");
		return;
	}

	Button* choice;
	choice = new Button("ȷ�����", 0, 0, 150, 30);
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
		outtextxy(100, 100, "�ѳɹ����ͨѶ¼�б�!");
		Sleep(2000);
	}
	
	return;
}


void sort(Person* L)
{
	Button* choice1;
	choice1 = new Button("����������", 200, 0, 150, 30);
	choice1->drawButton();

	Button* choice2;
	choice2 = new Button("����������", 400, 0, 150, 30);
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
		while (L->next != end) //ð������
		{
			int work = 1;
			for (prep = L, curp = L->next, nextp = L->next->next;nextp != end;prep = prep->next, curp = curp->next, nextp = nextp->next)
			{
				if (t == 1 ? curp->name > nextp->name:comp(curp->birthday, nextp->birthday) == 1)//�����任
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
	choice1 = new Button("���·ݲ���", 0, 0, 150, 30);
	choice1->drawButton();

	Button* choice2;
	choice2 = new Button("������֮�ڲ���", 200, 0, 150, 30);
	choice2->drawButton();
	Person* q, * p;

	int _year = 0, _month = 0, _day = 0;
	int count = 0;//�ڸö�ʱ�������յ�����
	vector<Person*> contacts; Table m_table;

	if (choice1->isPushed())
	{
		char choice[3];
		InputBox(choice, 3, "�������·�:");
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
		outtextxy(100, 160, "�ڸ������յ���������:");
		TCHAR s[3];
		_stprintf(s, "%d", count);
		outtextxy(280, 160, s);
		FlushBatchDraw();
		Sleep(3000);
	}
	if (choice2->isPushed())
	{
		char choice[5];
		InputBox(choice, 5, "��������������(**��):");
		for (int i = 0;i < strlen(choice);i++)
		{
			_year = _year * 10 + int(choice[i] - '0');
		}
		InputBox(choice, 5, "��������������(**��):");
		for (int i = 0;i < strlen(choice);i++)
		{
			_month = _month * 10 + int(choice[i] - '0');
		}
		InputBox(choice, 5, "��������������(**��):");
		for (int i = 0;i < strlen(choice);i++)
		{
			_day = _day * 10 + int(choice[i] - '0');
		}
		Date today(_year, _month, _day);
		if (!today.date_correct())
		{
			MessageBox(Person::m_handle, "�����ʱ�����!", "EEROR", MB_OK);
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
			if (t1 && q1 || t2 && q2)//�ڸ�����������֮��
			{
				contacts.push_back(p);
				count++;
			}
		}
		m_table.setTable(contacts.size(), 6);
		m_table.drawTable(contacts);
		outtextxy(100, 160, "������֮�����յ���������:");
		TCHAR s[3];
		_stprintf(s, "%d", count);
		outtextxy(300, 160, s);
		FlushBatchDraw();
		Sleep(5000);
	}

	if (count)
	{
		//���ͺؿ�
		char choice[3];	int n = 0;
		InputBox(choice, 3, "��������Ҫ���ͺؿ�������:");
		for (int i = 0;i < strlen(choice);i++)
		{
			n = n * 10 + int(choice[i] - '0');
		}
		while (n--)
		{
			char name[20];
			InputBox(name, 20, "��������Ҫ���ͺؿ�������:");
			Greeting_card card;
			card.show(string(name));
		}
	}
}

Person::Person(string name, Date birthday, string phone_num, string email, string relate, string more)
	:name(name), birthday(birthday), phone_num(phone_num), email(email), relate(relate), more(more)
{
}
