#include <iostream>
#include <cstdlib>
#include "catapulte.h"

Catapulte::Catapulte(Player* player): Unite(20,8,2,4,6,player)
{}

void Catapulte::action1(int pos, std::vector<Unite*> &champ, Player* ennemi){
   act1Fait=false;
   int dist=1;
    int pas=1;
    int i=0;
    bool ennemiTrouve=false;
    if (champ.at(pos)->getPlayer()->getId()>ennemi->getId()){
        dist=12;
        pas=-1;
        for (i=pos-getRangeMin();i>=pos-getRangeMax();i--){
            if (i==champ.size()-dist){
                ennemiTrouve=true;
                break;
            }else if (champ.at(i)!=nullptr){
                if (this->getPlayer()!=champ.at(i)->getPlayer()){
                    ennemiTrouve=true;
                    break;
                }
            }
        }
    }
    else{
        for (i=pos+getRangeMin();i<=pos+getRangeMax();i++){
            if (i==champ.size()-dist){
                ennemiTrouve=true;
                break;
            }else if (champ.at(i)!=nullptr){
                if (this->getPlayer()!=champ.at(i)->getPlayer()){
                    ennemiTrouve=true;
                    break;
                }
            }
        }
    }
    if (i==champ.size()-dist) {
        ennemi->damage(this->getAtk());
        act1Fait=true;
    }
    else if (ennemiTrouve)
    {   
        this->attaque(champ.at(i));
        if (champ.at(i)->getHp()<=0) champ.at(i)=nullptr;
        act1Fait=true;
    }
}

void Catapulte::action3(int pos, std::vector<Unite*> &champ, Player* ennemi){
    if (!act1Fait) Unite::action2(pos, champ, ennemi);
}

Catapulte::~Catapulte(){}
