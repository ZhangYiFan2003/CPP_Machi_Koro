#include <iomanip>
#include <sstream>
#include "Game.h"
#include <regex>
#include <time.h>

using namespace std;

Game::Game()
{
    this->slot_count = 0;
    this->is_game_over = false;
    this->turn = 0;
    this->deal();

    this->create_player("RAY");//创建四位玩家
    this->create_player("NOLAN");
    this->create_player("KEVIN");
    this->create_player("ISABELLE");

    cout << "Combien de joueurs y-a-t-il? 1-9" << endl;
    cin >> playerno;
    while(playerno < 0 || playerno > 9){
        cout << "Impossible." << endl;
        cout << "Combien de joueurs y-a-t-il? 1 to 9" << endl;
        cin >> playerno;
    }
    getchar();
    if(playerno <= 4){
        for (std::size_t i = 0; i < playerno; ++i){
            cout << "Name of player no." << i + 1 << endl;
            cin >> players[i]->name;
            players[i]->bot = false;
        }
    }
    else{
        for(std::size_t i = 4; i < playerno; ++i){
            cout << "Name of player no." << i + 1 << endl;
            string str;
            cin >> str;
            this->create_player(str);
        }
    }
}

void Game::create_player(string name)//创建一位新的玩家
{
    player *p = new player(); // player的类型是struct L25的意思是通过调用 player 的默认构造函数 在堆区开辟一段类型为 player 的内存区域 将内存的首地址存放在 指针p 中
    p->bank = new Bank();//在创建玩家的同时 在堆区也为这位玩家背后的银行开辟内存
    p->name = name;//将玩家的名字存入对象的name变量中 因为 player 是 struct 类型 默认为public 所以可以通过指针直接访问

    YellowCard *c;
    c = new TrainStation(); p->yellow_cards.push_back(c);//将创建的黄色卡牌放到每位玩家自己的牌库中 但默认每张黄色地标都没有被激活（active=false）
    c = new ShoppingMall(); p->yellow_cards.push_back(c);
    c = new AmusementPark(); p->yellow_cards.push_back(c);
    c = new RadioTower(); p->yellow_cards.push_back(c);

    BlueCard *b;
    b = new WheatField(); p->blue_cards.push_back(b);//每位玩家开局默认得到一张麦田

    GreenCard *g;
    g = new Bakery(); p->green_cards.push_back(g);//开局默认得到一张蛋糕房

    players.push_back(p);//将这位玩家对应的内存地址存放在 “玩家列表” 中
}

void Game::deal()//对于 deal 整个方法而言，它的作用是检查牌库里是否有已经全部买完的牌，如果有，则不再显示该张卡牌
{
    Deck& d = Deck::getInstance();//使用单例设计模式，仅在用到时生成一个实例
    Card *c;
    bool exists;
    while (d.deck.size() > 0 && this->slot.size() < 15) {
        exists = false;
        c = d.deck.back(); //将 deck 向量中最后一个元素的引用赋给 c
        for (int i = 0; i < this->slot.size(); i++) {
            if (c->get_name().compare(this->slot[i][0]->get_name()) == 0) {
                slot[i].push_back(c);
                exists = true;
                break;
            }
        }
        if (!exists) {
            vector<Card *> v;
            v.push_back(c);
            this->slot.push_back(v);
            this->slot_count++;
        }
        d.deck.pop_back();
    }
}

vector<vector<Card *>> Game::get_slot()
{
    return this->slot;
}

void Game::rolling_dice(int dice_count)
{
    srand((unsigned int)time(0));
    this->dice1 = rand() % 6 + 1;//骰子1 生成1-6的随机数
    this->dice2 = 0;//投一次骰子，因此默认第二个骰子为0

    if (dice_count == 2)//一次投两个骰子
    {
        this->dice2 = rand() % 6 + 1;//骰子2 也生成1-6的随机数
    }
    this->dice = this->dice1 + this->dice2;//实际点数为两个骰子的点数之和
}

