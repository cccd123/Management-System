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
	string relate;//��ϵ������
	string more;//������Ϣ��������more��ͳ�����ѵ���ʶ�ص㡢ͬѧ��ѧУ��ͬ�µĵ�λ�Լ����ݵĳƺ���ʹ���ܴ���������д��ͬʱ��Ӱ��Ը�������more��Ϣ������
	static int total;//ͳ����ϵ������

	friend class Management;
	static HWND m_handle;//���ھ������messagebox��Ҫ�õ��������management����ȡֵ����
	friend class Table;

public:
	Person* next;

	Person(string name=" ", Date birthday = (0, 0, 0), string phone_num=" ", string email=" ", string relate=" ", string more=" ");

	friend void add(Person*& L, Person*& ptr); //�����ϵ��
	friend void display(Person* L);            //��ʾ��ϵ��
	friend void search(Person* L);             //������ϵ��
	friend void del(Person*& L);               //ɾ����ϵ��
	friend void revise(Person*& L);            //�޸���ϵ��
	friend void clear(Person*& L);             //�����ϵ��
	friend void sort(Person* L);               //��������������������
	friend void Birthday_search(Person* L);    //��������
};

#endif
