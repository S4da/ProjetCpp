#include <iostream>
#include <cstdlib>
#include "super_soldat.h"

SuperSoldat::SuperSoldat(int pv,Player* player): Fantassin(player)
{
    this->setHp(pv);
}


void SuperSoldat::action3(int pos, std::vector<Unite*> &champ, Player* ennemi){
    int dist=2;
    int pas=1;
    int taille_champ=champ.size();
    if (champ.at(pos)->getPlayer()->getId()>ennemi->getId()){
        dist=11;
        pas=-1;
    } 
    if (pos==taille_champ-dist) {
        if (champ.at(pos+pas)!=nullptr){
            this->attaque(champ.at(pos+pas));
            afficherActionAtk(pos);
        }
        else {
            afficherActionAtk(pos);
            ennemi->damage(this->getAtk());
        }
    }
    else if (champ.at(pos+pas)!=nullptr) {
        if (this->getPlayer()!=champ.at(pos+pas)->getPlayer()){
            this->attaque(champ.at(pos+pas));
            afficherActionAtk(pos);
        }
    }
}

SuperSoldat::~SuperSoldat() {}

