# <center> MachiKoro游戏说明书
- 程序开始运行，先在控制台输入人类玩家数量。如果不足4位则会由机器人bot补位，如果超过4位则全部为人类玩家。主要由以下代码实现：
```c++
    cin >> playerno;
    while(playerno < 0 || playerno > 9){
    ...
    }
    getchar();
    if(playerno <= 4){
        for (std::size_t i = 0; i < playerno; ++i){
        ...
        }
    }
    else{
        for(std::size_t i = 4; i < playerno; ++i){
        ...
        }
    }
```
- 第1位玩家回合开始，系统展示所有剩下的牌，展示当前玩家目前有的牌，并自动掷骰子，根据点数得出玩家当回合的钱的总数。主要由以下函数实现：
```c++
void Game::deal(){}
void Game::rolling_dice(int dice_count){}
void print_card(Card *c){}
void Game::view_slot_cards(bool cls){}
void Game::view_player_cards(int index, bool cls){}
void Game::roll_dice(){}
void Game::roll_dice(){}
void Game::red_card_check(){}
void Game::blue_card_check(){}
void Game::green_card_check(){}
void Game::purple_card_check(){}
```
其中掷骰子前如果如果触发了对应的黄色卡，也需要玩家进行输入
- 然后玩家可以输入想进行的操作。可以进行的操作有：
    1. no(跳过回合)
    2. view加数字来查看对应玩家所拥有的卡牌
    3. view table 来再次查看当前回合剩余的可购买卡牌
    4. buy加数字来购买数字对应的卡牌
主要由以下函数实现：
```c++
int Game::player_input(string message){}
void Game::buy_propery(){}
```
- 最后，玩家回合结束后，系统检查是否有玩家已经赢下整局游戏，或者是否有玩家由于拥有的黄色卡可以再进行一回合。主要由以下函数实现：
```c++
void Game::end_of_turn(){}
```
- 机器人玩家的操作将全部由程序完成，包括选择掷骰子的数量，是否重新掷骰子，以及买哪张卡。所有这些操作都会在控制台显示。机器人玩家选卡主要由以下函数实现：
```c++
int Game::bot() {}
```
P.S. 注意事项，在游戏过程中，为了保证控制台显示的完整性，玩家需要在系统提示“按任意键继续时”按一下回车，希望理解。
## 祝你在MachiKoro城玩得开心