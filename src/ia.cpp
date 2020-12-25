#include <iostream>
#include <cstdlib>
#include "ia.h"


IA::IA():Player(3){
}

int IA::jouer(){
    return strat1();
}

int IA::strat1(){
    std::cout<<getBalance();
    if (getBalance()>=20) return 3;
    else if (getBalance()>=12) return 2;
    else if (getBalance()>=10) return 1;
    else return 4;
}

IA::~IA(){}