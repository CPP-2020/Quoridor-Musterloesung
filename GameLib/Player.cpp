//
// Created by bened on 23.07.2020.
//

#include "Player.h"

Player::Player(const std::string &name, const int &id) : name(name), id(id)
{

}

std::string Player::getName() const
{
	return name;
}

int Player::getID() const
{
	return id;
}

void Player::setName(std::string newName)
{
	name = newName;
}

void Player::setId(int newId)
{
	id = newId;
}
