#include "ConsoleUtils.h"

#include <ioStream>
#include <ctime>

using std::cin;
using std::string;
using std::cout;
using std::endl;


int ConsoleUtils::readInteger()
{
    int result = -1;
    cin >> result;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
    }
    return result;
}

long ConsoleUtils::readLong()
{
    long result = -1;
    cin >> result;
    return result;
}

double ConsoleUtils::readDouble()
{
    double result = -1;
    cin >> result;
    return result;
}

std::string ConsoleUtils::readString()
{
    string line = "";
    cin >> line;
    return line;
}

std::string ConsoleUtils::readString(const std::string & message, int maxLength)
{
    string line = "";
    while (line == "" || line.length() > maxLength) {
        cout << message << endl;
        cin >> line;
    }
    return line;
}

int ConsoleUtils::safelyReadInteger(const string & message, int min, int max)
{
    int result = min - 1;
    while (result == min -1) {
		cout << message << endl;
        result = readInteger();
		if (result < min || result > max) {
			cout << "Bitte einen Wert zwischen " << min << " und " << max << " eingeben!" << endl;
			result = min - 1;
		}
    }
    return result;
}

int ConsoleUtils::safelyReadInteger(const string & message)
{
    int result = -1;
    while (result == -1)
    {
		cout << message << endl;
        result = readInteger();
    }
    return result;
}
