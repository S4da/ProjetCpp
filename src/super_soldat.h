#ifndef SUPER_SOLDAT_H
#define SUPER_SOLDAT_H
#include "fantassin.h"

class SuperSoldat: public Fantassin{
    private:
        
    public:
        SuperSoldat(int pv,Player* player);
        ~SuperSoldat();
        void setHp(int vie) { Fantassin::setHp(vie);};
        std::string getUnit() { return "S";};
        void action3(int pos, std::vector<Unite*> &champ, Player* ennemi);
};

 #endif