void print_card(Card *c)//用来展示卡牌的具体信息
{
    cout << left <<  "|" <<  //left:强制一个值在其字段的左侧打印，在右边填充空格
         // setw() 函数用于控制输出之间的间隔
         setw(12) << c->get_string_color() << "|" << //setw函数用来设置每次打印的可用宽度n 打印不足n个字符时---->输出靠左放 右边填空白 以凑足宽度
         setw(27) << c->get_name() << "|" <<
         setw(12) << c->get_cost() << "|" <<
         setw(17) << c->get_value() << "|" <<
         setw(13) << c->get_low_roll() << "|" <<
         setw(13) << c->get_high_roll() << "|" << endl;
}

void print_card_heading()//相当于打印表格信息的第一行
{
    cout << left << "|" <<
         //setw() 函数用于控制输出之间的间隔
         setw(12) << "Couleur" << "|" <<                     // 卡牌颜色
         setw(27) << "Batiments" << "|" <<                   // 各类建筑
         setw(12) << "Depense" << "|" <<                     // 建造需要的硬币开销
         setw(17) << "Points d'effet" << "|" <<       // 与玩家交互时的效果点数，例如 “拥有麦田能让玩家获得 ‘1’ 枚硬币” —— ‘1’
         setw(13) << "Points bas" << "|" <<                  // 触发卡牌效果的较低点数
         setw(13) << "Points haut" << "|" << endl;           // 触发卡牌效果的较高点数
}

void Game::view_slot_cards(bool cls)
{
    if (cls) {
        system("cls");
        cout<<"PRESS ANY KEY TO CONTINUE THE GAME:"<<endl;
        system("pause");
    }
    cout << "<<   Bienvenue dans le Machi-Koro !   >>" << endl << endl;
    cout << "Ce sont les cartes vous pouvez choisir:" << endl ;
    cout << left <<
         setw(7) << "No." <<
         setw(12) << "Quantity" ;
    print_card_heading();
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < this->slot.size(); i++)
    {
        cout << left <<
             setw(7) << i <<//i代表卡牌前的序号 我们使用序号来代指卡牌
             setw(12) << this->slot[i].size();
        print_card(this->slot[i][0]);//展示每一种卡牌的所有信息
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    }
    cout << endl;//输出完一张卡牌的信息就换行
}

void Game::view_player_cards(int index, bool cls)//输入的变量为：index-想要查看的玩家的序号 cls-是否需要清屏 需要则：cls=1 不需要：cls=0
{
    if (cls) {
        system("cls");
        cout << "Appuyez sur n'importe quelle touche pour continuer le jeu..." << endl;
        system("pause");
    }
    print_card_heading();
    for (int i = 0; i < this->players[index]->blue_cards.size(); i++) {
        print_card(this->players[index]->blue_cards[i]);
    }//输出当前玩家所拥有的蓝色卡牌的所有具体信息
    cout << endl;
    for (int i = 0; i < this->players[index]->green_cards.size(); i++) {
        print_card(this->players[index]->green_cards[i]);
    }//输出当前玩家所拥有的绿色卡牌的所有具体信息
    cout << endl;
    for (int i = 0; i < this->players[index]->red_cards.size(); i++) {
        print_card(this->players[index]->red_cards[i]);
    }//输出当前玩家所拥有的红色卡牌的所有具体信息
    cout << endl;
    for (int i = 0; i < this->players[index]->purple_cards.size(); i++) {
        print_card(this->players[index]->purple_cards[i]);
    }//输出当前玩家所拥有的紫色卡牌的所有具体信息
    cout << endl;
    for (int i = 0; i < this->players[index]->yellow_cards.size(); i++) {
        cout << i + 16 << "|";
        print_card(this->players[index]->yellow_cards[i]);
        cout << "---> active:" ;
        cout << left << setw(10) << this->players[index]->yellow_cards[i]->active << endl;
    }//输出当前玩家所拥有的黄色卡牌的所有具体信息
    cout << endl;
}

vector<string> split(string str)
{
    stringstream ss(str);//将str复制到ss中
    string item;
    vector<string> tokens;
    while (getline(ss, item, ' ')) {// 从istream中读取至多item个字符(包含结束标记符)保存在ss中。即使还没读够n个字符，如果遇到delim 或 字数达到限制，则读取终止，delim都不会被保存进s对应的数组中
        tokens.push_back(item);
    }
    return tokens;
}

