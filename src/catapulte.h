#ifndef CATAPULTE_H
#define CATAPULTE_H
#include "unite.h"
#include "player.h"

class Catapulte: public Unite{
    private:
        bool act1Fait=false;
    public:
        Catapulte(int id);
        ~Catapulte();
        std::string getUnit() { return " _C_ ";};
        void action1(int pos, std::vector<Unite*> &champ);
        //void action2(int pos, std::vector<Unite*> &champ);
        void action3(int pos, std::vector<Unite*> &champ);
};

 #endif
