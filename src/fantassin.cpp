#include <iostream>
#include <cstdlib>
#include "fantassin.h"
#include "super_soldat.h"

Fantassin::Fantassin(Player* player): Unite(10,10,1,1,4,player)
{
    setType("Fantassin");
}

void Fantassin::action1(int pos, std::vector<Unite*> &champ, Player* ennemi){
    act1Fait=false;
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
            if (champ.at(pos+pas)->getHp()<=0) {
                if (getType()==champ.at(pos+pas)->getType()) {
                    afficherDevientSS(pos);
                    champ.at(pos)=new SuperSoldat(champ.at(pos)->getHp(),champ.at(pos)->getPlayer());
                }
            }
        }
        else {
            afficherActionAtk(pos);
            ennemi->damage(this->getAtk());
        }
        act1Fait=true;
    }
    else if (champ.at(pos+pas)!=nullptr) {
        if (this->getPlayer()!=champ.at(pos+pas)->getPlayer()){
            this->attaque(champ.at(pos+pas));
            std::cout<< "\nL'unite a la position "<<pos<<" attaque.";
            if (champ.at(pos+pas)->getHp()<=0) {
                if (getType()==champ.at(pos+pas)->getType()) {
                    if (this->getType()=="Fantassin") std::cout<< "\nL'unite a la position "<<pos<<" devient un Super Soldat.";
                    champ.at(pos)=new SuperSoldat(champ.at(pos)->getHp(),champ.at(pos)->getPlayer());
                }
            }
            act1Fait=true;
        }
    }
}

void Fantassin::action3(int pos, std::vector<Unite*> &champ, Player* ennemi){
    if (!act1Fait) action1(pos,champ,ennemi);
}

Fantassin::~Fantassin(){}
