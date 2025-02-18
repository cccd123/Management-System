#include "Management.h"

HWND Management::m_handle;

IMAGE m_bk;

Management::Management()
{
	//新建一个带头结点的联系人链表
	L = new Person;
	L->next = NULL;

	//读取文本信息进联系人链表中
	readfile("Contacts.txt");

	//加载背景
	m_handle = initgraph(960, 640, EX_SHOWCONSOLE);
	Person::m_handle = m_handle;
	loadimage(&m_bk, "bk.jpeg", getwidth(), getheight());

	//主界面按钮初始化
	menu_btns.push_back(new Button("添加联系人"));
	menu_btns.push_back(new Button("显示联系人"));
	menu_btns.push_back(new Button("排序联系人"));
	menu_btns.push_back(new Button("查找联系人"));
	menu_btns.push_back(new Button("修改联系人"));
	menu_btns.push_back(new Button("删除联系人"));
	menu_btns.push_back(new Button("清空通讯录"));
	menu_btns.push_back(new Button("查找寿星"));
	menu_btns.push_back(new Button("退出系统"));
	for (int i = 0;i < menu_btns.size();i++)
	{
		menu_btns[i]->setSize(260, 50);
		int bx = (getwidth() - menu_btns[i]->get_width()) / 2;
		int vspace = (getheight() - menu_btns[i]->get_height() * menu_btns.size()) / 2;
		int by = vspace + i * menu_btns[i]->get_height();
		menu_btns[i]->move(bx, by);//居中打印文字
	}
}

Management::~Management()
{
	//将文本信息保存进联系人列表中
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
		outtextxy(0, 600, "进入功能页后，按ESC可以回到主菜单页面");

		if (Button::hasMsg())
		{
			m_msg = Button::getMsg();//获得鼠标键盘消息
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{//鼠标左键按下esc键，返回主菜单
				op = Menu;
			}
		}
		switch (op)
		{
		case Menu:
			op = menu();
			break;
		case Add:
		{   //绘制按钮
			Button* choice1, * choice2, * choice3, * choice4;
			choice1 = new Button("选择朋友类型", 0, 0, 150, 30);
			choice1->drawButton();
			choice2 = new Button("选择同学类型", 0, 40, 150, 30);
			choice2->drawButton();
			choice3 = new Button("选择同事类型", 0, 80, 150, 30);
			choice3->drawButton();
			choice4 = new Button("选择亲戚类型", 0, 120, 150, 30);
			choice4->drawButton();

			static Person* ptr = 0; 
			if (choice1->isPushed())
			{
				delete ptr; //新建之前要先delete，释放原来的空间，防泄露
				ptr = new Friend;
				ptr->relate = "朋友";
			}
			if (choice2->isPushed())
			{
				delete ptr;
				ptr = new Classmate;
				ptr->relate = "同学";
			}
			if (choice3->isPushed())
			{
				delete ptr;
				ptr = new Colleague;
				ptr->relate = "同事";
			}
			if (choice4->isPushed())
			{
				delete ptr;
				ptr = new Relative;
				ptr->relate = "亲戚";
			}
			//要先选择类型,创建好相应的空间,才能输入信息添加联系人
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
		cout << "文件打开失败!\n";
		exit(0);
	}

	infile.seekg(0, ios::beg);
	char s[100];
	infile.getline(s, 100);//略去标题行
	
	while (infile >> p.name >> p.birthday >> p.phone_num >> p.email >> p.relate >> p.more)
	{
		if (p.relate == "朋友")
			ptr = new Friend(p.name, p.birthday, p.phone_num, p.email, p.relate, p.more);
		if (p.relate == "同学")
			ptr = new Classmate(p.name, p.birthday, p.phone_num, p.email, p.relate, p.more);
		if (p.relate == "同事")
			ptr = new Colleague(p.name, p.birthday, p.phone_num, p.email, p.relate, p.more);
		if (p.relate == "亲戚")
			ptr = new Relative(p.name, p.birthday, p.phone_num, p.email, p.relate, p.more);

		//头插法再反转
		ptr->next = L->next;
		L->next = ptr;
	}
	
	//反转
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
		cout << "文件打开失败!\n";
		exit(0);
	}

	outfile << "姓名\t生日\t\t\t\t\t电话号码\t电子邮件\t关系\t更多信息\n";//写入标题
	outfile1 << "姓名\t生日\t\t\t\t\t电话号码\t电子邮件\t关系\t更多信息\n";
	outfile2 << "姓名\t生日\t\t\t\t\t电话号码\t电子邮件\t关系\t更多信息\n";
	outfile3 << "姓名\t生日\t\t\t\t\t电话号码\t电子邮件\t关系\t更多信息\n";
	outfile4 << "姓名\t生日\t\t\t\t\t电话号码\t电子邮件\t关系\t更多信息\n";

	Person* ptr = L->next;
	while (ptr)
	{
		if (ptr->relate == "朋友")
		{
			outfile1 << ptr->name << "\t" << ptr->birthday << "\t" << ptr->phone_num << "\t\t\t\t\t" << ptr->email << "\t\t\t\t\t" << ptr->relate << "\t\t\t\t\t" << ptr->more << "\n";
	    }
		if (ptr->relate == "同学")
		{
			outfile2 << ptr->name << "\t" << ptr->birthday << "\t" << ptr->phone_num << "\t\t\t\t\t" << ptr->email << "\t\t\t\t\t" << ptr->relate << "\t\t\t\t\t" << ptr->more << "\n";
		}
		if (ptr->relate == "同事")
		{
			outfile3 << ptr->name << "\t" << ptr->birthday << "\t" << ptr->phone_num << "\t\t\t\t\t" << ptr->email << "\t\t\t\t\t" << ptr->relate << "\t\t\t\t\t" << ptr->more << "\n";
		}
		if (ptr->relate == "亲戚")
		{
			outfile4 << ptr->name << "\t" << ptr->birthday << "\t" << ptr->phone_num << "\t\t\t\t\t" << ptr->email << "\t\t\t\t\t" << ptr->relate << "\t\t\t\t\t" << ptr->more << "\n";
		}
		outfile << ptr->name << "\t" << ptr->birthday << "\t" << ptr->phone_num << "\t\t\t\t\t" << ptr->email << "\t\t\t\t\t" << ptr->relate << "\t\t\t\t\t" << ptr->more << "\n";
		ptr = ptr->next;
	}

	outfile.close();
}
