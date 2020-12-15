#include <iostream>
#include <cstdlib>
#include "unite.h"
#include "archer.h"
#include "player.h"

Archer::Archer(int id): Unite(12,8,1,3,3,id)
{}

void Archer::action1(int pos, std::vector<Unite*> &champ){
    if (this->getId()!=champ.at(pos+1)->getId()){
        this->attaque(champ.at(pos+1));
    } 
}

void Archer::action2(int pos, std::vector<Unite*> &champ){
    
}

void Archer::action3(int pos, std::vector<Unite*> &champ){
    
}
Archer::~Archer(){}
