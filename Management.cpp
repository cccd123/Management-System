#include "Management.h"

HWND Management::m_handle;

IMAGE m_bk;

Management::Management()
{
	//�½�һ����ͷ������ϵ������
	L = new Person;
	L->next = NULL;

	//��ȡ�ı���Ϣ����ϵ��������
	readfile("Contacts.txt");

	//���ر���
	m_handle = initgraph(960, 640, EX_SHOWCONSOLE);
	Person::m_handle = m_handle;
	loadimage(&m_bk, "bk.jpeg", getwidth(), getheight());

	//�����水ť��ʼ��
	menu_btns.push_back(new Button("�����ϵ��"));
	menu_btns.push_back(new Button("��ʾ��ϵ��"));
	menu_btns.push_back(new Button("������ϵ��"));
	menu_btns.push_back(new Button("������ϵ��"));
	menu_btns.push_back(new Button("�޸���ϵ��"));
	menu_btns.push_back(new Button("ɾ����ϵ��"));
	menu_btns.push_back(new Button("���ͨѶ¼"));
	menu_btns.push_back(new Button("��������"));
	menu_btns.push_back(new Button("�˳�ϵͳ"));
	for (int i = 0;i < menu_btns.size();i++)
	{
		menu_btns[i]->setSize(260, 50);
		int bx = (getwidth() - menu_btns[i]->get_width()) / 2;
		int vspace = (getheight() - menu_btns[i]->get_height() * menu_btns.size()) / 2;
		int by = vspace + i * menu_btns[i]->get_height();
		menu_btns[i]->move(bx, by);//���д�ӡ����
	}
}

Management::~Management()
{
	//���ı���Ϣ�������ϵ���б���
	savefile("Contacts.txt", "Friend.txt", "Classmate.txt", "Colleague.txt", "Relative.txt");
}

int Management::menu()
{

	for (int i = 0;i < menu_btns.size();i++)
	{
		menu_btns[i]->drawButton();
	}
	for (int i = 0;i < menu_btns.size();i++)
	{
		if (menu_btns[i]->isPushed())
		{
			return i;
		}
	}
	return Menu;
}

void Management::run()
{
	int op = Menu;
	BeginBatchDraw();
	while (1)
	{
		cleardevice();
		putimage(0, 0, &m_bk);
		setbkmode(TRANSPARENT);
		outtextxy(0, 600, "���빦��ҳ�󣬰�ESC���Իص����˵�ҳ��");

		if (Button::hasMsg())
		{
			m_msg = Button::getMsg();//�����������Ϣ
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{//����������esc�����������˵�
				op = Menu;
			}
		}
		switch (op)
		{
		case Menu:
			op = menu();
			break;
		case Add:
		{   //���ư�ť
			Button* choice1, * choice2, * choice3, * choice4;
			choice1 = new Button("ѡ����������", 0, 0, 150, 30);
			choice1->drawButton();
			choice2 = new Button("ѡ��ͬѧ����", 0, 40, 150, 30);
			choice2->drawButton();
			choice3 = new Button("ѡ��ͬ������", 0, 80, 150, 30);
			choice3->drawButton();
			choice4 = new Button("ѡ����������", 0, 120, 150, 30);
			choice4->drawButton();

			static Person* ptr = 0; 
			if (choice1->isPushed())
			{
				delete ptr; //�½�֮ǰҪ��delete���ͷ�ԭ���Ŀռ䣬��й¶
				ptr = new Friend;
				ptr->relate = "����";
			}
			if (choice2->isPushed())
			{
				delete ptr;
				ptr = new Classmate;
				ptr->relate = "ͬѧ";
			}
			if (choice3->isPushed())
			{
				delete ptr;
				ptr = new Colleague;
				ptr->relate = "ͬ��";
			}
			if (choice4->isPushed())
			{
				delete ptr;
				ptr = new Relative;
				ptr->relate = "����";
			}
			//Ҫ��ѡ������,��������Ӧ�Ŀռ�,����������Ϣ�����ϵ��
			add(L, ptr);
		}
		break;
		case Display:
			display(L);
			break;
		case Sort:
			sort(L);
			display(L);
			break;
		case Search:
			search(L);
			break;
		case Revise:
			revise(L);
			break;
		case Erase:
			del(L);
			break;
		case Clear:
			clear(L);
			break;
		case SearchBirthday:
			Birthday_search(L);
			break;
		case Exit:
			system("cls");
			return;
		}
		FlushBatchDraw();
		//Button::getMsg().message = 0;
	}
	EndBatchDraw();
}

