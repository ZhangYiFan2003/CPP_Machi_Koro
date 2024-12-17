#pragma once
#include <vector>

#include "Card.h"
#include "Bank.h"
#include "Deck.h"

using namespace std;

struct player { //每位玩家所包含的属性 存放在结构体中
	string name; //姓名
	Bank *bank;//每位玩家背后都有一个负责管理金币数量的Bank结构体 但实际存放的是Bank类型的指针bank
	vector<BlueCard*> blue_cards; //所拥有的蓝色卡牌
	vector<GreenCard*> green_cards; //所拥有的绿色卡牌
	vector<RedCard*> red_cards;  //所拥有的红色卡牌
	vector<PurpleCard*> purple_cards; //所拥有的紫色卡牌
	vector<YellowCard*> yellow_cards; //所拥有的黄色卡牌
	bool anotherTurn = false;//是否因为AmusementPark进行过第2回合
	bool bot = true;//标记该名玩家是否为机器人
};

class Game {
public:
	Game();//game默认构造函数
	int turn;
	bool is_game_over;//用来判断游戏是否结束
	void deal();
	vector<vector<Card *>> get_slot();
	vector<player*> players;//用来存放当前所有player类型玩家的首地址：相当于players是整局游戏的玩家列表
	void create_player(string name);
	void roll_dice();
	void red_card_check();
	void blue_card_check();
	void green_card_check();
	void purple_card_check();
	void buy_propery();
	int bot();
	void end_of_turn();
	void view_slot_cards(bool cls);
	void view_player_cards(int index, bool cls);
    int playerno;//记录用户输入的人类玩家数
    vector<int> botslot;//机器人的操作
private:
	int dice;//实际投到的点数dice = 第一个骰子的点数dice1 + 第二个骰子的点数dice2
	int dice1;//第一个骰子的点数
	int dice2;//第二个骰子的点数
	void rolling_dice(int dice_count);
	int player_input(string message);
	vector<vector<Card *>> slot;
	int slot_count;
};