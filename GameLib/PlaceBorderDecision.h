//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_PLACEBORDERDECISION_H
#define HACKATHON_PLACEBORDERDECISION_H

#include "GameDecision.h"
#include <set>

enum class BorderOrientation
{
    Vertical,
    Horizontal,
};

class PlaceBorderDecision : public GameDecision
{
  public:
    PlaceBorderDecision(const BorderOrientation &orientation, const Coordinate &topLeftCoordinate);

    bool isValidMove(std::shared_ptr<const PlayerData> player, std::shared_ptr<const GameField> gameField) const override;
    void executeMove(std::shared_ptr<PlayerData> player, std::shared_ptr<GameField> gameField) override;

  private:
    BorderOrientation orientation;
    Coordinate topLeftCoordinate;

    bool borderDoesNotCatchPlayer(std::shared_ptr<const GameField> gameField,
                                  std::shared_ptr<const PlayerData> player) const;

    std::set<Combinatorics::EdgeId> getEdgesOfBorder(
        const std::shared_ptr<const GameField> &gameField) const;
};

#endif // HACKATHON_PLACEBORDERDECISION_H