void Management::readfile(string filename)
{
	Person p, * ptr = NULL;

	ifstream infile(filename, ios::in);

	if (!infile)
	{
		cout << "�ļ���ʧ��!\n";
		exit(0);
	}

	infile.seekg(0, ios::beg);
	char s[100];
	infile.getline(s, 100);//��ȥ������
	
	while (infile >> p.name >> p.birthday >> p.phone_num >> p.email >> p.relate >> p.more)
	{
		if (p.relate == "����")
			ptr = new Friend(p.name, p.birthday, p.phone_num, p.email, p.relate, p.more);
		if (p.relate == "ͬѧ")
			ptr = new Classmate(p.name, p.birthday, p.phone_num, p.email, p.relate, p.more);
		if (p.relate == "ͬ��")
			ptr = new Colleague(p.name, p.birthday, p.phone_num, p.email, p.relate, p.more);
		if (p.relate == "����")
			ptr = new Relative(p.name, p.birthday, p.phone_num, p.email, p.relate, p.more);

		//ͷ�巨�ٷ�ת
		ptr->next = L->next;
		L->next = ptr;
	}
	
	//��ת
	Person* pre = NULL;
	Person* cur = NULL;
	if (L->next) {
		Person* pre = L->next;
		Person* cur = L->next->next;
	}
	while (cur)
	{
		pre->next = cur->next;
		cur->next = L->next;
		L->next = cur;
		cur = pre->next;
	}
	
	infile.close();
}

void Management::savefile(string filename, string filename1, string filename2, string filename3, string filename4)
{
	fstream outfile(filename, ios::out | ios::trunc);
	fstream outfile1(filename1, ios::out | ios::trunc);
	fstream outfile2(filename2, ios::out | ios::trunc);
	fstream outfile3(filename3, ios::out | ios::trunc);
	fstream outfile4(filename4, ios::out | ios::trunc);

	if (!outfile || !outfile1 || !outfile2 || !outfile3 || !outfile4)
	{
		cout << "�ļ���ʧ��!\n";
		exit(0);
	}

	outfile << "����\t����\t\t\t\t\t�绰����\t�����ʼ�\t��ϵ\t������Ϣ\n";//д�����
	outfile1 << "����\t����\t\t\t\t\t�绰����\t�����ʼ�\t��ϵ\t������Ϣ\n";
	outfile2 << "����\t����\t\t\t\t\t�绰����\t�����ʼ�\t��ϵ\t������Ϣ\n";
	outfile3 << "����\t����\t\t\t\t\t�绰����\t�����ʼ�\t��ϵ\t������Ϣ\n";
	outfile4 << "����\t����\t\t\t\t\t�绰����\t�����ʼ�\t��ϵ\t������Ϣ\n";

	Person* ptr = L->next;
	while (ptr)
	{
		if (ptr->relate == "����")
		{
			outfile1 << ptr->name << "\t" << ptr->birthday << "\t" << ptr->phone_num << "\t\t\t\t\t" << ptr->email << "\t\t\t\t\t" << ptr->relate << "\t\t\t\t\t" << ptr->more << "\n";
	    }
		if (ptr->relate == "ͬѧ")
		{
			outfile2 << ptr->name << "\t" << ptr->birthday << "\t" << ptr->phone_num << "\t\t\t\t\t" << ptr->email << "\t\t\t\t\t" << ptr->relate << "\t\t\t\t\t" << ptr->more << "\n";
		}
		if (ptr->relate == "ͬ��")
		{
			outfile3 << ptr->name << "\t" << ptr->birthday << "\t" << ptr->phone_num << "\t\t\t\t\t" << ptr->email << "\t\t\t\t\t" << ptr->relate << "\t\t\t\t\t" << ptr->more << "\n";
		}
		if (ptr->relate == "����")
		{
			outfile4 << ptr->name << "\t" << ptr->birthday << "\t" << ptr->phone_num << "\t\t\t\t\t" << ptr->email << "\t\t\t\t\t" << ptr->relate << "\t\t\t\t\t" << ptr->more << "\n";
		}
		outfile << ptr->name << "\t" << ptr->birthday << "\t" << ptr->phone_num << "\t\t\t\t\t" << ptr->email << "\t\t\t\t\t" << ptr->relate << "\t\t\t\t\t" << ptr->more << "\n";
		ptr = ptr->next;
	}

	outfile.close();
}
