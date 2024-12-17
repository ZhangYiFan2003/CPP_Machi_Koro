#pragma once

#include "Card.h"

using namespace machi;

class YellowCard : public Card { //通过继承 黄色卡牌拥有卡牌的所有属性
public:
	virtual void action(Bank *p1, Bank *p2, Card *c1, Card *c2, int val);
	bool active;
private:
};

class AmusementPark : public YellowCard {
public:
	AmusementPark();
private:
};

class RadioTower : public YellowCard {
public:
	RadioTower();
private:
};

class ShoppingMall : public YellowCard {
public:
	ShoppingMall();
private:
};

class TrainStation : public YellowCard {
public:
	TrainStation();
private:
};