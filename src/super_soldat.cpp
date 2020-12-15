#include <iostream>
#include <cstdlib>
#include "super_soldat.h"
#include "player.h"

SuperSoldat::SuperSoldat(int pv,int id): Fantassin(id)
{
    this->setHp(pv);
}

SuperSoldat::~SuperSoldat() {}

