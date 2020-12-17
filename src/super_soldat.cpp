#include <iostream>
#include <cstdlib>
#include "super_soldat.h"

SuperSoldat::SuperSoldat(int pv,Player* player): Fantassin(player)
{
    this->setHp(pv);
}


void SuperSoldat::action3(int pos, std::vector<Unite*> &champ, Player* ennemi){
    action1(pos,champ,ennemi);
}

SuperSoldat::~SuperSoldat() {}

