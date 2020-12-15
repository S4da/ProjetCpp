#include <iostream>
#include <cstdlib>
#include "unite.h"
#include "fantassin.h"
#include "player.h"

Fantassin::Fantassin(int id): Unite(10,10,1,1,4,id)
{}

void Fantassin::action1(int pos, std::vector<Unite*> &champ){
    if (this->getId()!=champ.at(pos+1)->getId()){
        this->attaque(champ.at(pos+1));
        act1Fait=true;
    } 
}

void Fantassin::action2(int pos, std::vector<Unite*> &champ){
    
}

void Fantassin::action3(int pos, std::vector<Unite*> &champ){
    
}

Fantassin::~Fantassin(){}
