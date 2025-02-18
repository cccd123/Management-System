#ifndef __CLASSMATE_H__
#define __CLASSMATE_H__

#include"person.h"

class Classmate :public Person
{
private:
	string school;

public:
	Classmate(string name = " ", Date birthday=(0,0,0), string phone_num = " ", string email = " ", string relate = " ", string more = " ");
};

#endif