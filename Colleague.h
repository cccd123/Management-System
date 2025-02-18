#ifndef __COLLEAGUE_H__
#define __COLLEAGUE_H__

#include"person.h"

class Colleague :public Person
{
private:
	string firm;

public:
	Colleague(string name = " ", Date birthday = (0, 0, 0), string phone_num = " ", string email = " ", string relate = " ", string more = " ");
};

#endif
