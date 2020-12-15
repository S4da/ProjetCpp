#ifndef MODELE_H
#define MODELE_H
#include "unite.h"
#include "player.h"

class Fantassin: public Unite{
    private:
        
    public:
        Fantassin(int id);
        ~Fantassin();
        void setHp(int vie) { Unite::setHp(vie);};
        std::string getUnit() { return " _F_ ";};
        
};

 #endif
