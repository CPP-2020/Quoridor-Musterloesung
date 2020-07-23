//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_PLAYERDATA_H
#define HACKATHON_PLAYERDATA_H

#include "GameField.h"
#include <string>

class PlayerData
{
  public:
    PlayerData(const std::string &name, int id, BoardSides startSide);

    int getID() const;
    std::string getName() const;
    BoardSides getStartSide() const;

    int getRemainingBorders() const;
    void setRemainingBorders(int borders);

  private:
    std::string name;
    int id;
    BoardSides startSide;
    int remainingBorders = 10;
};

#endif // HACKATHON_PLAYERDATA_H
