#ifndef ARCHER_H
#define ARCHER_H
#include "player.h"

class Archer: public Unite{
    private:
        
    public:
        Archer(int id);
        ~Archer();
        std::string getUnit() { return " _A_ ";};
        void action1(int pos, std::vector<Unite*> &champ);
        void action2(int pos, std::vector<Unite*> &champ);
        void action3(int pos, std::vector<Unite*> &champ);
};

 #endif
