#include <iostream>
#include <cstdlib>
#include "archer.h"


Archer::Archer(Player* player): Unite(12,8,1,3,3,player)
{
    setType("Archer");
}

void Archer::action1(int pos, std::vector<Unite*> &champ, Player* ennemi){
    int dist=1;
    int i=0;
    int taille_champ=champ.size();
    bool ennemiTrouve=false;
    if (champ.at(pos)->getPlayer()->getId()>ennemi->getId()){
        dist=12;
        for (i=pos-getRangeMin();i>=pos-getRangeMax();i--){
            if (i==taille_champ-dist){
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
            if (i==taille_champ-dist){
                break;
            }else if (champ.at(i)!=nullptr){
                if (this->getPlayer()!=champ.at(i)->getPlayer()){
                    ennemiTrouve=true;
                    break;
                }
            }
        }
    }
    if (ennemiTrouve)
    {   
        //afficherActionAtk(pos);
        this->attaque(champ.at(i));
    }else if (i==taille_champ-dist) {
        afficherActionAtk(pos);
        ennemi->damage(this->getAtk());
    }
}

Archer::~Archer(){}
