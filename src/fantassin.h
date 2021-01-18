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
        std::string getUnitp11() { return " o ";};
        std::string getUnitp12() { return " |/";};
        std::string getUnitp13() { return " ʌ ";};

        std::string getUnitp21() { return " o ";};
        std::string getUnitp22() { return "\\| ";};
        std::string getUnitp23() { return " ʌ ";};
        
        void action1(int pos, std::vector<Unite*> &champ, Player* ennemi);
        void action3(int pos, std::vector<Unite*> &champ, Player* ennemi);
        void afficherDevientSS(int pos) { std::cout<<"\nL'unite a la position "<<pos<<" devient un Super Soldat.";};
};

 #endif