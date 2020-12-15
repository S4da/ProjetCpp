#ifndef MODELE_H
#define MODELE_H
#include "unite.h"
#include "player.h"

class Fantassin: public Unite{
    private:
        bool act1Fait=false;
        
    public:
        Fantassin(int id);
        ~Fantassin();
        void setHp(int vie) { Unite::setHp(vie);};
        std::string getUnit() { return " _F_ ";};
        void action1(int pos, std::vector<Unite*> &champ);
        void action2(int pos, std::vector<Unite*> &champ);
        void action3(int pos, std::vector<Unite*> &champ);
        
};

 #endif
