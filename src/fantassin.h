#ifndef MODELE_H
#define MODELE_H
#include "unite.h"

class Fantassin: public Unite{
    private:
        bool act1Fait=false;
        
    public:
        Fantassin(Player* player);
        ~Fantassin();
        void setHp(int vie) { Unite::setHp(vie);};
        std::string getUnit() { return "F";};
        void action1(int pos, std::vector<Unite*> &champ, Player* ennemi);
        void action3(int pos, std::vector<Unite*> &champ, Player* ennemi);
        
};

 #endif
