//
// Created by bened on 23.07.2020.
//

#include "Ui.h"
#include "GameField.h"
#include "Player.h"
#include "Coordinate.h"
#include <vector>
#include <iostream>
#include <memory>

// Without NOMINMAX, windows.h defines a max() macro
// which conflicts with std::numeric_limits<std::streamsize>::max().
#ifdef _WIN32
	#define NOMINMAX
	#include <windows.h>
#else
	#include <term.h>
	#include <unistd.h>
#endif

static std::string const first_delimiter_y_open = "  ";

static std::string const delimiter_x_open = "   ";
static std::string const delimiter_x_closed = " | ";
static std::string const delimiter_y_open = "    ";
#ifdef _WIN32
	static std::string const first_delimiter_y_closed = "--";
	static std::string const last_delimiter_y_closed = " --";
	static std::string const delimiter_y_closed = " ---";
#else
	static std::string const first_delimiter_y_closed = "\u2015\u2015";
	static std::string const last_delimiter_y_closed = " \u2015\u2015";
	static std::string const delimiter_y_closed = " \u2015\u2015\u2015";
#endif

void Ui::drawGame(std::shared_ptr<const GameField> gameField) const {
	std::string result;
	for (int y = 0; y < gameField->getHeight(); y++) {
		for (int x = 0; x < gameField->getWidth(); x++) {
			appendDelimiter(result, gameField,Coordinate(x, y));
		}
		result.append("\n");
		for (int x = 0; x < gameField->getWidth(); x++) {
			appendContent(result, gameField, Coordinate(x, y));
		}
		result.append("\n");
	}
	std::cout << result << std::endl;
}

void Ui::appendDelimiter(std::string & result, std::shared_ptr<const GameField> gameField, Coordinate const & coordinate) const
{
	if (coordinate.y() != 0) {
		if (gameField->isOpenBelowCoordinate(coordinate)) {
			result.append(coordinate.x() == 0 ? first_delimiter_y_open : delimiter_y_open);
		} else {
			if(coordinate.x() == 0)
			{
				result.append(first_delimiter_y_closed);
			}
            else if (coordinate.x() == gameField->getWidth() - 1)
			{
				result.append(last_delimiter_y_closed);
			}
			else
			{
                result.append(delimiter_y_closed);
			}
		}
	}
}

void Ui::appendContent(std::string & result, std::shared_ptr<const GameField> gameField, Coordinate const & coordinate) const
{
	if (coordinate.x() != 0) {
		if (gameField->isOpenLeftOfCoordinate(coordinate)) {
			result.append(delimiter_x_open);
		} else {
			result.append(delimiter_x_closed);
		}
	}
	result.append(gameField->getPosition(coordinate).toString());
}

void Ui::showWinnerMessage(std::shared_ptr<const PlayerData> player) const {
	std::cout << "Player " << player->getName() << " has won! Congrats!" << std::endl;
}

void Ui::showMessage(const std::string &message) const
{
	std::cout << message << std::endl;
}

int Ui::showMultipleChoice(const std::string &message, const std::vector<std::string> &answers) const {
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

void Ui::clearScreen() const {
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
