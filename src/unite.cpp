#include <iostream>
#include <cstdlib>
#include "unite.h"

Unite::Unite(int prix, int pv, int rangeMin,int rangeMax,int atk,Player* player){
    this->prix=prix;
    this->pv=pv;
    this->rangeMin=rangeMin;
    this->rangeMax=rangeMax;
    this->atk=atk;
    this->player=player;
}

void Unite::attaque(Unite* ennemi){
    if (ennemi!=nullptr) ennemi->damage(this->atk);
}

void Unite::action2(int pos, std::vector<Unite*> &champ, Player* ennemi){
    int pas=1;
    int dist=2;
    int taille_champ=champ.size();
    if (champ.at(pos)->getPlayer()->getId()>ennemi->getId()){
        pas=-1;
        dist=11;
    } 

    if (pos!=taille_champ-dist && champ.at(pos+pas)==nullptr) {
        champ.at(pos+pas)=this;
        champ.at(pos)=nullptr;
        //afficherActionAvance(pos);
    }
}

Unite::~Unite(){}
