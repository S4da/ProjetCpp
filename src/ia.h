#ifndef IA_H
#define IA_H
#include "player.h"

class IA: public Player{
    private:
        
    public:
        IA();
        ~IA();
        std::string print() { return "\n\tIA\n\n\n";};
        int jouer();
        int strat1();
        //void joue();
        int stratRandom();
        int stratMostDmg();
};

 #endif
