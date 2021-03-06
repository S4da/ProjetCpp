#ifndef SUPER_SOLDAT_H
#define SUPER_SOLDAT_H
#include "fantassin.h"

class SuperSoldat: public Fantassin{
    private:
        
    public:
        SuperSoldat(int pv,Player* player);
        ~SuperSoldat();
        void setHp(int vie) { Fantassin::setHp(vie);};
        std::string getUnitp11() { return "o  ";};
        std::string getUnitp12() { return "|//";};
        std::string getUnitp13() { return "ʌ  ";};

        std::string getUnitp21() { return "  o";};
        std::string getUnitp22() { return "\\\\|";};
        std::string getUnitp23() { return "  ʌ";};
        void action3(int pos, std::vector<Unite*> &champ, Player* ennemi);
};

 #endif
