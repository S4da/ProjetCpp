#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include<cstdlib>
//#include "unite.h"

class Player{
    private:
        int vie;
        int balance;
        //std::vector<Unite*> champ;
        int id=0;
    public:
        Player(int i);
        virtual ~Player();
        bool aPerdu() { return vie <= 0;};
        void print();
        void addOr(int montant){ balance+=montant;};
        int getBalance() { return balance;};
        int getId() { return id;};
        void payer(int montant) { balance-=montant;};
        void damage(int montant) { vie-=montant;};
        int getVie() {return vie;};
        bool operator==(Player* player) { return this->getId()==player->getId();};
        bool operator!=(Player* player) { return this->getId()!=player->getId();};
        //virtual void joue();
};

 #endif