int Game::player_input(string message) {
    string cmds = "(no)"
                  "|(view [0-9]+)"
                  "|(view table)"
                  "|(buy [0-9]*)";       // ????
    regex view(cmds);  //用来匹配cmds中固定的字符串
    bool complete = false;
    while (true) {
        string str;
        getline(cin, str);
        vector<string> input = split(str);
        if (!regex_match(str, view)) //如果str和view不匹配
        {
            cout << "Commande inconnue" << endl; //输出：未知命令
        } else if (input[0] == "no") return -1;//如果输入的是“no” 就返回-1
        else if (input[0] == "view") {
            if (input[1] == "table")
                view_slot_cards(true);//输入了指令“view table” 此时会给view_slot_cards函数输入true 会执行清屏操作 并重新展示表格

            else if (stoi(input[1]) > this->players.size())  //stoi():将字符串转化为10进制数 此处指：如果输入的想要查看牌库的玩家编号大于所有的玩家编号
            {
                cout << "Il n'y a pas de joueur " << stoi(input[1]) << endl;//输出：没有这位玩家
                continue;
            } else view_player_cards(stoi(input[1]) - 1, true);//存在该名玩家 输出这位玩家所有的卡牌
            cout << message << endl;
            continue;
        } else if (input[0] == "buy")//如果输入的第一个关键字为buy
        {
            //cout << this->slot.size() << endl;
            if (stoi(input[1]) >= 16 && stoi(input[1]) <= 19) {
                if (this->players[this->turn]->bank->get_coins() <
                    this->players[this->turn]->yellow_cards[stoi(input[1]) - 16]->get_cost()) {
                    cout << "Tu ne peux pas vous permettre. (Pas assez de monnaies)" << endl; //提示你没有足够的金币购买这张卡牌
                    continue;
                } else {
                    switch (stoi(input[1])) {
                        case 16:
                            cout << "TrainStation est activee! " << endl;
                            break;
                        case 17:
                            cout << "ShoppingMall est activee!" << endl;
                            break;
                        case 18:
                            cout << "AmusementPark est activee!" << endl;
                            break;
                        case 19:
                            cout << "RadioTower est activee!" << endl;
                            break;
                    }
                }
                cout << players[this->turn]->name << ", felicitation! " << endl;
                //cout << stoi(input[1]);
                return stoi(input[1]);
                //continue;
            }
            if (stoi(input[1])> this->slot.size())//如果输入的数字大于所有卡牌类型的数量
            {
                cout << "Pas de carte au numero:" << stoi(input[1]) << endl;//输出：没有数字编号为：xx的卡牌
                continue;
            }
            if (this->players[this->turn]->bank->get_coins() <
                this->slot[stoi(input[1])][0]->get_cost())//如果玩家拥有的金币数 < 购买这张卡牌所需要的金币数
            {
                cout << "Tu ne peux pas vous permettre. (Pas assez de monnaies)" << endl; //提示你没有足够的金币购买这张卡牌
                continue;
            }

            // if (input[1] == "")
            return stoi(input[1]);//返回想要购买的卡牌序号，并把它从字符串类型转换为十进制数
        }
    }
    return 'a';
}
void Game::roll_dice()//掷骰子用到的函数
{
    system("cls");//cls用来清屏
    this->deal();
    this->view_slot_cards(true);
    this->view_player_cards(this->turn, false);

    int dice_count = 1;

    // Should be Train Station Card
    if (this->players[this->turn]->yellow_cards[0]->active && this->players[this->turn]->bot == false)//如果黄色卡牌火车站已经被该名玩家激活
    {
        cout << "1 or 2 dice: ";//询问玩家要投掷一次还是两次骰子
        cin >> dice_count;//将输入值赋给dice_count
        getchar();
    }
    if (this->players[this->turn]->yellow_cards[0]->active && this->players[this->turn]->bot == true)//如果黄色卡牌火车站已经被该名玩家激活
    {
        cout << "1 or 2 dice: ";//询问玩家要投掷一次还是两次骰子
        dice_count = 2;
        cout << "2";
    }
    this->rolling_dice(dice_count);//交给rolling_dice函数 该函数将返回对应的投掷结果

    // Should be Radio Tower
    if (this->players[this->turn]->yellow_cards[3]->active)//如果电视塔被该名玩家激活
    {
        if (dice_count == 2){
            cout << endl << "le premier:" << this->dice1 << endl << "le second:" << this->dice2 << endl << "le totale: " << this->dice1 + this->dice2;
        }
        else{
            cout << "lance un(e) " << this->dice;
        }
        cout << ". Relancer(y/n): ";//返回第一次投掷骰子的结果 并询问当前玩家是否要选择重新再投一次骰子
        char response;
        if(this->players[this->turn]->bot == false){
            cin >> response; //将玩家输入的结果y/n赋值给变量response
            getchar();
        }
        else{
            response = 'y';
            cout << 'y';
        }
        if (response == 'y') this->rolling_dice(dice_count);//如果当前玩家选择“y” 则重新再投掷一次骰子
    }

    cout << endl;
    cout << "Joueur: " << players[this->turn]->name  << "(No." << (this->turn) +1 << ")";
    if (dice_count == 2){
        cout << "lance: " << endl << "le premier: " << this->dice1 << endl << "le second: " << this->dice2 << endl << "--> le totale: " << this->dice1 + this->dice2;
    }
    else{
        cout << "lance un(e) " << this->dice;
    }
    cout << "   |   Ses monnaies: " << this->players[this->turn]->bank->get_coins() << endl;//返回：玩家Name 投掷出了数字n 现在拥有金币总数：m
    this->red_card_check();//用来检查是否有红色卡牌 拿取该名玩家的金币
}

