#include <iostream>
#include <cstdlib>
#include "player.h"

Player::Player(int i)
{
    vie=100;
    id=i;
    balance=20;
}

void Player::print(){ 
    std::cout<<"Player "<<id<< ": \tVie: "<<vie<<"\t Gold: "<<balance<<std::endl<<std::endl;
}

Player::~Player() {}

