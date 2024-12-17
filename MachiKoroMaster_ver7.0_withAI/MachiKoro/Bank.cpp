#include "Bank.h"

Bank::Bank()//bank类负责管理玩家的金币数
{
	this->coins = 60; //默认构造器：每位玩家的初始金币数为 3
}

int Bank::get_coins()
{
	return this->coins;
}

void Bank::deposit(int val)
{
	this->coins += val;
}

int Bank::withdraw(int val)//扣钱
{
	if (val > this->coins)
	{
		this->coins = 0;
		return this->coins;
	}

	this->coins -= val;
	return val;
}