void Game::red_card_check()
{
    int tracker = (this->turn) - 1; //tracker用来记录当前正在检查手牌的玩家序号
    if (tracker < 0) tracker = this->players.size() - 1; //如果当前玩家序号为0 此时 tracker - 1 < 0 此时就将tracker移到最后一位玩家身上

    while (tracker != this->turn)//只要tracker没有等于当前回合的玩家序号，就对其手牌进行检查
    {
        for (int i = 0; i < this->players[tracker]->red_cards.size(); i++)//对当前检索的玩家手牌所有类型进行遍历
        {
            if (this->dice <= this->players[tracker]->red_cards[i]->get_high_roll() && //如果当前回合的点数 dice <= 待检索玩家红牌的最高位 并且 dice>=待检索玩家红牌的最低位 代表该名玩家拥有某张红牌
                this->dice >= this->players[tracker]->red_cards[i]->get_low_roll())
            {
                Card *c = NULL;
                // Should be Shopping Mall
                if (this->players[tracker]->yellow_cards[1]->active) c = this->players[tracker]->red_cards[i];//如果被检索玩家的购物中心也已经被激活 那么c就指向被检索玩家的当前这张红牌
                this->players[tracker]->red_cards[i]->action( //对被检索玩家和当前回合玩家的金币进行操作
                        this->players[tracker]->bank,
                        this->players[this->turn]->bank,
                        c,
                        NULL,
                        0
                );
            }
            //if (this->players[i]->bank->get_coins() == 0) break;
        }
        tracker--;
        if (tracker < 0) tracker = this->players.size() - 1;

    }
    this->blue_card_check(); //检查蓝色的卡牌
}
void Game::blue_card_check()
{
    for (int i = 0; i < this->players.size(); i++)//对每名玩家手中的蓝色卡牌进行遍历
    {
        for (int j = 0; j < this->players[i]->blue_cards.size(); j++)
        {
            if (this->dice <= this->players[i]->blue_cards[j]->get_high_roll() && //如果该名玩家拥有蓝色卡牌
                this->dice >= this->players[i]->blue_cards[j]->get_low_roll())
            {
                this->players[i]->blue_cards[j]->action( //将蓝色卡牌对应的金币奖励给该名玩家
                        this->players[i]->bank,
                        NULL,
                        NULL,
                        NULL,
                        0
                );
            }
        }
    }
    this->green_card_check();//检查绿色卡牌
}
void Game::green_card_check()
{
    for (int i = 0; i < this->players[this->turn]->green_cards.size(); i++)//对当前回合玩家本人的绿色卡牌进行遍历
    {
        if (this->dice <= this->players[this->turn]->green_cards[i]->get_high_roll() &&//如果找到绿色卡牌
            this->dice >= this->players[this->turn]->green_cards[i]->get_low_roll()) //
        {
            Card *c = NULL;
            // Should be Shopping Mall
            if (this->players[this->turn]->yellow_cards[1]->active) c = this->players[this->turn]->green_cards[i];//如果地标购物中心已经被激活
            int val = 0;
            Icon icon = this->players[this->turn]->green_cards[i]->get_icon();//将当前遍历所到位置的卡牌图标赋值给icon
            if (icon != Icon::none)//统计需要给当前玩家的奖励金币数 并且存放在val中 最后统一加给当前玩家
            {
                for (int j = 0; j < this->players[this->turn]->blue_cards.size(); j++)
                {
                    if (icon == this->players[this->turn]->blue_cards[j]->get_icon()) val++;
                }
            }
            this->players[this->turn]->green_cards[i]->action(
                    this->players[this->turn]->bank,
                    NULL,
                    c,
                    NULL,
                    val
            );
        }
    }
    this->purple_card_check();//检查当前玩家的紫色卡牌
}

