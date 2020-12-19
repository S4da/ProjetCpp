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
        std::string getUnit() { return "C";};
        void action1(int pos, std::vector<Unite*> &champ, Player* ennemi);
        void action2(int pos, std::vector<Unite*> &champ, Player* ennemi){ UNUSED(pos); UNUSED(champ); UNUSED(ennemi);};
        void action3(int pos, std::vector<Unite*> &champ, Player* ennemi);
};

 #endif
