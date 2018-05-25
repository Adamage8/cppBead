#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

#include "Player.h"

class Player;

class Field{
public:
    Field* nextField;
    std::string type;
    virtual void action(Player* p){};
};

class AccomodationField : public Field{
public:
    Player* owner = NULL;
    bool hasHouse;
    AccomodationField(){
        type = "accomodation";
    }
};

class ServiceField : public Field{
public:
    int price;
    ServiceField(int p):price(p){
        type = "service";
    }
};

class LuckyField : public Field {
public:
    int reward;
    LuckyField(int r):reward(r){
        type = "lucky";
    }
};

#endif // FIELD_H_INCLUDED
