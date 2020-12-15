#ifndef CATAPULTE_H
#define CATAPULTE_H
#include "unite.h"
#include "player.h"

class Catapulte: public Unite{
    private:
        
    public:
        Catapulte(int id);
        ~Catapulte();
        std::string getUnit() { return " _C_ ";};
};

 #endif
