#ifndef ARCHER_H
#define ARCHER_H
#include "player.h"

class Archer: public Unite{
    private:
        
    public:
        Archer(int id);
        ~Archer();
        std::string getUnit() { return " _A_ ";};
};

 #endif
