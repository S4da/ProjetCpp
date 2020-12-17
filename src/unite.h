#ifndef UNITE_H
#define UNITE_H
#include<vector>
#include "player.h"

class Unite{
    private:
        int prix;
        int pv;
        int rangeMin;
        int rangeMax;
        int atk;
        int numJoueur;
        Player* player=nullptr;
    public:
        Unite(int prix, int pv, int rangeMin, int rangeMax,int atk,Player* player);
        virtual ~Unite();
        virtual void setHp(int vie) { pv=vie;};
        virtual std::string getUnit() { return " ___ ";};
        int getPrix() {return prix;};
        Player* getPlayer() {return player;};
        void damage(int dmg) { pv-=dmg;};
        int getHp() {return pv;};
        int getAtk() {return atk;};
        int getRangeMax() { return rangeMax;};
        int getRangeMin() { return rangeMin;};
        virtual void action1(int pos, std::vector<Unite*> &champ, Player* ennemi){};
        virtual void action2(int pos, std::vector<Unite*> &champ, Player* ennemi);
        virtual void action3(int pos, std::vector<Unite*> &champ, Player* ennemi){};
        void attaque(Unite* ennemi);
        
};

 #endif