void Game::purple_card_check()
{
    for (int i = 0; i < this->players[this->turn]->purple_cards.size(); i++)
    {
        if (this->players[this->turn]->purple_cards[i]->get_name().compare("Stadium") == 0) //如果当前回合的玩家所拥有的紫色卡牌是Stadium
        {
            for (int j = 0; j < this->players.size(); j++)
            {
                this->players[this->turn]->bank->deposit(this->players[j]->bank->withdraw(2));
            }
        }
        if (this->players[this->turn]->purple_cards[i]->get_name().compare("TV Station") == 0)//如果当前玩家拥有TV Station-选择一个人拿取5个金币
        {
            cout << "Prendre jusqu'a 5 pieces de:";
            for (int j = 0; j < this->players.size(); j++)
            {
                cout << j << ": " << this->players[j]->bank->get_coins() << " ";//输出每名玩家当前所拥有的金币数
            }
            int player_num;
            cin >> player_num;//读取用户的选择 并存放在player_num内
            this->players[this->turn]->bank->deposit(this->players[player_num]->bank->withdraw(5));
        }
        if (this->players[this->turn]->purple_cards[i]->get_name().compare("Business Center") == 0)//这里的business center就是网页版游戏中的office 用来和另外一名玩家交换一张手牌（不能是紫牌和黄牌）
        {
            cout << "Trade Cards with a player:" << endl;
            for (int j = 0; j < this->players.size(); j++)
            {
                cout << "Player: " << j << endl;//输出其他玩家所拥有的手牌
                cout << "Blue(1): ";
                for (int k = 0; i < this->players[j]->blue_cards.size(); k++)
                {
                    cout << " |" << k << ": " << this->players[j]->blue_cards[k]->get_name();
                }
                cout << endl;
                cout << "Green(2): ";
                for (int k = 0; i < this->players[j]->green_cards.size(); k++)
                {
                    cout << " |" << k << ": " << this->players[j]->green_cards[k]->get_name();
                }
                cout << endl;
                cout << "Red(3): ";
                for (int k = 0; i < this->players[j]->red_cards.size(); k++)
                {
                    cout << " |" << k << ": " << this->players[j]->red_cards[k]->get_name();
                }
                cout << endl;
            }
            int player_num;
            int color_num;
            int card_num;
            cout << "Selectionnez le joueur a prendre: ";//选择需要交换手牌的玩家序号
            cin >> player_num;
            cout << endl;

            cout << "Selectionnez la couleur a prendre: ";//选择需要交换的卡牌颜色
            cin >> color_num;
            cout << endl;

            cout << "Selectionnez la carte a prendre: ";//选择需要交换哪张牌
            cin >> card_num;
            cout << endl;

            if (color_num == 1)//输入1代表要交换蓝色卡牌
            {
                this->players[this->turn]->blue_cards.push_back(this->players[player_num]->blue_cards[card_num]);
                this->players[player_num]->blue_cards.erase(this->players[player_num]->blue_cards.begin() + card_num);
            }
            else if (color_num == 2)//输入2代表要交换绿色卡牌
            {
                this->players[this->turn]->green_cards.push_back(this->players[player_num]->green_cards[card_num]);
                this->players[player_num]->green_cards.erase(this->players[player_num]->green_cards.begin() + card_num);
            }
            else//输入3代表要交换红色卡牌
            {
                this->players[this->turn]->red_cards.push_back(this->players[player_num]->red_cards[card_num]);
                this->players[player_num]->red_cards.erase(this->players[player_num]->red_cards.begin() + card_num);
            }

            cout << "Selectionnez la couleur a prendre: ";//选择你要换出去的卡牌颜色
            cin >> color_num;
            cout << endl;

            cout << "Selectionnez la carte a prendre: ";//选择你要换出去的卡牌
            cin >> card_num;
            cout << endl;

            if (color_num == 1)
            {
                this->players[player_num]->blue_cards.push_back(this->players[this->turn]->blue_cards[card_num]);
                this->players[this->turn]->blue_cards.erase(this->players[this->turn]->blue_cards.begin() + card_num);
            }
            else if (color_num == 2)
            {
                this->players[player_num]->green_cards.push_back(this->players[this->turn]->green_cards[card_num]);
                this->players[this->turn]->green_cards.erase(this->players[this->turn]->green_cards.begin() + card_num);
            }
            else
            {
                this->players[player_num]->red_cards.push_back(this->players[this->turn]->red_cards[card_num]);
                this->players[this->turn]->red_cards.erase(this->players[this->turn]->red_cards.begin() + card_num);
            }
        }
    }
    this->buy_propery();//给当前玩家购买一张卡牌的机会
}


