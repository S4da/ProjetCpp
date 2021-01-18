#ifndef CATAPULTE_H
#define CATAPULTE_H
#include "unite.h"
#include "player.h"
#define UNUSED(x) (void)(x)

class Catapulte: public Unite{
    private:
        bool act1Fait=false;
    public:
        Catapulte(Player* player);
        ~Catapulte();
        std::string getUnitp21() { return " /0";};
        std::string getUnitp22() { return "/__";};
        std::string getUnitp23() { return "o o";};

        std::string getUnitp11() { return "0\\ ";};
        std::string getUnitp12() { return "__\\";};
        std::string getUnitp13() { return "o o";};
        void action1(int pos, std::vector<Unite*> &champ, Player* ennemi);
        void action2(int pos, std::vector<Unite*> &champ, Player* ennemi){ UNUSED(pos); UNUSED(champ); UNUSED(ennemi);};
        void action3(int pos, std::vector<Unite*> &champ, Player* ennemi);
};

 #endif