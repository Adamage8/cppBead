#include "Field.h"
#include "Player.h"

using namespace std;

void Player::step(int value){
    for(int i = 0; i < value; ++i){
        position = position->nextField;
    }
}

virtual void GreedyPlayer::move(int value) override {
    cout << "greedymove" << endl;
    step(value);
    position->action(this);
}

virtual void CarefulPlayer::move(int value) override {
    cout << "carefulmove" << endl;
    step(value);
    ServiceField* v = dynamic_cast<ServiceField*>(position);
    if( v && v->price > money /2) {
        v->action(this);
    }
}

virtual void TacticalPlayer::move(int value) override {
    cout << "tacticalmove" << endl;
    step(value);
    if(skippedLastTime){
        position->action(this);
    }else{
        skippedLastTime = true;
    }
}
