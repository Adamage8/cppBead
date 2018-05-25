#include "Field.h"
#include "Player.h"

using namespace std;

virtual void AccomodationField::action(Player* p) override {
    if(owner == NULL){
        owner = p;
        owner->moneyLose(1000);
    }else if(owner = p){
        if(!hasHouse) {
            hasHouse = true;
            owner->moneyLose(4000);
        }
    }else{
        p->moneyLose(hasHouse ? 2000 : 500);
    }
}

virtual void ServiceField::action(Player* p) override {
    p->moneyLose(price);
}

virtual void LuckyField::action(Player* p) override {
    p->moneyGain(reward);
}
