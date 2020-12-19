#include <iostream>
#include <cstdlib>
#include "catapulte.h"

Catapulte::Catapulte(Player* player): Unite(20,8,2,4,6,player)
{
    setType("Catapulte");
}

void Catapulte::action1(int pos, std::vector<Unite*> &champ, Player* ennemi){
   act1Fait=false;
   int dist=1;
   int pas=1;
    int i=0;
    bool ennemiTrouve=false;
    int taille_champ=champ.size();
    if (champ.at(pos)->getPlayer()->getId()>ennemi->getId()){
        dist=12;
        pas=-1;
        for (i=pos-getRangeMin();i>=pos-getRangeMax()+1;i--){
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
        for (i=pos+getRangeMin();i<pos+getRangeMax();i++){
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
        int t1,t2;
        if (i==pos+(getRangeMax()*pas)){
            t1=i;
            t2=i-pas;
        }else{
            t1=i;
            t2=i+pas;
        }
        
        this->attaque(champ.at(t1));
        this->attaque(champ.at(t2));
        act1Fait=true;
    } else if (i==taille_champ-dist) {
        if (i==pos+(getRangeMax()*pas)){
            afficherActionAtk(pos);
            this->attaque(champ.at(i-pas));
            ennemi->damage(this->getAtk());
        }else{
            afficherActionAtk(pos);
            ennemi->damage(this->getAtk());
        }
        act1Fait=true;
    } 
}

void Catapulte::action3(int pos, std::vector<Unite*> &champ, Player* ennemi){
    if (!act1Fait){
        int pas=1;
        int dist=1+getRangeMin();
        int taille_champ=champ.size();
        if (champ.at(pos)->getPlayer()->getId()>ennemi->getId()){
            pas=-1;
            dist=taille_champ-getRangeMin();
        } 
        if (pos!=taille_champ-dist && champ.at(pos+pas)==nullptr) {
            afficherActionAvance(pos);
            champ.at(pos+pas)=this;
            champ.at(pos)=nullptr;
        }
    }
}

Catapulte::~Catapulte(){}
