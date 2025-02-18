#ifndef __RELATIVE_H__
#define __RELATIVE_H__

#include"person.h"

class Relative :public Person
{
private:
	string type;//什么类型的亲戚

public:
	Relative(string name = " ", Date birthday = (0, 0, 0), string phone_num = " ", string email = " ", string relate = " ", string more = " ");
};

#endif
