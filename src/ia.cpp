#include <iostream>
#include <cstdlib>
#include "ia.h"
#include <ctime>

IA::IA():Player(3){
    std::srand(std::time(0));
}

int IA::jouer(){
    int choix=std::rand()%4+1;
    if (choix==1) return strat1();
    else if (choix==2) return stratRandom();
    else return stratMostDmg();
}

int IA::strat1(){
    if (getBalance()>=20) return 3;
    else if (getBalance()>=12) return 2;
    else if (getBalance()>=10) return 1;
    else return 4;
}
int IA::stratRandom(){

    int borneSup=5;
    int choix=0;
    bool bonChoix=false;
    if (getBalance()<10) choix=4;
    else
    {
       do{
            choix=std::rand()%borneSup+1;
            if (choix==1 && getBalance()>=10) bonChoix=true;
            if (choix==2 && getBalance()>=12) bonChoix=true;
            if (choix==3 && getBalance()>=20)  bonChoix=true;
            else if(choix==4) bonChoix=true;
        } while(!bonChoix);
    }
    return choix;
}

int IA::stratMostDmg(){
    if (getBalance()>=20) return 3;
    else if (getBalance()>=10) return 1;
    else if (getBalance()>=12) return 2;
    else return 4;
}

IA::~IA(){}