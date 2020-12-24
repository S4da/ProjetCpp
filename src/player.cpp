#include <iostream>
#include <cstdlib>
#include "player.h"

Player::Player(int i)
{
    vie=100;
    id=i;
    balance=20;
}

std::string Player::print(){ 
    return "Player "+std::to_string(id)+ ": \tVie: "+std::to_string(vie)+"\t Gold: "+std::to_string(balance)+"\n\n";
}

Player::~Player() {}

