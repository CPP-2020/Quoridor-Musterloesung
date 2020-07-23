//
// Created by bened on 23.07.2020.
//

#include "Ui.h"
#include <vector>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <term.h>
	#include <unistd.h>
#endif

void Ui::drawGame(const GameField &gameField) const {

}

void Ui::showWinnerMessage(const PlayerId &playerId) const {

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

