#pragma once

#include <string>
#include "ColorAndIcon.h"
#include "Bank.h"

using namespace std;
namespace machi {
	class Card {//Card类包含了每张卡牌的属性
	public:
		virtual void action(Bank *p1, Bank *p2, Card *c1, Card *c2, int val) = 0;
		void set_cost(int cost);
		void set_value(int value);
		void set_color(Color color);
		void set_name(string name);
		void set_renovation(bool renovation);
		void set_low_roll(int low);
		void set_high_roll(int high);
		void set_icon(Icon icon);
		void set_card(string name, int value, int cost, int low_roll, int high_roll, Icon icon, Color color);

		int get_value();
		int get_cost();
		Color get_color();
		Icon get_icon();
		bool get_renovation();
		string get_name();

		int get_high_roll();
		int get_low_roll();

		string get_string_color();

	private:
		int low_roll;//最低可以掷到的点数
		int high_roll;//最高可以掷到的点数
		int cost;//得到的金币数
		int value;//购买这张牌所需要的点数
		Color color;//卡牌颜色
		Icon icon;//卡牌类型
		bool renovation;
		string name;

	};
}