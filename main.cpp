#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>

#include "Player.h"
#include "Field.h"

using namespace std;

//Feladat:       Adott nevű szöveges állományból a lényeket tartalmazó tömb és
//               a versenypályát tartralmazó tömb feltöltése
//Bemenõ adatok: string str	- szöveges állomány neve
//Kimenõ adatok: vector<Creature*> &creature  - lények pointereinek tömbje
//               vector<int> &court - versenypálya mezőinek tömbje
//Tevékenység:   szöveges állomány alapján létrehozza a lényeket és a címeiket
//               a lényeket tartalmazó tömbe teszi, továbbá
//               a versenypályát tartralmazó tömböt is feltölti
Field* create(const string &str, vector<Player*> &players)
{
    ifstream f(str.c_str());
    if(f.fail()) {
        cout << "Nincs meg a fájl\n";
        exit(1);
    }
   //  létrehozása
    int n;
    f >> n;
    Field* lastField = NULL;
    Field* startingField;
    for(int i=0; i<n; ++i){
        char type;
        int value;
        f >> type >> value;
        Field* createdField;
        switch(type){
            case 'A' : createdField = new AccomodationField(); break;
            case 'S' : createdField = new ServiceField(value);    break;
            case 'L' : createdField = new LuckyField(value);  break;
        }
        if(lastField != NULL){
            lastField->nextField = createdField;
        }else {
            startingField = createdField;
        }
        lastField = createdField;
    }
    lastField->nextField = startingField;


   // Pálya betöltése
    int m;
    f >> m;
    players.resize(m);
    for(int j=0; j<m; ++j) {
        string name;
        char type;
        f >> name >> type;
        switch(type){
            case 'G' : players[j] = new GreedyPlayer(name);  break;
            case 'C' : players[j] = new CarefulPlayer(name); break;
            case 'T' : players[j] = new TacticalPlayer(name); break;
        }
    }
    return startingField;
}


void play(Field* start, vector<Player*> &players){
    ifstream f("dice.txt");
    if(f.fail()){
        cout << "Nincs meg a fájl\n";
        exit(1);
    }
    for(int i = 0; i < players.size(); ++i){
        players[i]->position = start;
    }

    int diceThrowCount;
    f >> diceThrowCount;
    for(unsigned int i = 0; i < diceThrowCount; ++i){
        for(unsigned int j = 0; j < players.size(); ++j){
            int number;
            f >> number;
            players[j]->move(number);
            if(players[j]->name == "greedy") cout << players[j]->position->type << endl;
        }
    }
}

//Feladat:       Verseny lebonyolítása
//Bemenõ adatok: vector<Creature*> &creature  - lények pointereinek tömbje
//               vector<int> &court - versenypálya mezőinek tömbje
//Kimenõ adatok: vector<Creature*> &creature  - lények pointereinek tömbje
//               vector<int> &court - versenypálya mezőinek tömbje
//               vector<string> alive - versenyt túlélő lények neveinek tömbje
//Tevékenység:   minden lényt sorban egymás után végig vezet a pályán (közben a pálya változhat),
//               illetve addig, amíg a lény el nem pusztul.
//               kigyűjti a pályát túlélő lények neveit.


int main()
{
    vector<Player*> v;
    Field* f = create("input.txt", v);
    play(f, v);

    return 0;
}
