#ifndef SUPER_SOLDAT_H
#define SUPER_SOLDAT_H
#include "fantassin.h"
#include "player.h"

class SuperSoldat: public Fantassin{
    private:
        
    public:
        SuperSoldat(int pv,int id);
        ~SuperSoldat();
        void setHp(int vie) { Fantassin::setHp(vie);};
        std::string getUnit() { return " _SS_ ";};
};

 #endif
