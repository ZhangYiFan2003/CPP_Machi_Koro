#pragma once
#include <vector>
#include <iostream>
#include "Card.h"
#include "BlueCard.h"
#include "GreenCard.h"
#include "RedCard.h"
#include "PurpleCard.h"
#include "YellowCard.h"

using namespace std;

class Deck {
public:
	vector<Card*> deck;
    static Deck& getInstance()
    {
        static Deck instance;
        return instance;
    }

private:
    Deck(){
        Card *c;
        for (int i = 0; i < 6; i++) { c = new WheatField(); this->deck.push_back(c); }//创建整局游戏所需要的所有卡牌
        for (int i = 0; i < 6; i++) { c = new Ranch(); this->deck.push_back(c); }
        for (int i = 0; i < 6; i++) { c = new Forest(); this->deck.push_back(c); }
        for (int i = 0; i < 6; i++) { c = new Mine(); this->deck.push_back(c); }
        for (int i = 0; i < 6; i++) { c = new AppleOrchard(); this->deck.push_back(c); }

        for (int i = 0; i < 6; i++) { c = new Bakery(); this->deck.push_back(c); }
        for (int i = 0; i < 6; i++) { c = new ConvenienceStore(); this->deck.push_back(c); }
        for (int i = 0; i < 6; i++) { c = new CheeseFactory(); this->deck.push_back(c); }
        for (int i = 0; i < 6; i++) { c = new FurnitureFactory(); this->deck.push_back(c); }
        for (int i = 0; i < 6; i++) { c = new FruitAndVegetableMarket(); this->deck.push_back(c); }

        for (int i = 0; i < 6; i++) { c = new Cafe(); this->deck.push_back(c); }
        for (int i = 0; i < 6; i++) { c = new FamilyRestaurant(); this->deck.push_back(c); }

        for (int i = 0; i < 4; i++) { c = new BusinessCenter(); this->deck.push_back(c); }
        for (int i = 0; i < 4; i++) { c = new TVStation(); this->deck.push_back(c); }
        for (int i = 0; i < 4; i++) { c = new Stadium();}
    }

        ~Deck(){};
        Deck(const Deck& another) = delete;
        Deck& operator=(const Deck& another) = delete;
};