void Game::buy_propery() {
    cout << "Le nombre de monnaies qu'il lui reste: " << this->players[this->turn]->bank->get_coins()
         << endl;//输出当前玩家的金币数
    cout << "Quel batiment aimeriez-vous construire ?" << endl; //输出你想购买哪一张卡牌
    int selection;
    int tmp;
    bool complete = false;
    while (!complete) //当前玩家还没有购买卡牌的时候
    {
        if(this->players[this->turn]->bot == false){
            selection = this->player_input("Quel batiment aimeriez-vous construire ?");
        }
        else{
            selection = bot();
        }
        cout << endl;
        if (selection < slot.size()) {
            int select = selection;
            if (Color::blue == this->slot[select][0]->get_color())//如果当前玩家选择想要购买的卡牌颜色是蓝色
            {
                this->players[this->turn]->blue_cards.push_back((BlueCard *) this->slot[select].back());//将选中的牌加入当前玩家的牌库
                this->players[this->turn]->bank->withdraw(this->slot[select][0]->get_cost());
                this->slot[select].pop_back();//将牌库中的所选中的牌删除
                complete = true;//玩家完成购买
            } else if (Color::green == this->slot[select][0]->get_color())//如果当前玩家选择想要购买的卡牌颜色是绿色
            {
                this->players[this->turn]->green_cards.push_back(
                        (GreenCard *) this->slot[select].back());//将选中的牌加入当前玩家的牌库
                this->players[this->turn]->bank->withdraw(this->slot[select][0]->get_cost());
                this->slot[select].pop_back();//将牌库中的所选中的牌删除
                complete = true;//玩家完成购买
            } else if (Color::red == this->slot[select][0]->get_color()) {
                this->players[this->turn]->red_cards.push_back((RedCard *) this->slot[select].back());//将选中的牌加入当前玩家的牌库
                this->slot[select].pop_back();//将牌库中的所选中的牌删除
                this->players[this->turn]->bank->withdraw(this->slot[select][0]->get_cost());
                complete = true;//玩家完成购买
            } else if (Color::purple == this->slot[select][0]->get_color())//如果当前玩家选择想要购买的卡牌颜色是紫色
            {
                bool purp = true;
                for (int i = 0; i < this->players[this->turn]->purple_cards.size(); i++) {
                    if (this->slot[select].back()->get_name().compare(
                            this->players[this->turn]->purple_cards[i]->get_name()) == 0) //玩家已经拥有当前种类的紫色卡牌
                    {
                        cout << "Vous avez deja cet etablissement" << endl;
                        purp = false;
                        break;
                    }
                }
                if (purp)//如果玩家还没拥有当前的紫色卡牌
                {
                    this->players[this->turn]->purple_cards.push_back(
                            (PurpleCard *) this->slot[select].back());//将选中的牌加入当前玩家的牌库
                    this->players[this->turn]->bank->withdraw(this->slot[select][0]->get_cost());
                    this->slot[select].pop_back();//将牌库中的所选中的牌删除
                    complete = true;
                }
            }
            if (this->slot[select].size() == 0) //如果牌库中已经没有这张牌
            {
                this->slot.erase(this->slot.begin() + select); //将这张牌的名字从剩余的牌库中删除
            }

        } else {
            if (selection >= 16 && selection <= 19)//如果当前玩家选择想要购买的卡牌颜色是黄色
            {
                bool yellow = true;
                if (this->players[this->turn]->yellow_cards[selection - 16]->active == true) //玩家已经拥有当前种类的黄色卡牌
                {
                    cout << "Vous avez deja cet etablissement" << endl;
                    yellow = false;
                    break;
                }
                if (yellow) {
                    this->players[this->turn]->yellow_cards[selection - 16]->active = true;
                    this->players[this->turn]->bank->withdraw(
                            this->players[this->turn]->yellow_cards[selection - 16]->get_cost());
                    //cout << this->players[this->turn]->yellow_cards[selection - 16]->get_cost();
                    complete = true;
                }
            }
            else{break;}
        }
    }
    this->end_of_turn();//结束当前玩家的回合
}
void Game::end_of_turn()
{
    this->is_game_over = true;
    for (int i = 0; i < this->players[turn]->yellow_cards.size(); i++)
    {
        if (!this->players[turn]->yellow_cards[i]->active)//如果上一回合玩家的黄色卡牌还没有被全部激活
        {
            this->is_game_over = false;//对局就还没有结束
            break;
        }
    }
    if (this->is_game_over) { cout << this->players[turn]->name << " remporte la victoire! Le jeu termine. " << endl; exit(0); } //如果对局结束 输出当前胜利的玩家 结束对局
    cout << "Fin du tour de "<< this->players[turn]->name << ". Les monnaies restant: " << this->players[turn]->bank->get_coins();
    // Should be Amusement Park card
    if (this->players[this->turn]->yellow_cards[2]->active && this->players[this->turn]->anotherTurn == false)//如果上一名玩家的 amusement park 被激活
    {
        //turn--;//重新回到上一名玩家的回合
        this->players[this->turn]->anotherTurn = true;
        cout << "   --->   " << "Apres, c'est le tour de " << players[this->turn]->name  << "." << endl;//输出：当前是 第n位玩家的回合
        return;
    }
    else if(this->players[this->turn]->yellow_cards[2]->active && this->players[this->turn]->anotherTurn == true){
        this->players[this->turn]->anotherTurn = false;
        this->turn++;//轮到下一位玩家
        if (this->turn == players.size()) this->turn = 0; //如果回合数已经=玩家的数量 重新轮到第一位玩家
        cout << "   --->   " << "Apres, c'est le tour de " << players[this->turn]->name  << "." << endl;//输出：当前是 第n位玩家的回合
        return;
    }
    this->turn++;//轮到下一位玩家
    if (this->turn == players.size()) this->turn = 0; //如果回合数已经=玩家的数量 重新轮到第一位玩家
    cout << "   --->   " << "Apres, c'est le tour de " << players[this->turn]->name  << "." << endl;//输出：当前是 第n位玩家的回合
    return;
}
int Game::bot() {
    for(int i = 3; i >= 0; --i){
        if(this->players[this->turn]->bank->get_coins() > this->players[this->turn]->yellow_cards[i]->get_cost() && this->players[this->turn]->yellow_cards[i]->active == false){
            cout << "buy " << i + 16;
            return i + 16;
        }
    }
    for(std::size_t i = 0; i < this->slot.size(); ++i){
        if(this->players[this->turn]->bank->get_coins() > this->slot[i][0]->get_cost() && this->slot[i][0]->get_color() != Color::purple){
            botslot.push_back(i);
        }
    }
    srand((unsigned int)time(0));
    int i = botslot[rand()%(botslot.size())];
    cout << "buy " << i;
    return i;
}