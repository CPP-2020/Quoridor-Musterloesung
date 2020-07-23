//
// Created by bened on 23.07.2020.
//

#include "PlayerId.h"

std::string PlayerId::getName()
{
    return name;
}

int PlayerId::getID()
{
    return id;
}

void PlayerId::setName(std::string NewName)
{
    name = NewName;
}

void PlayerId::setId(int NewId)
{
    id = NewId;
}
