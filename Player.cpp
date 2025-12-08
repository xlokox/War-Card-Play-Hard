#include "player.h"
#include <iostream>
#include "Card.h"
#include "Deck.h"

using namespace std;


Player::Player(const Player &other)

    : hand(other.hand)
{


size_t len = std;strlen(other.name) + 1;
this->name = new char[len];
 strcpy(this->name, other.name);
}


Player::~Player(){
    (delete[] this->name);
}

void Card Player::receiveCard()
{ 
    return this->card.draw ;
}






