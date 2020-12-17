#include <iostream>
#include <cstdlib>
#include "archer.h"

Archer::Archer(Player* player): Unite(12,8,1,3,3,player)
{}

void Archer::action1(int pos, std::vector<Unite*> &champ, Player* ennemi){
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
    }
    else if (ennemiTrouve)
    {   
        this->attaque(champ.at(i));
        if (champ.at(i)->getHp()<=0) champ.at(i)=nullptr;
    }
}



void Archer::action3(int pos, std::vector<Unite*> &champ, Player* ennemi){
    
}
Archer::~Archer(){}
