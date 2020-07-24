//
// Created by bened on 23.07.2020.
//

#include "Ui.h"
#include "Player.h"
#include <iostream>
#include <memory>
#include <vector>

// Without NOMINMAX, windows.h defines a max() macro
// which conflicts with std::numeric_limits<std::streamsize>::max().
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#else
#include <term.h>
#include <unistd.h>
#endif

void Ui::drawGame(std::shared_ptr<const GameField> gameField) const
{
    // TODO: Current players
    // TODO: Player statistics

    clearScreen();
    std::vector<std::vector<GamePrintTile>> output = buildOutputBuffer(gameField);

    drawGameRowColumnNumbers(gameField, output);
    drawGameGrid(gameField, output);
    drawGamePlayers(gameField, output);
    drawGameHorizontalBorders(gameField, output);
    drawGameVerticalBorders(gameField, output);
    drawGameOutputToCout(output);
}

void Ui::showWinnerMessage(std::shared_ptr<const PlayerData> player) const
{
    std::cout << player->getName() << " has won! Congrats!" << std::endl;
}

void Ui::showMessage(const std::string &message) const
{
    std::cout << message << std::endl;
}

int Ui::showMultipleChoice(const std::string &message,
                           const std::vector<std::string> &answers) const
{
    int result;

    std::cout << message << std::endl;

    for (int i = 0; i < answers.size(); i++)
    {
        std::cout << i + 1 << ": " << answers[i] << std::endl;
    }

    std::cout << "Answer: ";
    std::cin >> result;

    while (std::cin.fail() || result > answers.size() || result < 1)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "The given answer was invalid! Please enter a new answer: ";
        std::cin >> result;
    }

    return result;
}


std::vector<std::vector<GamePrintTile>> Ui::buildOutputBuffer(
    const std::shared_ptr<const GameField> &gameField) const
{
    std::vector<std::vector<GamePrintTile>> output;

    int outputHeight = gameField->getHeight() * (fieldHeight + 1) + 1 + firstRowHeight;
    int outputWidth = gameField->getWidth() * (fieldWidth + 1) + 1 + firstColumnWidth;

    outputHeight += 1; // Current player line
    outputHeight += 1; // Player remaining borders line

    for (int x = 0; x < outputWidth; x++)
    {
        std::vector<GamePrintTile> line;

        for (int y = 0; y < outputHeight; y++)
        {
            line.push_back(GamePrintTile());
        }

        output.push_back(line);
    }
    return output;
}

void Ui::drawGameRowColumnNumbers(std::shared_ptr<const GameField> gameField,
                                  std::vector<std::vector<GamePrintTile>> &output) const
{
    // Draw the row indices
    for (int y = 0; y < gameField->getHeight() - 1; y++)
    {
        output[0][(y + 1) * 2 + firstRowHeight].character = std::to_string(y + 1);
    }

    // Draw the column indices
    for (int y = 0; y < gameField->getWidth() - 1; y++)
    {
        output[(y + 1) * 4 + firstColumnWidth][0].character = std::to_string(y + 1);
    }
}

void Ui::drawGameGrid(const std::shared_ptr<const GameField> &gameField,
                      std::vector<std::vector<GamePrintTile>> &output) const
{
    // Draw the +
    for (int y = 0; y < gameField->getHeight() + 1; y++)
    {
        for (int x = 0; x < gameField->getWidth() + 1; x++)
        {
            output[x * (fieldWidth + 1) + firstColumnWidth][y * 2 + firstRowHeight].character = "+";
        }
    }
}

void Ui::drawGamePlayers(const std::shared_ptr<const GameField> &gameField,
                         std::vector<std::vector<GamePrintTile>> &output) const
{
    for (const auto &p: gameField->getAllPlayersOnField())
    {
        auto position = gameField->getPlayerPosition(p);

        int xPosition = position->x() * (fieldWidth + 1) + 2 + firstColumnWidth;
        int yPosition = position->y() * (fieldHeight + 1) + 1 + firstRowHeight;

        output[xPosition][yPosition].character = "X";
        output[xPosition][yPosition].foregroundColor = ConsoleColor::Red;
    }
}

void Ui::drawGameHorizontalBorders(const std::shared_ptr<const GameField> &gameField,
                                   std::vector<std::vector<GamePrintTile>> &output) const
{
    // Color the horizontal borders
    for (int y = 0; y < gameField->getHeight() - 1; y++)
    {
        for (int x = 0; x < gameField->getWidth(); x++)
        {
            if (!gameField->isOpenBelowCoordinate({x, y}))
            {
                int xPosition = x * (fieldWidth + 1) + 2 + firstColumnWidth;
                int yPosition = y * (fieldHeight + 1) + 2 + firstRowHeight;

                output[xPosition - 2][yPosition].foregroundColor = ConsoleColor::Yellow;
                output[xPosition - 1][yPosition].foregroundColor = ConsoleColor::Yellow;
                output[xPosition - 1][yPosition].character = "-";
                output[xPosition + 0][yPosition].foregroundColor = ConsoleColor::Yellow;
                output[xPosition + 0][yPosition].character = "-";
                output[xPosition + 1][yPosition].foregroundColor = ConsoleColor::Yellow;
                output[xPosition + 1][yPosition].character = "-";
                output[xPosition + 2][yPosition].foregroundColor = ConsoleColor::Yellow;
            }
        }
    }
}

