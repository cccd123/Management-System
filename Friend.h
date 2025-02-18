#ifndef __FRIEND_H__
#define __FRIEND_H__

#include"person.h"

class Friend :public Person
{
private:
	string position;

public:
	Friend(string name = " ", Date birthday = (0, 0, 0), string phone_num = " ", string email = " ", string relate = " ", string more = " ");
};

#endif
