#ifndef ARCHER_H
#define ARCHER_H
#include "player.h"
#include "unite.h"

class Archer: public Unite{
    private:
        
    public:
        Archer(Player* player);
        ~Archer();
        std::string getUnit() { return "A";};
        void action1(int pos, std::vector<Unite*> &champ, Player* ennemi);

};

 #endif
