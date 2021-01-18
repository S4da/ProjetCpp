#ifndef ARCHER_H
#define ARCHER_H
#include "player.h"
#include "unite.h"

class Archer: public Unite{
    private:
        
    public:
        Archer(Player* player);
        ~Archer();
        std::string getUnitp21() { return "  o";};
        std::string getUnitp22() { return "-(|";};
        std::string getUnitp23() { return "  ʌ";};

        std::string getUnitp11() { return "o  ";};
        std::string getUnitp12() { return "|)-";};
        std::string getUnitp13() { return "ʌ  ";};
        void action1(int pos, std::vector<Unite*> &champ, Player* ennemi);

};

 #endif