#include <iostream>
#include <cstdlib>
#include "catapulte.h"

Catapulte::Catapulte(int id): Unite(20,8,2,4,6,id)
{}

void Catapulte::action1(int pos, std::vector<Unite*> &champ){
    if (this->getId()!=champ.at(pos+1)->getId()){
        this->attaque(champ.at(pos+1));
        act1Fait=true;
    } 
}

void Catapulte::action3(int pos, std::vector<Unite*> &champ){
    
}

Catapulte::~Catapulte(){}
