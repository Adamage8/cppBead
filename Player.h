#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <string>
#include "Field.h"

using namespace std;

class Field;

class Player{
public:
    string name;
    Field* position;
    int money = 10000;
    bool inGame = true;
    Player(string n):name(n){}
    void step(int value);
    virtual void move(int value) = 0;
    void moneyGain(int quantity){
        money += quantity;
    }
    void moneyLose(int quantity){
        money -= quantity;
        if(money <= 0){
            inGame = false;
        }
    }
};

class GreedyPlayer : public Player{
public:
    GreedyPlayer(string s) : Player(s){};
    virtual void move(int value);
};

class CarefulPlayer : public Player{
public:
    CarefulPlayer(string s) : Player(s){};
    virtual void move(int value);
};

class TacticalPlayer : public Player{
public:
    TacticalPlayer(string s) : Player(s){};
    bool skippedLastTime = false;
    virtual void move(int value);
};

#endif // PLAYER_H_INCLUDED