void Ui::drawGameVerticalBorders(const std::shared_ptr<const GameField> &gameField,
                                 std::vector<std::vector<GamePrintTile>> &output) const
{
    for (int y = 0; y < gameField->getHeight(); y++)
    {
        for (int x = 1; x < gameField->getWidth(); x++)
        {
            if (!gameField->isOpenLeftOfCoordinate({x, y}))
            {
                int xPosition = x * (fieldWidth + 1) + firstColumnWidth;
                int yPosition = (y - 1) * (fieldHeight + 1) + fieldWidth + firstRowHeight;

                output[xPosition][yPosition - 1].foregroundColor = ConsoleColor::Yellow;
                output[xPosition][yPosition + 0].foregroundColor = ConsoleColor::Yellow;
                output[xPosition][yPosition + 0].character = "|";
                output[xPosition][yPosition + 1].foregroundColor = ConsoleColor::Yellow;
            }
        }
    }
}

void Ui::drawGameOutputToCout(std::vector<std::vector<GamePrintTile>> &output) const
{
    for (int y = 0; y < output[0].size(); y++)
    {
        for (int x = 0; x < output.size(); x++)
        {
            output[x][y].print();
        }

        std::cout << std::endl;
    }
}

void Ui::clearScreen() const
{
#ifdef _WIN32
    HANDLE hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = {0, 0};

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE)
    {
        return;
    }

    // Get the number of cells in the current buffer
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        return;
    }
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire buffer with spaces
    if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, homeCoords, &count))
    {
        return;
    }

    // Fill the entire buffer with the current colors and attributes
    if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count))
    {
        return;
    }

    // Move the cursor home
    SetConsoleCursorPosition(hStdOut, homeCoords);

#else
    if (!cur_term)
    {
        int result;
        setupterm(NULL, STDOUT_FILENO, &result);
        if (result <= 0)
        {
            return;
        }
    }
#endif
}

#ifdef _WIN32
void GamePrintTile::print()
{
    int colorCode = 7;

    switch (foregroundColor)
    {
    case ConsoleColor::Black:
        colorCode = 0;
        break;
    case ConsoleColor::Red:
        colorCode = 4;
        break;
    case ConsoleColor::Green:
        colorCode = 2;
        break;
    case ConsoleColor::Yellow:
        colorCode = 6;
        break;
    case ConsoleColor::Blue:
        colorCode = 1;
        break;
    case ConsoleColor::Magenta:
        colorCode = 4;
        break;
    case ConsoleColor::Cyan:
        colorCode = 9;
        break;
    case ConsoleColor::White:
        colorCode = 7;
        break;
    case ConsoleColor::Gray:
        colorCode = 8;
        break;
    }

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE)
    {
        return;
    }

    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hStdOut, &info);
    SetConsoleTextAttribute(hStdOut, colorCode);

    std::cout << character;

    SetConsoleTextAttribute(hStdOut, info.wAttributes);
}
#else
void GamePrintTile::print()
{
    std::string colorCode = "";

    switch (foregroundColor)
    {
    case ConsoleColor::Black:
        colorCode = "\x1B[30m";
        break;
    case ConsoleColor::Red:
        colorCode = "\x1B[31m";
        break;
    case ConsoleColor::Green:
        colorCode = "\x1B[32m";
        break;
    case ConsoleColor::Yellow:
        colorCode = "\x1B[33m";
        break;
    case ConsoleColor::Blue:
        colorCode = "\x1B[34m";
        break;
    case ConsoleColor::Magenta:
        colorCode = "\x1B[35m";
        break;
    case ConsoleColor::Cyan:
        colorCode = "\x1B[36m";
        break;
    case ConsoleColor::White:
        colorCode = "\x1B[37m";
        break;
    }

    std::string colorCodeEnd = "\033[0m";

    std::cout << colorCode << character << colorCodeEnd;
}
#endif

int Ui::showMultipleIntChoice(const std::string &message, const int minValue,
    const int maxValue) const
{
    int result;

    std::cout << message << std::endl;


    std::cout << "Answer: ";
    std::cin >> result;

    while (std::cin.fail() || result > maxValue || result < minValue)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "The given answer was invalid! Please enter a new answer: ";
        std::cin >> result;
    }

    return result;
}
