#include <iostream>
#include <cstdlib>
#include "unite.h"

Unite::Unite(int prix, int pv, int rangeMin,int rangeMax,int atk,int numJoueur){
    this->prix=prix;
    this->pv=pv;
    this->rangeMin=rangeMin;
    this->rangeMax=rangeMax;
    this->atk=atk;
    this->numJoueur=numJoueur;
}

Unite::~Unite(){}
