//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_UI_H
#define HACKATHON_UI_H

#include "GameField.h"
#include <memory>
#include <string>
#include <vector>

enum class ConsoleColor
{
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    Gray
};

class GamePrintTile
{
  public:
    std::string character = " ";
    ConsoleColor foregroundColor = ConsoleColor::Gray;
    ConsoleColor backgroundColor;

    void print();
};

class Ui
{
  public:
    void drawGame(std::shared_ptr<const GameField> gameField) const;
    void showWinnerMessage(std::shared_ptr<const PlayerData> player) const;
    void showMessage(const std::string &message) const;
    int showMultipleChoice(const std::string &message,
                           const std::vector<std::string> &answers) const;

  private:
    void clearScreen() const;

    void drawGameRowColumnNumbers(std::shared_ptr<const GameField> gameField,
                                  std::vector<std::vector<GamePrintTile>> &output) const;

    void drawGameGrid(const std::shared_ptr<const GameField> &gameField,
                      std::vector<std::vector<GamePrintTile>> &output) const;

    void drawGamePlayers(const std::shared_ptr<const GameField> &gameField,
                         std::vector<std::vector<GamePrintTile>> &output) const;

    void drawGameHorizontalBorders(const std::shared_ptr<const GameField> &gameField,
                                   std::vector<std::vector<GamePrintTile>> &output) const;

    void drawGameVerticalBorders(const std::shared_ptr<const GameField> &gameField,
                                 std::vector<std::vector<GamePrintTile>> &output) const;

    void drawGameOutputToCout(std::vector<std::vector<GamePrintTile>> &output) const;

    std::vector<std::vector<GamePrintTile>> buildOutputBuffer(
        const std::shared_ptr<const GameField> &gameField) const;

    int fieldHeight = 1;
    int fieldWidth = 3;
    int firstColumnWidth = 2;
    int firstRowHeight = 1;
};

#endif // HACKATHON_UI_H
